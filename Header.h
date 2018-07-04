#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Header{
private:
    vector<string> columnNames;
public:
    int size(){return columnNames.size();}
    void addHeader(string x);
    string getHeader(int x);
    vector<string> getNames();
    string print();
    Header removeAllOtherColumnsBut(vector<int>);
    vector<int> getMatchingColumns(Header);
    Header mergeWith(Header, vector<int>);
    bool contains(string);
    vector<int> createMapFor(Header h);
    bool compatible(Header);
};
