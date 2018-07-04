#pragma once
#include "Predicate.h"

using namespace std;


class Query
{
    private:
      string schemeName;
      Predicate question;
    public:
      Query(){
      }
      ~Query(){}

      Query(Predicate x){
        question = x;
        schemeName = x.getScheme();
      }

      //Maybe put these in predicate?



      Predicate getQuestion(){
        return question;
      }

      string getScheme(){
          return schemeName;
      }

      string print(){
        string printer = question.print();
        printer += "?";
        return printer;
      }
};
