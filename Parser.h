#pragma once
#include <fstream>
#include "Scanner.h"
#include "TokenClass.h"
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"
#include "Domain.h"

using namespace std;

class Parser
{
    private:
      vector<Token> toks;
      vector<Token> currentT;
      Schemes sList;
      Facts fList;
      Rules rList;
      Queries qList;
      Domain domains;
      map <tokenType, string> tokenTypeString;
      tokenType token;
      string tokenValue;
      int count;

    public:
      Parser(vector<Token>);
      tokenType getToken();
      string getValue();
      string print();
      void increment();
      void match(tokenType);
      void run();
      void error();
      void splitTokens(tokenType);
      void datalogProgram();
      void scheme();
      void fact();
      void rule();
      void query();
      Predicate headPredicate();
      Predicate normalPredicate(char);
      Parameter makeParameter();
      void makeDomain();
      string printDomain();

      Schemes getSchemes(){
        return sList;
      }
      Facts getFacts(){
        return fList;
      }
      Queries getQueries(){
        return qList;
      }
      Rules getRules(){
        return rList;
      }

    };