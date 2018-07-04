#pragma once
#include "Header.h"
#include "Row.h"
#include "Predicate.h"

using namespace std;

class Table{
private:
    string name;
    Header header;
    set<Row> rows;
    vector<int> sameHeaderLocationsR1;
public:
    Table();
    Table(string, Header);
    Table(Header);
    ~Table(){}

    string print();
    string printAnswer(Predicate query);
    string printMultiAnswers();

    //Does the question have more than one answer?
    bool questionType(Predicate query);

    void addRow(Row row);
    void setRows(set<Row>);
    set<Row> getRows();
    int getRowCount();
    void setName(string, Header);
    void setName(string s){
        name = s;
    }
    void setHeader(Header);

    Header getHeader();
    void addHeader(string);
    string getName(){
        return name;
    }


    Table selectionKeys(Table t, Predicate query);
    Table getMatchingColumnes(Table t, Predicate query);
    Table getColumnesToKeep(Table t, Predicate query);
    Table select(int row1, int row2);
    Table select(int column, string value);
    Table project(vector<int> columns);
    void rename(int, string);

    Table join(Table);
    bool joinable(Row&, Row&, Header&, Header&);
    Table unite(Table);
    Table orderRows(Table, vector<int>, Table);

};