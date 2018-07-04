#pragma once
#include "Scheme.h"
#include "TokenClass.h"
#include "idList.h"

using namespace std;


class Schemes{
    private:
        Token t;
        vector<Scheme> allSchemes;

    public:
        Schemes(){}
        ~Schemes(){}

        void addToken(Token toks){
            t = toks;
        }

        void addScheme(Scheme s){
            allSchemes.push_back(s);
        }

        Scheme getScheme(int x){
            return allSchemes[x];
        }

        int size(){
            return allSchemes.size();
        }

        vector<Scheme> getSchemes(){
            return allSchemes;
        }
        
        string print(){
            string full = t.getValue();
            full += "(";
            full += to_string(allSchemes.size());
            full += "):";
            for(int i = 0;i < allSchemes.size();i++){
                full += "\n  ";
                full += allSchemes[i].print();
            }
            return full;
        }
};