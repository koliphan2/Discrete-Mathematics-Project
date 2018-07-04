#include <iostream>
#include "Database.h"
#include "Query.h"

using namespace std;

class Interpreter{
private:
    set<Row> currentRows;

    string name;
    Table finalTable;

    Predicate currentPredicate;
    Rule currentRule;

    //The final result that I'll union with my facts
    Table workingResult;

public:

    Interpreter(Rule currentR){
        currentRule = currentR;
        currentPredicate = currentR.getLeftSide();
        name = currentPredicate.getScheme();   
        Header h = processHead();
        finalTable = Table(name, h);
    }

    Interpreter();
    string getName(){
        return name;
    }

    Table select(Table t){
        t = t.selectionKeys(t, currentPredicate);
        t = t.getMatchingColumnes(t, currentPredicate);
        return t;
    }
    void project(Table t){
        Header h1 = finalTable.getHeader();
        Header h2 = t.getHeader();
        Table newTable = Table(finalTable.getName(), h2);
        vector<int> map = h2.createMapFor(h1);
        vector<int> projectedColumns;
        for(int i = 0;i<h2.size();i++){
            for(int x = 0; x < h1.size();x++){
                if(h2.getHeader(i)==h1.getHeader(x)){  
                    projectedColumns.push_back(i);
                }
            }
        }
        workingResult = t.project(projectedColumns);
        workingResult = t.orderRows(workingResult, map, finalTable);
    }

    void rename(Header originalHeader){
        vector<string> columnNames;
        for(int i = 0;i<originalHeader.size();i++){
            columnNames.push_back(originalHeader.getHeader(i));
        }
        for(int x = 0;x<columnNames.size();x++){
            workingResult.rename(x, columnNames[x]);
        }
    }
    
    Table unite(Table original){
        original = workingResult.unite(original);
        return original;
    }

    Predicate getCurrentPred(){
        return currentPredicate;
    }
    void setUpInterpreter(set<Row> workResult){
        workingResult = Table(name, processBody(0));
        workingResult.setRows(workResult);
    }

    Table join(Table table2, Table table1){
        table1 = table1.join(table2);
        return table1;
    }
    Table getNeededRows(set<Row> table2Rows, int i){
        Table newTable = processBody(i);
        newTable.setRows(table2Rows);
        return newTable;
    }
    Table getResult(){
        return workingResult;
    }
    Table process(Predicate p){
        Header h = Header();
        for(int i = 0;i<p.parameterSize();i++){
          h.addHeader(p.predicateValue(i));
        }
        Table result = Table(name, h);
        return result;
    }
    Header processHead(){
        Table r = process(currentRule.getLeftSide());
        return r.getHeader();
    }
    Header processBody(int i){
        Table r = process(currentRule.at(i));
        return r.getHeader();
    }
};