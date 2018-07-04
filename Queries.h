#pragma once
#include "Query.h"
#include "TokenClass.h"

using namespace std;


class Queries{
    private:
        Token t;
        vector<Query> allQueries;

    public:
        Queries(){}
        ~Queries(){}

        int size(){
            return allQueries.size();
        }

        Query getQuery(int x){
            return allQueries[x];
        }

        void addToken(Token toks){
            t = toks;
        }

        void addQuery(Query q){
            allQueries.push_back(q);
        }
        
        string print(){
            string full = "\n"; 
            full += t.getValue();
            full += "(";
            full += to_string(allQueries.size());
            full += "):";
            for(int i = 0;i < allQueries.size();i++){
                full += "\n  ";
                full += allQueries[i].print();
            }
            return full;
        }

};