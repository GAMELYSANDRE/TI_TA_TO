/*
  TI_TA_TO_POO.ino

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
#include "Grid.h"

Grid Game;

int Mode = 1;
int playerWin = 0;

void setup()
{
  // initialize the Gamebuino object
  gb.begin();
  Game.Initialize(); // clean grid
}



void loop()
{
  while (!gb.update());
  gb.display.clear();
  switch (Mode)
  {
    case 1:
      // activates movements and actions
      Game.Button();
      // draw the game
      Game.Draw();
      Game.MoveBox();
      playerWin = Game.VerifyWinner();
      if (playerWin == 1 or playerWin == 2 )
      {
        Mode = 2;
      }

      break;
    case 2:
      // draw the game
      Game.Draw();
      Game.Winner();
      if (gb.buttons.pressed(BUTTON_B) )
      {
        Game.Initialize();
        Mode = 1;
      }
      break;
  }
}
