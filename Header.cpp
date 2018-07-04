#include "Header.h"
#include <iostream>

vector<string> Header::getNames(){
    return columnNames;
}
string Header::getHeader(int x){
    return columnNames[x];
}
string Header::print(){
    stringstream ss = stringstream();
    for(int s = 0; s<columnNames.size(); s++){
        ss << "  " << columnNames[s];
    }
    return ss.str();
}

void Header::addHeader(string x){
    columnNames.push_back(x);
}

Header Header::removeAllOtherColumnsBut(vector<int> columnsToKeep){
    Header tempHeader;
    for(int k = 0;k < columnsToKeep.size();k++){
        for(int s = 0; s<columnNames.size(); s++){
            if(s == columnsToKeep[k]){
                tempHeader.addHeader(columnNames[s]);
            }
            else;
        }    
    }
    return tempHeader;
}

bool Header::contains(string s){
    for(int i = 0;i<columnNames.size();i++){
        if(s == columnNames[i]){
            return true;
        }
    }
    return false;
}
bool Header::compatible(Header h){
    for(int i = 0;i<h.size();i++){
        if(!(contains(h.getHeader(i)))){
            return false;
        }
    }
    return true;
}

vector<int> Header::getMatchingColumns(Header h){
    vector<int> keepers;
    for(int y = 0;y<columnNames.size();y++){
        string attribute = columnNames[y];
        if(!h.contains(attribute)){
            keepers.push_back(y);
        }
    }
    return keepers;
}

Header Header::mergeWith(Header h, vector<int> duplicates){
    Header newHeader = h;
    for(int x = 0;x<duplicates.size();x++){
        newHeader.addHeader(columnNames[duplicates[x]]);
    }
    return newHeader;
}

vector<int> Header::createMapFor(Header h){
    vector<int> locations;
    for(int i = 0;i<columnNames.size();i++){
        for(int x = 0;x<h.size();x++){
            if(columnNames[i]==h.getHeader(x)){
                locations.push_back(x);
            }
        }
    }
    return locations;
}