#include "Grid.h"
#include <Gamebuino-Meta.h>

// defined new color for the GAMEBUINO
Color LIME = gb.createColor(132, 226, 44);

/*
  GRID POSITION

   0 | 1 | 2
  -----------
   3 | 4 | 5
  -----------
   6 | 7 | 8

*/
Grid::Grid() :  m_gridPos(4),  m_gridPlayer(0),  m_gridWinning
{
  {0, 4, 8},
  {2, 4, 6},
  {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8},
  {0, 3, 6},
  {1, 4, 7},
  {2, 5, 8}
}, m_boxCursor(0), m_gridPlayerWinner(0), m_soundNotRepeat(1), m_symbol(0), m_playerOne(0), m_playerTwo(0), m_gridParty(5)
{
  // create objects external to the class
  // create objects external Box
  m_boxCursor = new Box(4, 3);
  m_boxFirstSymbol = new Box(0, 0);
  m_boxSecondSymbol = new Box(0, 0);
  m_boxThreeSymbol = new Box(0, 0);
  // create objects external Symbol
  m_symbol = new Symbol(0, 8, 'E');
  m_playerOne = new Player(LEFT, "PLAYER 1" );
  m_playerTwo = new Player(RIGHT, "PLAYER 2" );
}

Grid::~Grid()
{
  delete m_boxFirstSymbol;
  delete m_boxSecondSymbol;
  delete m_boxThreeSymbol;
  delete m_boxCursor;
  delete m_symbol;
  delete m_playerOne;
  delete m_playerTwo;
}

// initialize the grid
void Grid::Initialize()
{
  for (int i = 0; i < 9; i++)
  {
    m_grid[i] = {'E'};
  }
}

char Grid::getGrid (int nbrBox ) const
{
  return (m_grid[nbrBox]);
}

int Grid::getGridWin (int line, int column ) const
{
  return (m_gridWinning[line][column]);
}

bool Grid::gridVerifySymbol ()
{
  if (m_grid[m_gridPos] == 'E') // no symbol in the box
  {
    return 1;
  }
  if (m_grid[m_gridPos] != 'E') // presence of a symbol in the box
  {
    return 0;
  }
}

//--------------------------------------------------------------------------------/
//  FR : fonction qui retourne 0 si aucun gagnant et 1 ou 2 selon le joueur       /
//  US : function that returns 0 if no winner and 1 or 2 depending on the player  /
//--------------------------------------------------------------------------------/

int Grid::VerifyWinner()
{
  for (int i = 0; i < 2 ; i++)
  {
    char tempChar = 0;
    int tempPlayerChoose = 0;
    int tempColor = 0;
    int firstRec = 0;
    int secondRec = 0;
    int threeRec = 0;
    if ( i == 0 )
    {
      tempChar = 'O';
      tempPlayerChoose = 1;
      tempColor = m_playerOne->Color();
    }
    else if ( i == 1 )
    {
      tempChar = 'X';
      tempPlayerChoose = 2;
      tempColor = m_playerTwo->Color();
    }
    // FR : vérifier les huit combinaisons gagnantes
    // US : check out the eight winning combinations
    for (int y = 0; y < 8; y++)
    {
      firstRec = m_gridWinning[y][0];
      secondRec = m_gridWinning[y][1];
      threeRec = m_gridWinning[y][2];
      if (m_grid[firstRec] == tempChar && m_grid[secondRec] == tempChar && m_grid[threeRec] == tempChar)
      {
        m_boxFirstSymbol->Color(tempColor);
        m_boxFirstSymbol->Position(firstRec);
        m_boxFirstSymbol->Draw();
        gb.lights.fill(RED); delay(100);
        gb.sound.playTick(); delay(350);
        gb.lights.clear(); delay(250);
        m_boxSecondSymbol->Color(tempColor);
        m_boxSecondSymbol->Position(secondRec);
        m_boxSecondSymbol->Draw();
        gb.lights.fill(RED); delay(100);
        gb.sound.playTick(); delay(350);
        gb.lights.clear(); delay(250);
        m_boxThreeSymbol->Color(tempColor);
        m_boxThreeSymbol->Position(threeRec);
        m_boxThreeSymbol->Draw();
        gb.lights.fill(RED); delay(100);
        gb.sound.playTick(); delay(350);
        gb.lights.clear(); delay(250);
        m_gridPlayerWinner = tempPlayerChoose;
        if ( tempChar == 'O' )
        {
          m_playerOne->Score(m_playerOne->Score() + 1);
        }
        else if ( tempChar == 'X' )
        {
          m_playerTwo->Score(m_playerTwo->Score() + 1);
        }
        m_soundNotRepeat = 1;
        return (tempPlayerChoose);
      }
    }
  }
  return 0;
}


