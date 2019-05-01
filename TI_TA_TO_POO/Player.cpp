#include "Player.h"
#include <Gamebuino-Meta.h>


Player::Player( Position PlayerPosition, const char playerName[] ) : m_PlayerPosScreen(LEFT), m_PlayerScore(0), m_PlayerState(0)
{
  strcpy(m_PlayerName, playerName);
  m_PlayerPosScreen = PlayerPosition;
}

void Player::Score( int Score)
{
  m_PlayerScore = Score;
}

int Player::Score()
{
  return(m_PlayerScore);
}

void Player::Color( int PlayerColor)
{
  m_PlayerColor = PlayerColor;
}

int Player::Color()
{
  return(m_PlayerColor);
}

void Player::Draw()
{
  // display score
  gb.display.setColor(ORANGE);
  gb.display.fillRect(m_PlayerPosScreen, 1, m_PlayerPosScreen + 9, 8);
  gb.display.setColor(BLACK);
  gb.display.drawChar(m_PlayerPosScreen + 3, 2, m_PlayerScore + '0', 1);
  // display text
  if ( m_PlayerState == 0)
  {
    gb.display.setColor(DARKGRAY);
    gb.display.fillRect(m_PlayerPosScreen, 8, m_PlayerPosScreen + 9, 52);
    gb.display.setColor(GRAY);
  }
  else
  {
    gb.display.setColor(m_PlayerColor);
    gb.display.fillRect(m_PlayerPosScreen, 8, m_PlayerPosScreen + 9, 52);
    gb.display.setColor(ORANGE);
  }
  for (int i = 0; i < 8; i++)
  {
    gb.display.drawChar(m_PlayerPosScreen + 3, 10 + (i * 6), m_PlayerName[i] , 1);
  }
}

void Player::State(bool PlayerState)
{
  m_PlayerState = PlayerState;
}
