#pragma once
#include <vector>
#include <sstream>
#include "Parameter.h"

using namespace std;


class Predicate
{
    private:
      Parameter schemeName;
      vector<Parameter> parameters;
    public:

      Predicate(){}
      ~Predicate(){}
      

      Predicate(string h){
        Parameter newh = Parameter(h);
        schemeName = newh;
      }

      string getScheme(){
        return schemeName.print();
      }

      int parameterSize(){
        return parameters.size();
      }

      void addNewParameter(Parameter newPara){
        parameters.push_back(newPara);
      }


      string print(){
        string end = schemeName.print() + "(";
        end += parameters[0].print();
        for(int i = 1;i<parameters.size();i++){
          end += ",";
          end += parameters[i].print();
        }
        end += ")";
        return end;
      }

      string predicateValue(int i){
        return parameters[i].print();
      }
};
