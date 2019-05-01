#include "Box.h"
#include <Gamebuino-Meta.h>


Box::Box(int BoxPosition = 0, int BoxColor = 5) : m_BoxError(0)
{
  m_BoxColor = BoxColor;
  m_BoxPosGrid = BoxPosition;
}

void Box::Color(int BoxColor)
{
  m_BoxColor = BoxColor;
}
int Box::Color()
{
  return (m_BoxColor);
}


void Box::Position(int BoxPosition)
{
  m_BoxPosGrid = BoxPosition;
}

void Box::Draw()
{
  // control position box
  if (!(m_BoxPosGrid <= 8 && m_BoxPosGrid >= 0))
  {
    m_BoxError = 1;
  }
  // verif error
  if (m_BoxError == 1 )
  {
    gb.display.setColor(RED);
    gb.display.print("error out of tolerances");
  }
  else
  {
    gb.display.setColor(m_BoxColor);
    gb.display.drawRect((m_BoxPosGrid - (3 * (m_BoxPosGrid / 3))) * 20 + 11 , (m_BoxPosGrid / 3) * 20 + 1, 19, 19);
    gb.display.drawRect((m_BoxPosGrid - (3 * (m_BoxPosGrid / 3))) * 20 + 10 , (m_BoxPosGrid / 3) * 20 , 21, 21);
  }
}
