#include "Database.h"

using namespace std;

Database::Database(){
}
void Database::makeDatabase(Schemes allS, Facts allF, Rules allR, Queries allQ){
    //Set Schemes and Facts
    addAllTables(allS, allF);
    //Set Queries
    allQueries = allQ;
    allRules = allR;
}
void Database::addAllTables(Schemes allSchemes, Facts allFacts){
    //Schemes
    for(int s = 0;s < allSchemes.size();s++){
        addTable(allSchemes.getScheme(s));
    }

    //Facts
    for(int f = 0; f < allFacts.size();f++){
        addRowToTable(allFacts.getFact(f));
    }
}
void Database::addTable(Scheme scheme){
    Header newHeader = scheme.getHeaders();
    string newName = scheme.getTableName();
    Table newTable = Table(newName,newHeader);
    allTables.insert(pair<string,Table>(newName, newTable));
}
void Database::addRowToTable(Fact fact){
    string newName = fact.getTableName();
    Row r = fact.getRow();
    allTables[newName].addRow(r);
}
string Database::print(){
    stringstream ss = stringstream();
    for(auto t : allTables){
        ss << t.second.print() << endl;
    }
    ss << allQueries.print() << endl;
    return ss.str();
}
Table Database::getTable(string x){
    Table newTable = Table();
    for(auto t: allTables){
        if(x == t.first){
            newTable = t.second;
        }
    }
    return newTable;
}
Table Database::execute(Query query){
    string tableName = query.getScheme();
    Table currentT = allTables[tableName];
    stringstream ss = stringstream();
    
    //Select all set values
    currentT = currentT.selectionKeys(currentT, query.getQuestion());
    
    //Select same column values
    currentT = currentT.getMatchingColumnes(currentT, query.getQuestion());   
    
    //Project needed columnes and rename them.
    currentT = currentT.getColumnesToKeep(currentT, query.getQuestion()); 
    ss << currentT.printAnswer(query.getQuestion()) << endl;
    return currentT;
}
string Database::solveAllQueries(){
    stringstream ss = stringstream();
    Table currentT;
    for(int q = 0; q < allQueries.size();q++){
        Query query = allQueries.getQuery(q);
        ss << allQueries.getQuery(q).print();
        currentT = execute(query);
        ss << currentT.printAnswer(query.getQuestion()) << endl;
    }
    return ss.str();
}

string Database::printEfficiantResults(){
    stringstream ss = stringstream();

    ss << "Dependency Graph" << endl;
    Graph g = getDependancyGraph();
    ss <<  g.print() << endl;


    ss << "Rule Evaluation" << endl;
    vector<vector<int>> numberForest = g.sortGraphCompletely(g);
    vector<vector<Rule>> ruleForest = getRuleForest(numberForest);
    int ruleCount = 0;

    for(int i = 0;i <ruleForest.size(); i++){
        ruleCount = interpretRules(ruleForest[i]);
        ss << ruleCount << " passes: ";
        for(int x = 0;x < numberForest[i].size();x++){
           ss << "R" << numberForest[i][x] << ",";
        }
        ss.seekp(-1, ss.end);
        ss << endl;
    }
    ss << endl;
    ss << "Query Evaluation" << endl;
    ss << solveAllQueries();
    return ss.str();  
}

int Database::interpretRules(vector<Rule>& rules){
    bool factsAdded;
    int numOfPasses = 0;
    do{
        numOfPasses++;
        factsAdded = false;
        bool tempBool;
        for(int i = 0;i<rules.size();i++){ 
            //Check if rule depends on itself or others 
            if(rules[i].isSelfReliant() || rules.size() > 1){
                tempBool = interpret(rules[i]);
                if(tempBool){
                factsAdded = true;
                }
            }
            else {
                interpret(rules[i]);
            }
        }
        
    }
    while(factsAdded);
    return numOfPasses;
}

bool Database::interpret(Rule& currentRule){

    Interpreter readRules = Interpreter(currentRule);
    Query halfOne = Query(currentRule.at(0));
    Table halfOneTable = execute(halfOne);
    
    //Join all parameters
    for(int i = 1;i<currentRule.getRightSide().size();i++){
        Query halfTwo = Query(currentRule.at(i));
        Table halfTwoTable = execute(halfTwo);
        halfOneTable = halfTwoTable.join(halfOneTable);
    }

    //Select
    Table finalTable = readRules.select(halfOneTable);

    //Project
    readRules.project(finalTable);

    //Rename
    Table original = getTable(readRules.getName());
    readRules.rename(original.getHeader());

    //Unite
    int originalFactNumber = original.getRowCount();
    Table result = readRules.unite(original);\
    string finalName = currentRule.getLeftSide().getScheme();
    allTables.at(finalName) = result;

    //Check if facts were added
    int addedFacts = result.getRowCount();
    if (addedFacts > originalFactNumber){
        return true;
    }
    else{
        return false;
    }
}

Graph Database::getDependancyGraph(){
    Graph g;
    g.makeGraph(allRules.getRules());
    return g;
}

vector<vector<Rule>> Database::getRuleForest(vector<vector<int>>& graphVector){
    //Turn forest of Ints into forest of Rules
    vector<vector<Rule>> ruleVector;
    vector<Rule> tempVector;
    for(int i = 0;i<graphVector.size();i++){
        vector<Rule> tempVector;
        for(int k = 0;k<graphVector[i].size();k++){
            int ruleIndex = graphVector[i][k];
            Rule tempRule = allRules.getRules()[ruleIndex];
            tempVector.push_back(tempRule); 
        }
        ruleVector.push_back(tempVector);
    }
    return ruleVector;
}
