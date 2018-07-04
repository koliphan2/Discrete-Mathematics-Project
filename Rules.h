#pragma once
#include "Rule.h"
#include "TokenClass.h"
#include "Parameter.h"
#include "Predicate.h"

using namespace std;


class Rules{
    private:
        Token t;
        vector<Rule> allRules;

    public:
        Rules(){}
        ~Rules(){}


        void addToken(Token toks){
            t = toks;
        }

        void addRule(Rule r){
            allRules.push_back(r);
        }

        vector<Rule> getRules(){
            return allRules;
        }
        
        string print(){
            string full = "\n";
            full += t.getValue();
            full += "(";
            full += to_string(allRules.size());
            full += "):";
            for(int i = 0;i < allRules.size();i++){
                full += "\n  ";
                full += allRules[i].print();
            }
            return full;
        }

    
};