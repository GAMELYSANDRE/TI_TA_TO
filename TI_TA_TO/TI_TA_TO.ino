/*
   TI_TA_TO.ino

   Copyright 2019 Laurent Meurillon <gamelysandre@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.


*/
#include <Gamebuino-Meta.h>
#define BOXCOLOR_BLACK 0
#define BOXCOLOR_WHITE 7
#define BOXCOLOR_RED 8
#define BOXCOLOR_GREEN 11

// Variables for the grid
// grid ti ta to 60x60 pixels
// E = Empty  O = Circle X = Cross
char grid[9] = {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'};
int gridPos = 4; // initializes in the center of the grid
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


// Variables for the box 20x20 pixels
int boxPosX = 20; // initializes in the center of the grid
int boxPosY = 20; // initializes in the center of the grid
int boxDelay = 0; // flash the box

// Variables for the players
bool playerFlip = 0; // player one = 0 and player two = 1
int playerOneScore = 0;
int playerTwoScore = 0;
const int playerParty = 5; // number of part
const char playerTextNumberParty[7] = {'0', '1', '2', '3', '4', '5'};
const char playerText[3][9] =
{
  "PLAYER 1",
  "PLAYER 2",
  "COMPUTER"
};

// Variable for the game
int gameMode = 1; // menu 1

// Variable for the sound
bool soundNotRepeat = 1;

// defined new color for the GAMEBUINO
Color MEDIUMPURPLE = gb.createColor(147, 112, 219);
Color LIME = gb.createColor(132, 226, 44);

/*---------------------------------------------*/
/*               GRID FUNCTIONS                */
/*---------------------------------------------*/

// initialize the grid
void gridInitialize (char grid[], int gridSize)
{
  for (int i = 0; i < gridSize; i++)
  {
    grid[i] = {'E'};
  }
}

// display the grid with the symbols
void gridDisplay (char grid[], int gridSize)
{
  for (int i = 0; i < gridSize; i++)
  {
    if ( grid[i] == 'O' )
    {
      symbolCircleDraw ((i - (3 * (i / 3))) * 20, (i / 3) * 20 );
    }
    else if ( grid[i] == 'X' )
    {
      symbolCrossDraw ((i - (3 * (i / 3))) * 20, (i / 3) * 20 );
    }
  }
}

// verifies the presence of symbol under the cursor (box)
bool gridVerifySymbol (char grid[], int gridSize, int gridPos)
{
  if (grid[gridPos] == 'E')
  {
    return 1;
  }
  if (grid[gridPos] != 'E')
  {
    return 0;
  }
}

// check if there is a winner
bool gridVerifyWinner (char grid[], int gridSize)
{
  for (int i = 0; i < 2 ; i++)
  {
    char Symbol = 0;
    int boxColor = 0;
    if ( i == 0 )
    {
      Symbol = 'O';
      boxColor = BOXCOLOR_RED;
    }
    else if ( i == 1 )
    {
      Symbol = 'X';
      boxColor = BOXCOLOR_GREEN;
    }
    for (int y = 0; y < 8; y++)
    {
      int firstRec = gridWinning[y][0];
      int secondRec = gridWinning[y][1];
      int threeRec = gridWinning[y][2];
      if (grid[firstRec] == Symbol && grid[secondRec] == Symbol && grid[threeRec] == Symbol)
      {
        boxDraw((firstRec - (3 * (firstRec / 3))) * 20 , (firstRec / 3) * 20  , boxColor);
        boxDraw((secondRec - (3 * (secondRec / 3))) * 20 , (secondRec / 3) * 20, boxColor);
        boxDraw((threeRec - (3 * (threeRec / 3))) * 20 , (threeRec / 3) * 20, boxColor);
        return 1;
      }
    }
  }
  return 0;
}

/*---------------------------------------------*/
/*           GRID FUNCTIONS GRAPHICS           */
/*---------------------------------------------*/

// draw la grille
void gridDraw ()
{
  gb.display.setColor(LIME);
  gb.display.drawLine(30, 0, 30, 60);
  gb.display.drawLine(50, 0, 50, 60);
  gb.display.drawLine(10, 20, 70, 20);
  gb.display.drawLine(10, 40, 70, 40);
}


/*---------------------------------------------*/
/*               BOX FUNCTIONS                */
/*---------------------------------------------*/

// flashes a box
int boxFlash (int boxPosX, int boxPosY, int boxDelay)
{
  boxDelay++;
  int boxColor;
  if (boxDelay < 15)
  {
    boxColor = BOXCOLOR_BLACK;
  }
  else
  {
    boxColor = BOXCOLOR_WHITE;
  }
  if (boxDelay == 30)
  {
    boxDelay = 0;
  }
  boxDraw (boxPosX, boxPosY, boxColor);
  return (boxDelay);
}

// move a box
void boxMove (int *boxPosX, int *boxPosY, int *gridPos, bool *playerFlip)
{
  if (gb.buttons.pressed(BUTTON_RIGHT) && *boxPosX != 40)
  {
    *boxPosX = *boxPosX + 20;
    *gridPos = *gridPos + 1;
  }
  if (gb.buttons.pressed(BUTTON_LEFT) && *boxPosX > 0 )
  {
    *boxPosX = *boxPosX - 20;
    *gridPos = *gridPos - 1;
  }
  if (gb.buttons.pressed(BUTTON_UP) && *boxPosY > 0)
  {
    *boxPosY = *boxPosY - 20;
    *gridPos = *gridPos - 3;
  }
  if (gb.buttons.pressed(BUTTON_DOWN) && *boxPosY != 40)
  {
    *boxPosY = *boxPosY + 20;
    *gridPos = *gridPos + 3;
  }
  if (gb.buttons.pressed(BUTTON_A))
  {
    if (gridVerifySymbol (grid, 9, *gridPos))
    {
      if ( *playerFlip == 0)
      {
        grid[*gridPos] = 'O';
        *playerFlip = 1;
        gb.sound.playTick();

      }
      else
      {
        grid[*gridPos] = 'X';
        *playerFlip = 0;
        gb.sound.playTick();
      }
    }

  }
  if (gb.buttons.pressed(BUTTON_B))
  {
    grid[*gridPos] = 'E';
    *playerFlip = !*playerFlip;
    gb.sound.play("button_1.wav");
  }
  if (gb.buttons.pressed(BUTTON_MENU))
  {
    gridInitialize(grid, 9);
    gb.lights.clear();
    soundNotRepeat = 1;
  }
}

/*---------------------------------------------*/
/*            BOX FUNCTIONS GRAPHICS           */
/*---------------------------------------------*/

// draw a box
void boxDraw (int boxPosX, int boxPosY, int boxColor)
{

  gb.display.setColor(boxColor);
  gb.display.fillRect(boxPosX + 11, boxPosY + 1, 19, 19);
}

/*---------------------------------------------*/
/*              SYMBOLS FUNCTIONS              */
/*---------------------------------------------*/

// draw a circle
void symbolCircleDraw (int posCirx, int posCirY )
{
  gb.display.setColor(MEDIUMPURPLE);
  gb.display.drawCircle(posCirx + 20, posCirY + 10, 6);
  gb.display.drawCircle(posCirx + 20, posCirY + 10, 5);
}

// draw a cross
void symbolCrossDraw (int posCrossX, int posCrossY )
{
  gb.display.setColor(MEDIUMPURPLE);
  gb.display.drawLine(posCrossX + 14, posCrossY + 4, posCrossX + 25, posCrossY + 16);
  gb.display.drawLine(posCrossX + 15, posCrossY + 4, posCrossX + 26, posCrossY + 16);
  gb.display.drawLine(posCrossX + 25, posCrossY + 4, posCrossX + 14, posCrossY + 16);
  gb.display.drawLine(posCrossX + 26, posCrossY + 4, posCrossX + 15, posCrossY + 16);
}

/*---------------------------------------------*/
/*              PLAYERS FUNCTIONS              */
/*---------------------------------------------*/

void playerDisplay ()
{
  gb.display.setColor(ORANGE);
  gb.display.fillRect(0, 0, 10, 8);
  gb.display.setColor(BLACK);
  gb.display.drawChar(4, 2, playerTextNumberParty[playerOneScore] , 1);
  gb.display.setColor(LIGHTGREEN);
  gb.display.fillRect(70, 0, 80, 8);
  gb.display.setColor(BLACK);
  gb.display.drawChar(74, 2, playerTextNumberParty[playerTwoScore] , 1);
  if (playerFlip == 0)
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
    gb.display.drawChar(4, 10 + (i * 6), playerText[0][i] , 1);
  }
  if (playerFlip == 1)
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
    gb.display.drawChar(74, 10 + (i * 6), playerText[1][i] , 1);
  }
}



