#pragma once
#include <sstream>
#include <iostream>
#include <set>
#include <map>
#include "Table.h"
#include "Facts.h"
#include "Schemes.h"
#include "Queries.h"
#include "Rules.h"
#include "Interpreter.h"
#include "Graph.h"

using namespace std;


class Database{
private:
    map<string,Table> allTables;
    Queries allQueries;
    Rules allRules;

public:
    Database();
    void makeDatabase(Schemes, Facts, Rules, Queries);
    void addAllTables(Schemes, Facts);
    void addTable(Scheme scheme);
    void addRowToTable(Fact fact);
    void addQueries(Queries q);

    string print();
    Table getTable(string);
    Table execute(Query query);
    string solveAllQueries();
    Graph getDependancyGraph();

    int interpretRules(vector<Rule>&);
    bool interpret(Rule&);
    vector<vector<Rule>> getRuleForest(vector<vector<int>>&);
    string printEfficiantResults();
};

