#pragma once
#include "TokenClass.h"

using namespace std;


class Parameter
{
    private:
      string paraIdentity;
      string InnerExpression;
    public:
      Parameter(){}
      ~Parameter(){}

      Parameter(string in){
        paraIdentity = in;
        InnerExpression = "";
      }

      void add(string x){
        paraIdentity += x;
        InnerExpression += x;
      }

      void clearString(){
        paraIdentity = "";
      }

      void clearExpression(){
        InnerExpression = "";
      }

      string print(){
        return paraIdentity;
      }

      string printEx(){
        return InnerExpression;
      }

      bool checkOperator(tokenType t){
        if(t == ADD){
          add("+");
          return true;
        }
        else if (t == MULTIPLY){
          add("*");
          return true;
        }
        else return false;
      }
};

