#ifndef __SYMBOL__
#define __SYMBOL__

class Symbol
{
  public:
  
    Symbol(int SymbolPosition, int SymbolColor, char SymbolChar); // Constructor
    void Position(int SymbolPosition);
    void Color(int SymbolColor);
    void Type(char SymbolChar);
    void Draw();

  private:
  
    int m_SymbolPosGrid;
    int m_SymbolColor;
    char m_SymbolChar;

};

#endif
