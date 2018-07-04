#pragma once
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "TokenClass.h"
//#include "Parser.h"

using namespace std;

class Scanner
{
    private:
      vector<Token> toks;
      map <tokenType, string> tokenTypeString;
      int lineNumber;
      ifstream in;
      string file;
    public:
      Scanner(string);
      //Might need to make parse return a vector to get it out of the class.
      vector<Token> parse();
      void scanToken(char);
      void makeToken(tokenType, char);
      void colonDash();
      void isComment(char);
      bool multiComment(string, char);
      void scanString(char);
      void isKeyword(char);
      void endToken();
      string toString();

      string getTypeString(Token t){return tokenTypeString[t.getType()];}
};
