#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;


class idList{
    private:
        vector<string> values;
    public:
        idList(){}
        ~idList(){}

        void add(string s){
            values.push_back(s);
        }

        string getID(int x){
            return values[x];
        }
        
        int size(){
            return values.size();
        }

        string print(){
            string end = values[0];
            for(int i = 1;i<values.size();i++){
                end.append(",");
                end.append(values[i]);
            }
            return end;
        }

};