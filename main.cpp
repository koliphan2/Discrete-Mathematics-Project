#include <fstream>
#include <iomanip>
#include "TokenClass.h"
#include "Scanner.h"
#include "Parser.h"
#include "Table.h"
#include "Database.h"


int main(int argc, char* argv[]){
  cout.flush();
  
  string fileName = argv[1];
  Scanner scan(fileName);

  //Lab 1 (Tokenizer)
  vector<Token> toks = scan.parse();
  Parser parse(toks);
  //cout << scan.toString();

  //Lab 2 (Parsing and Syntax)
  if(toks.size() == 1) return 0;
  parse.run();
  //cout << parse.print();

  //Lab 3 (Interpret Facts, Schemes and Queries)
  Database Data = Database();
  Data.makeDatabase(parse.getSchemes(),parse.getFacts(),parse.getRules(),parse.getQueries());

  //Lab 4 (Interpret Rules and add to facts)
  cout << Data.printEfficiantResults();
  return 0;
}