void setup()
{
  // initialize the Gamebuino object
  gb.begin();
}

void loop()
{
  while (!gb.update());
  gb.display.clear();
  switch (gameMode)
  {
    case 1:
      gridDraw();
      boxDelay = boxFlash (boxPosX, boxPosY, boxDelay);
      playerDisplay ();
      gridDisplay(grid, 9);
      boxMove (&boxPosX, &boxPosY, &gridPos, &playerFlip);
      if ( gridVerifyWinner (grid, 9) == 1)
      {
        playerFlip = !playerFlip;
        if (playerFlip == 0)
        {
          playerOneScore++;
        }
        else
        {
          playerTwoScore++;
        }
        gameMode = 2;
      }
      break;
    case 2:
      gridDraw();
      playerDisplay ();
      gridVerifyWinner (grid, 9);
      gridDisplay(grid, 9);
      gb.display.setColor(WHITE);
      gb.display.setFontSize(2);
      gb.display.setCursor(10, 15);
      if (playerFlip == 0)
      {
        gb.lights.fill(RED);
        gb.display.print("PLAYER 1");
      }
      else
      {
        gb.lights.fill(GREEN);
        gb.display.print("PLAYER 2");
      }

      if (playerOneScore == playerParty || playerTwoScore == playerParty)
      {
        gb.display.setFontSize(2);
        gb.display.setCursor(15, 35);
        gb.display.print("WINNER");
        if (soundNotRepeat == 1 )
        {
          gb.sound.play("win_1.wav");
          soundNotRepeat = 0;
        }
      }
      else
      {
        gb.display.setCursor(20, 35);
        gb.display.print("WIN !");
        if (soundNotRepeat == 1 )
        {
          gb.sound.play("win_2.wav");
          soundNotRepeat = 0;
        }
      }

      if ( gb.buttons.pressed(BUTTON_A)
           || gb.buttons.pressed(BUTTON_B)
           || gb.buttons.pressed(BUTTON_MENU))
      {
        gridInitialize(grid, 9);
        gb.lights.clear();
        soundNotRepeat = 1;
        gameMode = 1;
        if (playerOneScore == playerParty || playerTwoScore == playerParty)
        {
          playerOneScore = 0;
          playerTwoScore = 0;
        }

      }

      break;
  }
}
