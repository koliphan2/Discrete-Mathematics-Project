#pragma once
#include <sstream>
#include "Fact.h"
#include "TokenClass.h"
#include "idList.h"

using namespace std;

class Facts{
private:
    Token t;
    vector<Fact> allFacts;
public:
    Facts(){}
    ~Facts(){}

    void addToken(Token toks){
        t = toks;
    }

    void addFact(Fact f){
        allFacts.push_back(f);
    }

    int size(){
        return allFacts.size();
    }

    Fact getFact(int x){
        return allFacts[x];
    }

    string print(){
        string full = "\n";
        full += t.getValue();
        full += "(";
        full += to_string(allFacts.size());
        full += "):";
        for(int i = 0;i < allFacts.size();i++){
            full += "\n  ";
            full += allFacts[i].print();
        }
        return full;
    }

};