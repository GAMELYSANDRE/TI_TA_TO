#include <Gamebuino-Meta.h>
// grid ti ta to
// E = Empty
char grid[9] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'};
int boxPosX = 20;
int boxPosY = 20;
int tempo = 0;
int posTab = 4;
bool tiltPlayer = 0;
bool soundTest = 1;
int modeGame = 1;
int playerOneScore = 0;
int playerTwoScore = 0;
int numberPart = 5;
const char textPlayer[3][9] = {"PLAYER 1", "PLAYER 2", "COMPUTER"};
const int gridWinning[8][3] =
{
  {0, 4, 8},
  {2, 4, 6},
  {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8},
  {0, 3, 6},
  {1, 4, 7},
  {2, 5, 8}
};
const char textNumber[7] = {'0', '1', '2', '3', '4', '5'};

Color MEDIUMPURPLE = gb.createColor(147, 112, 219);
Color LIME = gb.createColor(132, 226, 44);

// initialize the grid
void iniGrid (char grid[], int gridSize)
{
  for (int i = 0; i < gridSize; i++)
  {
    grid[i] = {'E'};
  }
}
// display the grid
void displayGrid (char grid[], int gridSize)
{
  for (int i = 0; i < gridSize; i++)
  {
    if ( grid[i] == 'O' )
    {
      drawCir ((i - (3 * (i / 3))) * 20, (i / 3) * 20 );
    }
    else if ( grid[i] == 'X' )
    {
      drawCross ((i - (3 * (i / 3))) * 20, (i / 3) * 20 );
    }
    //gb.display.print(grid[i]);
  }
}
bool verifySymbole (char grid[], int gridSize, int posTab)
{
  if (grid[posTab] == 'E')
  {
    return 1;
  }
  if (grid[posTab] != 'E')
  {
    return 0;
  }
}
bool verifyGrid (char grid[], int gridSize)
{
  for (int i = 0; i < 2 ; i++)
  {
    char Symbol = 0;
    if ( i == 0 )
    {
      Symbol = 'O';
      gb.display.setColor(RED);
    }
    else if ( i == 1 )
    {
      Symbol = 'X';
      gb.display.setColor(GREEN);
    }
    for (int y = 0; y < 8; y++)
    {
      int firstRec = gridWinning[y][0];
      int secondRec = gridWinning[y][1];
      int threeRec = gridWinning[y][2];
      if (grid[firstRec] == Symbol && grid[secondRec] == Symbol && grid[threeRec] == Symbol)
      {
        gb.display.fillRect((firstRec - (3 * (firstRec / 3))) * 20 + 11, (firstRec / 3) * 20  , 19, 19);
        gb.display.fillRect((secondRec - (3 * (secondRec / 3))) * 20 + 11, (secondRec / 3) * 20, 19, 19);
        gb.display.fillRect((threeRec - (3 * (threeRec / 3))) * 20 + 11, (threeRec / 3) * 20, 19, 19);
        return 1;
      }
    }
  }
  return 0;
}


void GridDraw ()
{
  gb.display.setColor(LIME);
  gb.display.drawLine(30, 0, 30, 60);
  gb.display.drawLine(50, 0, 50, 60);
  gb.display.drawLine(10, 20, 70, 20);
  gb.display.drawLine(10, 40, 70, 40);
}
void drawRec (int posRecx, int posRecY )
{
  tempo++;
  if (tempo < 15)
  {
    gb.display.setColor(WHITE);
  }
  else
  {
    gb.display.setColor(BLACK);
  }
  if (tempo == 30)
  {
    tempo = 0;
  }
  gb.display.fillRect(posRecx + 11, posRecY + 1, 19, 19);
}
void drawCir (int posCirx, int posCirY )
{
  gb.display.setColor(MEDIUMPURPLE);
  gb.display.drawCircle(posCirx + 20, posCirY + 10, 6);
  gb.display.drawCircle(posCirx + 20, posCirY + 10, 5);
}
void drawCross (int posCrossX, int posCrossY )
{
  gb.display.setColor(MEDIUMPURPLE);
  gb.display.drawLine(posCrossX + 14, posCrossY + 4, posCrossX + 25, posCrossY + 16);
  gb.display.drawLine(posCrossX + 15, posCrossY + 4, posCrossX + 26, posCrossY + 16);
  gb.display.drawLine(posCrossX + 25, posCrossY + 4, posCrossX + 14, posCrossY + 16);
  gb.display.drawLine(posCrossX + 26, posCrossY + 4, posCrossX + 15, posCrossY + 16);
}

