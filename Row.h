#pragma once
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>

using namespace std;

class Row : public vector<string>{
public:
    Row removeAllColumnsBut(vector<int>);
    string print();  
    Row mergeWith(Row r, vector<int> duplicates);
    Row rearrange(vector<int> map, Row);
};

