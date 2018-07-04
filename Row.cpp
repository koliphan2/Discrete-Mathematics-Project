#include "Row.h"

Row Row::removeAllColumnsBut(vector<int> columns){
    Row tempRow;
    for(int r = 0;r < this->size();r++){
        for(int c = 0;c < columns.size();c++){
            if(r == columns[c]){
                tempRow.push_back(this->at(r));
            }
            else;
        }
    }
    return tempRow;
}

string Row::print(){
    stringstream ss = stringstream();
    for(int v = 0;v < this->size();v++){
        ss << "  " << this->at(v);
    }
    return ss.str();
}

Row Row::mergeWith(Row r, vector<int> duplicates){
    Row newRow = r;
    for(int x = 0;x<duplicates.size();x++){
        newRow.push_back(this->at(duplicates[x]));
    }
    return newRow;
}

Row Row::rearrange(vector<int> map, Row r){
    Row newRow = r;
    for(int i = 0; i < map.size();i++){
        newRow[i] = this->at(map[i]);
    }
    return newRow;
 }