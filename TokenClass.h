#pragma once
#include <string>
#include <iostream>

using namespace std;

enum tokenType{
  COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON,
  COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES,
  ID, STRING, COMMENT, WHITESPACE, UNDEFINED, END
};

class Token
{
    private:
      tokenType type;
      string value;
      int line;
    public:
      Token(){}
      ~Token(){}
      Token(tokenType, string, int);
      tokenType getType(){return type;}
      string getValue(){return value;}
      int getLn(){return line;}
};
