#pragma once
#include "idList.h"
#include "TokenClass.h"
#include "Header.h"

using namespace std;


class Scheme{
    private:
        string name;
        idList contents;
        
    public:
        Scheme(){}
        ~Scheme(){}

        Scheme(string id){
            name = id;
            contents = idList();
        }
        Scheme(vector<string> info){
            name = info[0];
            info.erase(info.begin());
            for(int i = 0;i<info.size();i++){
                contents.add(info[i]);
            }
        }
        void makeContent(string ts){
            contents.add(ts);
        }
        idList getContents(){
            return contents;
        }
        Header getHeaders(){
            Header newHeader;
            for(int i = 0; i<contents.size();i++){
                newHeader.addHeader(contents.getID(i));
            }
            return newHeader;

        }
        string getTableName(){
            return name;
        }
        string print(){
            string full = name + "(";
            full.append(contents.print());
            full.append(")");
            return full;
        }

};
