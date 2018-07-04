#pragma once
#include <set>
#include "idList.h"
#include <sstream>

using namespace std;


class Domain{
private:
    set<string> allDomains;

public:
    Domain(){}

    void addDomain(string s){
        allDomains.insert(s);
    }

    string printWhole(){
        stringstream ss = stringstream();
        ss << "\nDomains(";
        ss << allDomains.size() << "):";
        ss << print();
        return ss.str();
    }
    string print(){
        stringstream result = stringstream();
        for(string s : allDomains){
            result << "\n";
            result << s;
        }
        return result.str();
    }
};