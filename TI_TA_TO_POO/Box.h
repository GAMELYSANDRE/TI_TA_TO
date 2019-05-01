#ifndef __BOX__
#define __BOX__
class Box
{
  public:

    Box(int BoxPosition, int BoxColor); // Constructor
    void Color(int BoxColor); // US: change color FR: change couleur
    int Color(); // US: return color FR: renvoi couleur
    void Position(int BoxPosition);
    void Draw();

  private:

    int m_BoxPosGrid;
    int m_BoxColor;
    int m_BoxError;

};

#endif
