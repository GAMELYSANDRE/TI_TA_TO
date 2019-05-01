#ifndef __PLAYER__
#define __PLAYER__
enum Position
{
  LEFT = 1,
  RIGHT = 71
};

class Player
{

  public:
    Player( Position PlayerPosition, const char PlayerName[] );
    void Score(int Score);// US: change color FR: change couleur
    int Score();
    void Draw();
    void State(bool PlayerState);
    void Color( int PlayerColor);// US: change color FR: change couleur
    int Color(); // US: return color FR: renvoi couleur

  private:
    Position m_PlayerPosScreen;
    int m_PlayerScore;
    bool m_PlayerState;
    char m_PlayerName[9];
    int m_PlayerColor;
};

#endif
