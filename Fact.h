#pragma once
#include "idList.h"
#include "TokenClass.h"
#include "Row.h"

using namespace std;


class Fact{
    private:
        string name;
        idList contents;
        
    public:
        Fact(){}
        ~Fact(){}

        Fact(string id){
            name = id;
            contents = idList();
        }
        
        void makeContent(string ts){
            contents.add(ts);
        }

        idList getContents(){
            return contents;
        }

        Row getRow(){
            Row newRow;
            for(int i = 0; i<contents.size();i++){
                newRow.push_back(contents.getID(i));
            }
            return newRow;
        }

        string getTableName(){
            return name;
        }

        string print(){
            string full = name + "(";
            full.append(contents.print());
            full.append(").");
            return full;
        }

};