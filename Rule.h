#pragma once
#include "Predicate.h"

using namespace std;


class Rule
{
    private:
      Predicate leftSide;
      vector<Predicate> rightSide;
      bool selfReliant;
    public:
      Rule(){
      }
      ~Rule(){}

      Rule(Predicate x){
        leftSide = x;
        selfReliant = false;
      }


      Predicate getLeftSide(){
        return leftSide;
      }

      bool isSelfReliant(){
        return selfReliant;
      }
      
      Predicate at(int index)
      {
        return rightSide[index];
      }

      vector<Predicate> getRightSide(){
        return rightSide;
      }

      int size(){
        return rightSide.size();
      }

      void addRightSide(Predicate newPred){
        rightSide.push_back(newPred);
        if(newPred.getScheme() == leftSide.getScheme()){
          selfReliant = true;
        }
      }

      string print(){
        stringstream ss;
        int i = 0;
        ss << leftSide.print() <<  " :- ";
        ss << rightSide[0].print();
        for(i ++; i < rightSide.size();i++){
          if(rightSide[i].print() == "(" && rightSide[i+1].print() == "("){
            ss << "INSIDE THE LOOP" << endl;
          }
          else {ss<<",";}
          ss << rightSide[i].print();
        }
        ss << ".";
        return ss.str();
      }
};
