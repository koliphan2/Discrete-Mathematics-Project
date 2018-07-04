#include "Table.h"
#include <iostream>

Table::Table(){}
Table::Table(string n, Header h){
    name = n;
    header = h;
 }
 Table::Table(Header h){
     header = h;
 }
void Table::setHeader(Header h){
    header = h;
}
void Table::setName(string n, Header h){
    name = n;
    header = h;
 }

string Table::print(){
    stringstream ss = stringstream();
    ss << name <<'\n' << header.print() << '\n';
    for(Row r : rows){
        ss << r.print();
        ss << '\n';
    }
    return ss.str();
 }

string Table::printAnswer(Predicate query){
    stringstream ss = stringstream();
    if(rows.size() == 0){
        ss << " No";
    }
    else {
        ss << " Yes";
        ss << "(" << rows.size() << ")";
        bool oneAnswer = questionType(query);
        if(oneAnswer){
            return ss.str();
        }
        else{
            ss << printMultiAnswers();
        }
    }
    return ss.str();
 }
string Table::printMultiAnswers(){
    stringstream ss = stringstream();
    string extra;
    int head = 0;
    for(Row r : rows){
        ss << "\n  " << header.getNames()[head] << "=";
        ss << r[head];
        for(int heads = head+1;heads<header.getNames().size();heads++){
            ss << ", ";
            ss << header.getNames()[heads] << "=";
            ss << r[heads];
        }
    }
    return ss.str();
 }

//Returns true if there is only one answer
bool Table::questionType(Predicate query){
    bool oneAnswer = true;
    for(int i = 0;i<query.parameterSize();i++){
        if(query.predicateValue(i).at(0) != '\''){
            oneAnswer = false;
        }
    }
    return oneAnswer;
 }

void Table::addRow(Row row){
    rows.insert(row);
 }

void Table::setRows(set<Row> s){
     rows = s;
 }
set<Row> Table::getRows(){
     return rows;
 }
int Table::getRowCount(){
    return rows.size();
 }

void Table::addHeader(string s){
    header.addHeader(s);
 }

Header Table::getHeader(){
    return header;
 }

//Know which ones to select(int, string)
Table Table::selectionKeys(Table t, Predicate query){
    for(int i = 0; i < query.parameterSize();i++){
        if(query.predicateValue(i).at(0) == '\''){
          t = t.select(i, query.predicateValue(i));
        }
    }
    return t;
 }

//Know which ones to select(int,int)
Table Table::getMatchingColumnes(Table t, Predicate query){
    for(int x = 0; x < query.parameterSize();x++){
        for(int y = x+1; y < query.parameterSize();y++){
            if(query.predicateValue(x)==query.predicateValue(y)){
                t = t.select(x,y);
            }
        }
    }
    return t;
 }

Table Table::select(int row1, int row2){
    Table newT;
    newT.setName(name, header);
    for(Row r : rows){
        if(r[row1] == r[row2]){
            Row newR = r;
          newT.addRow(newR);
        }
    }
    return newT;
    //Returns the table with only the 'facts' that match in
    //Rows entered in.
  }

Table Table::select(int column, string value){
    Table newT;
    newT.setName(name, header);
    for(Row r : rows){
      if(r[column] == value){
          Row newR = r;
        newT.addRow(newR);
      }
      else;
    }
    return newT;
    //Returns the Table fact row set with only the 
    //facts that match the value in that column.
 }

//Know which columns to project
Table Table::getColumnesToKeep(Table t, Predicate query){
    //Make sure there is only one copy of each column
    vector<int> ColumnsToKeep;
    vector<string> columnNames;
    for(int i = 0;i<query.parameterSize();i++){
        bool notFound = true;
        if(query.predicateValue(i).at(0) != '\''){
            for(int names = 0;names < columnNames.size();names++){
                if(columnNames[names]== query.predicateValue(i)){
                    notFound = false;   
                }
            }
            if(notFound){
                columnNames.push_back(query.predicateValue(i));
                ColumnsToKeep.push_back(i);
            }
        }
    }

    //Project it
    if(ColumnsToKeep.size() > 0){
        t = t.project(ColumnsToKeep);
    }

    //Rename everything
    for(int x = 0;x<columnNames.size();x++){
        t.rename(x, columnNames[x]);
    }
    return t;
 }
Table Table::project(vector<int> columns){
    Table newT;
    newT.setName(name, header);
    newT.setName(name, newT.getHeader().removeAllOtherColumnsBut(columns));
    for(Row r : rows){
        Row newR = r;
        newR = newR.removeAllColumnsBut(columns);
        newT.addRow(newR);
    }
    return newT;
 }
  
void Table::rename(int x, string n){
    Header tempHeader;
    int count = 0;
    for(string s : header.getNames()){
        if(x == count){
            tempHeader.addHeader(n);
        }
        else {
            tempHeader.addHeader(s);
        }
        count++;
    }
    header = tempHeader;
 }



Table Table::join(Table table2){
     Header h2 = table2.getHeader();
     vector <int> columnsToKeep = header.getMatchingColumns(h2);
     Header newHeader = header.mergeWith(h2, columnsToKeep);
     //Name is going to be the headPredicate rule name
     Table newTable = Table(newHeader);
     for(Row r1 : rows){
         for(Row r2 : table2.getRows()){
             if(joinable(r1, r2, header, h2)){
                 Row newRow = r1.mergeWith(r2,columnsToKeep);
                 newTable.addRow(newRow);
             }
         }
     }
     return newTable;
 }

bool Table::joinable(Row &r1, Row &r2, Header &h1, Header &h2){
    for(int one = 0;one < r1.size();one++){
        for(int two = 0;two < r2.size();two++){
            if((h1.getHeader(one) == h2.getHeader(two))){
                //This keeps track of which value locations are under the same header
                sameHeaderLocationsR1.push_back(one);
                if(r1[one]!= r2[two]){
                    return false;
                }
            }   
        }
    }
    return true;
 }

Table Table::unite(Table table){
    Table newTable = Table(name, header);
    newTable.setRows(rows);
    if(header.compatible(table.getHeader())){
        vector<int> newOrderingMap = header.createMapFor(table.getHeader());
        newTable = orderRows(table, newOrderingMap, newTable);
    }
    return newTable;
 }

 Table Table::orderRows(Table table, vector<int> map, Table newTable){
    for(Row r : table.getRows()){
        Row rearrangedRow = r.rearrange(map, r);
        newTable.addRow(rearrangedRow);
    }
    return newTable;
 }