void setup()
{
  // initialize the Gamebuino object
  gb.begin();
}
void displayPlayer ()
{
  gb.display.setColor(ORANGE);
  gb.display.fillRect(0, 0, 10, 8);
  gb.display.setColor(BLACK);
  gb.display.drawChar(4, 2, textNumber[playerOneScore] , 1);
  gb.display.setColor(LIGHTGREEN);
  gb.display.fillRect(70, 0, 80, 8);
  gb.display.setColor(BLACK);
  gb.display.drawChar(74, 2, textNumber[playerTwoScore] , 1);
  if (tiltPlayer == 0)
  {
    gb.display.setColor(RED);
    gb.display.fillRect(0, 8, 10, 52);
    gb.display.setColor(ORANGE);
  }
  else
  {
    gb.display.setColor(DARKGRAY);
    gb.display.fillRect(0, 8, 10, 52);
    gb.display.setColor(GRAY);
  }
  for (int i = 0; i < 8; i++)
  {
    gb.display.drawChar(4, 10 + (i * 6), textPlayer[0][i] , 1);
  }
  if (tiltPlayer == 1)
  {
    gb.display.setColor(GREEN);
    gb.display.fillRect(70, 8, 80, 52);
    gb.display.setColor(LIGHTGREEN);
  }
  else
  {
    gb.display.setColor(DARKGRAY);
    gb.display.fillRect(70, 8, 80, 52);
    gb.display.setColor(GRAY);
  }
  for (int i = 0; i < 8; i++)
  {
    gb.display.drawChar(74, 10 + (i * 6), textPlayer[1][i] , 1);
  }
}


void loop()
{
  while (!gb.update());
  gb.display.clear();
  switch (modeGame)
  {
    case 1:
      GridDraw();
      drawRec(boxPosX, boxPosY);

      displayPlayer ();
      if (gb.buttons.pressed(BUTTON_RIGHT) && boxPosX != 40)
      {
        boxPosX = boxPosX + 20;
        posTab = posTab + 1;
      }
      if (gb.buttons.pressed(BUTTON_LEFT) && boxPosX > 0 )
      {
        boxPosX = boxPosX - 20;
        posTab = posTab - 1;
      }
      if (gb.buttons.pressed(BUTTON_UP) && boxPosY > 0)
      {
        boxPosY = boxPosY - 20;
        posTab = posTab - 3;
      }
      if (gb.buttons.pressed(BUTTON_DOWN) && boxPosY != 40)
      {
        boxPosY = boxPosY + 20;
        posTab = posTab + 3;
      }
      if (gb.buttons.pressed(BUTTON_A))
      {
        if (verifySymbole (grid, 9, posTab))
        {
          if ( tiltPlayer == 0)
          {
            grid[posTab] = 'O';
            tiltPlayer = 1;
            gb.sound.playTick();

          }
          else
          {
            grid[posTab] = 'X';
            tiltPlayer = 0;
            gb.sound.playTick();
          }
        }

      }
      if (gb.buttons.pressed(BUTTON_B))
      {
        grid[posTab] = 'E';
        tiltPlayer = !tiltPlayer;
        gb.sound.play("button_1.wav");
      }
      if (gb.buttons.pressed(BUTTON_MENU))
      {
        iniGrid(grid, 9);
        gb.lights.clear();
        soundTest = 1;
      }
      displayGrid(grid, 9);
      if ( verifyGrid (grid, 9) == 1)
      {
        modeGame = 2;
        tiltPlayer = !tiltPlayer;
        if (tiltPlayer == 0)
        {
          playerOneScore++;
        }
        else
        {
          playerTwoScore++;
        }

      }
      break;
    case 2:

      GridDraw();
      displayPlayer ();
      verifyGrid (grid, 9);
      displayGrid(grid, 9);
      gb.display.setColor(WHITE);
      gb.display.setFontSize(2);
      gb.display.setCursor(10, 15);
      if (tiltPlayer == 0)
      {
        gb.lights.fill(RED);
        gb.display.print("PLAYER 1");
      }
      else
      {
        gb.lights.fill(GREEN);
        gb.display.print("PLAYER 2");
      }

      if (playerOneScore == numberPart || playerTwoScore == numberPart)
      { 
        gb.display.setFontSize(2);
        gb.display.setCursor(15, 35);
        gb.display.print("WINNER");
        if (soundTest == 1 )
        {
          gb.sound.play("win_1.wav");
          soundTest = 0;
        }
      }
      else
      {
        gb.display.setCursor(20, 35);
        gb.display.print("WIN !");
        if (soundTest == 1 )
        {
          gb.sound.play("win_2.wav");
          soundTest = 0;
        }
      }

      if ( gb.buttons.pressed(BUTTON_A)
           || gb.buttons.pressed(BUTTON_B)
           || gb.buttons.pressed(BUTTON_MENU))
      {
        iniGrid(grid, 9);
        gb.lights.clear();
        soundTest = 1;
        modeGame = 1;
        if (playerOneScore == numberPart || playerTwoScore == numberPart)
        {
          playerOneScore = 0;
          playerTwoScore = 0;
        }

      }

      break;
  }
}
