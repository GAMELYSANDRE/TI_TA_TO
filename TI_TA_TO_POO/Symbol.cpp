#include "Symbol.h"
#include <Gamebuino-Meta.h>


Symbol::Symbol(int SymbolPosition = 0, int SymbolColor = 5, char SymbolChar = 'O' )
{
  m_SymbolPosGrid = SymbolPosition;
  m_SymbolColor = SymbolColor;
  m_SymbolChar = SymbolChar;
}
void Symbol::Position(int SymbolPosition)
{
  m_SymbolPosGrid = SymbolPosition;
}

void Symbol::Color(int SymbolColor)
{
  m_SymbolColor = SymbolColor;
}

void Symbol::Type(char SymbolChar)
{
  m_SymbolChar = SymbolChar;
}


void Symbol::Draw()
{
  gb.display.setColor(m_SymbolColor);
  switch (m_SymbolChar)
  {
    case 'O':
      gb.display.drawCircle((m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20  + 20, (m_SymbolPosGrid / 3) * 20 + 10, 6);
      gb.display.drawCircle((m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20  + 20, (m_SymbolPosGrid / 3) * 20 + 10, 5);
      break;
    case 'X':
      gb.display.drawLine
      (
        (m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20 + 14, (m_SymbolPosGrid / 3) * 20 + 4,
        (m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20 + 25, (m_SymbolPosGrid / 3) * 20 + 16
      );
      gb.display.drawLine
      (
        (m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20 + 15, (m_SymbolPosGrid / 3) * 20 + 4,
        (m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20 + 26, (m_SymbolPosGrid / 3) * 20 + 16
      );
      gb.display.drawLine
      (
        (m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20 + 25, (m_SymbolPosGrid / 3) * 20 + 4,
        (m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20 + 14, (m_SymbolPosGrid / 3) * 20 + 16
      );
      gb.display.drawLine
      (
        (m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20 + 26, (m_SymbolPosGrid / 3) * 20 + 4,
        (m_SymbolPosGrid - (3 * (m_SymbolPosGrid / 3))) * 20 + 15, (m_SymbolPosGrid / 3) * 20 + 16
      );
      break;
  }
}
