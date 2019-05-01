#ifndef __GRID__
#define __GRID__


#include "Box.h"
#include "Symbol.h"
#include "Player.h"

class Grid
{
  public:

    Grid(); // Constructor
    ~Grid(); // Destructor

    void Initialize ();
    char getGrid (int nbrBox ) const;
    int getGridWin (int line, int column ) const;
    void Draw () const;
    void MoveBox();
    void Button();
    int VerifyWinner ();
    void Winner();

  private:

    char m_grid[9];
    int m_gridPos;
    bool m_gridPlayer;
    int m_gridWinning[8][3];
    int m_gridPlayerWinner;
    int m_gridParty;
    bool m_soundNotRepeat;
    bool gridVerifySymbol ();

    Box *m_boxCursor;
    Box *m_boxFirstSymbol;
    Box *m_boxSecondSymbol;
    Box *m_boxThreeSymbol;
    Symbol *m_symbol;
    Player *m_playerOne;
    Player *m_playerTwo;

};

#endif