// draw the grid and box
void Grid::Draw () const
{
  // draw Grid
  gb.display.setColor(LIME);
  gb.display.drawLine(30, 0, 30, 60);
  gb.display.drawLine(50, 0, 50, 60);
  gb.display.drawLine(10, 20, 70, 20);
  gb.display.drawLine(10, 40, 70, 40);
  // draw Symbols
  for (int i = 0; i < 9; i++)
  {
    if ( m_grid[i] == 'O' )
    {
      m_symbol->Color(8);
      m_symbol->Type('O');
      m_symbol->Position(i);
      m_symbol->Draw();
    }
    else if ( m_grid[i] == 'X' )
    {
      m_symbol->Color(1);
      m_symbol->Type('X');
      m_symbol->Position(i);
      m_symbol->Draw();
    }

  }

  // draw Player
  m_playerOne->Draw();
  m_playerTwo->Draw();
  m_playerOne->Color(8);
  m_playerTwo->Color(1);


}

void Grid::MoveBox()
{
  if (gb.buttons.pressed(BUTTON_RIGHT) )
  {
    if ( m_gridPos != 2 and m_gridPos != 5 and m_gridPos != 8)
    {
      m_gridPos++;
    }
  }
  if (gb.buttons.pressed(BUTTON_LEFT) )
  {
    if ( m_gridPos != 0 and m_gridPos != 3 and m_gridPos != 6 )
    {
      m_gridPos--;
    }
  }
  if (gb.buttons.pressed(BUTTON_UP) )
  {
    if ( m_gridPos != 0 and m_gridPos != 1 and m_gridPos != 2 )
    {
      m_gridPos = m_gridPos - 3;
    }
  }
  if (gb.buttons.pressed(BUTTON_DOWN) )
  {
    if ( m_gridPos != 6 and m_gridPos != 7 and m_gridPos != 8 )
    {
      m_gridPos = m_gridPos + 3;
    }
  }
  // draw Box
  m_boxCursor->Position(m_gridPos);
  m_boxCursor->Draw();
}

void Grid::Button()
{
  if (gb.buttons.pressed(BUTTON_A) )
  {
    if (gridVerifySymbol ())
    {
      if (m_gridPlayer == 0)
      {
        m_grid[m_gridPos] = 'O';
      }
      else
      {
        m_grid[m_gridPos] = 'X';
      }
      m_gridPlayer = !m_gridPlayer;
      gb.sound.playTick();
    }
  }
  if (gb.buttons.pressed(BUTTON_B) )
  {
    m_grid[m_gridPos] = 'E';
    m_gridPlayer = !m_gridPlayer;
    gb.sound.play("button_1.wav");
  }
  // State Player
  m_playerOne->State(!m_gridPlayer);
  m_playerTwo->State(m_gridPlayer);
}

void Grid::Winner()
{
  gb.display.setColor(DARKGRAY);
  gb.display.fillRect( 9 , 22, 64, 18);
  gb.display.setColor(WHITE);
  gb.display.fillRect( 8 , 22, 64, 18);
  gb.display.setColor(GRAY);
  gb.display.drawRect( 8 , 22, 64, 18);
  gb.display.setCursor(10, 25);
  gb.display.print(" PLAYER ");
  gb.display.print(m_gridPlayerWinner);
  gb.display.print(" WINS ");
  gb.display.setCursor(10, 32);
  if ( m_gridParty == m_playerOne->Score() or m_gridParty == m_playerTwo->Score() )
  {
    gb.display.print(" THE PARTY ");
    if (m_soundNotRepeat == 1 )
    {
      gb.sound.play("win_1.wav");
      m_soundNotRepeat = 0;
      delay(1000);
    }
    m_playerOne->Score(0);
    m_playerTwo->Score(0);
  }
  else if ( m_playerOne->Score() !=0 or m_playerTwo->Score() !=0)
  {
    gb.display.print(" THE ROUND ");
    if (m_soundNotRepeat == 1 )
    {
      gb.sound.play("win_2.wav");
      m_soundNotRepeat = 0;
      delay(500);
    }
  }
  else
  {
    gb.display.print(" THE PARTY ");
  }
}
