#include "Parser.h"

Parser::Parser(vector<Token> token_Vec){
  count = 0;
  toks = token_Vec;
  sList = Schemes();
  rList = Rules();
  //qList = Queries();
  domains = Domain();

  //Setting up the map
  tokenTypeString[COMMA] = "COMMA";
  tokenTypeString[PERIOD] = "PERIOD";
  tokenTypeString[Q_MARK] = "Q_MARK";
  tokenTypeString[LEFT_PAREN] = "LEFT_PAREN";
  tokenTypeString[RIGHT_PAREN] = "RIGHT_PAREN";
  tokenTypeString[COLON] = "COLON";
  tokenTypeString[COLON_DASH] = "COLON_DASH";
  tokenTypeString[MULTIPLY] = "MULTIPLY";
  tokenTypeString[ADD] = "ADD";
  tokenTypeString[SCHEMES] = "SCHEMES";
  tokenTypeString[FACTS] = "FACTS";
  tokenTypeString[RULES] = "RULES";
  tokenTypeString[QUERIES] = "QUERIES";
  tokenTypeString[ID] = "ID";
  tokenTypeString[STRING] = "STRING";
  tokenTypeString[COMMENT] = "COMMENT";
  tokenTypeString[WHITESPACE] = "WHITESPACE";
  tokenTypeString[UNDEFINED] = "UNDEFINED";
  tokenTypeString[END] = "EOF";
}

tokenType Parser::getToken(){
  return token;
}

void Parser::increment(){
  count++;
  token = toks[count].getType();
  tokenValue = toks[count].getValue();
}

string Parser::getValue(){
  return tokenValue;
}

void Parser::match(tokenType t){
  if(token == t){
    increment();
  }
  else {
    error();
  }
  //make sure to skip over comments
  while(token == COMMENT){
    increment();
  }
}

void Parser::run(){
  token = toks[count].getType();
  tokenValue = toks[count].getValue();
  while(token == COMMENT){
    increment();
    
  }
  try{
    datalogProgram();
    if(token != END){
      error();
    }
  }
  catch (tokenType t){
    cout << "Failure!" << endl;
    cout << "  (" << tokenTypeString.at(toks[count].getType());
    cout << ",\"" << toks[count].getValue() << "\"," << toks[count].getLn() << ")" << endl; 
    return;
  }
}

string Parser::print(){
  stringstream ss = stringstream();
  ss << "Success!" << endl << sList.print();
  ss << fList.print() << rList.print() << qList.print() <<domains.printWhole() << endl;
  return ss.str();
}

void Parser::error(){
  throw token;
}

void Parser::datalogProgram(){
  scheme();

  fact();

  rule();

  query();
}

void Parser::scheme(){
  //Make Scheme section
  sList.addToken(toks[count]);
  //sList.parseScemes(this, currentT)
  match(SCHEMES);
  match(COLON);
  
  //Get all of the schemes properly formatted
  do{
    //scheme name
    Scheme newScheme = Scheme(tokenValue);
    match(ID);
    //contents of scheme
    match(LEFT_PAREN);
    newScheme.makeContent(tokenValue);
    match(ID);
    while(token == COMMA){
      match(COMMA);
      newScheme.makeContent(tokenValue);
      match(ID);
    }
    match(RIGHT_PAREN);
    sList.addScheme(newScheme);
  }
  while(token != FACTS);
}

void Parser::fact(){
  fList.addToken(toks[count]);
  match(FACTS);
  match(COLON);
  
  //Get all of the facts
  while(token != RULES){
    //Fact name
    Fact newFact = Fact(tokenValue);
    match(ID);
    //contents of fact
    match(LEFT_PAREN);
    newFact.makeContent(tokenValue);
    domains.addDomain(tokenValue);
    match(STRING);
    while(token == COMMA){
      match(COMMA);
      newFact.makeContent(tokenValue);
      domains.addDomain(tokenValue);
      match(STRING);
    }
    match(RIGHT_PAREN);
    match(PERIOD);
    fList.addFact(newFact);
  }
}

void Parser::rule(){
  rList.addToken(toks[count]);
  match(RULES);
  match(COLON);

  //Get all rules.
  while(token != QUERIES){
    Rule newRule = Rule(headPredicate());
    match(COLON_DASH);
    while(token != PERIOD){
      newRule.addRightSide(normalPredicate('r'));
    }
    rList.addRule(newRule);
    match(PERIOD); 
  }
}

void Parser::query(){
  qList.addToken(toks[count]);
  match(QUERIES);
  match(COLON);
  do{
    Query newQuery = Query(normalPredicate('q'));
    match(Q_MARK);
    qList.addQuery(newQuery);
  }
  while(token != END);
}

Predicate Parser::headPredicate(){
  Predicate p  = Predicate(tokenValue);
  match(ID);
  match(LEFT_PAREN);
  Parameter tempPara = Parameter(toks[count].getValue());
  p.addNewParameter(tempPara);
  match(ID);
  while(token == COMMA){
    match(COMMA);
    tempPara = Parameter(toks[count].getValue());
    p.addNewParameter(tempPara);
    match(ID);
  }
  match(RIGHT_PAREN);
  return p;
}

Parameter Parser::makeParameter(){
  Parameter currentP;
  if(token ==  STRING || token == ID){
    currentP.add(tokenValue);
    increment();
  }
  else{
    match(LEFT_PAREN);
    currentP.clearExpression();
    currentP.add("(");

    currentP.add(makeParameter().print());

    if(currentP.checkOperator(token)){increment();}
    else{error();}

    currentP.add(makeParameter().print());
    
    currentP.add(")");
    match(RIGHT_PAREN);
  }
  return currentP;
}

Predicate Parser::normalPredicate(char type){
  bool moreParas;
  Predicate tempPred = Predicate(tokenValue);
  match(ID);
  match(LEFT_PAREN);
  do{
    moreParas = false;
    tempPred.addNewParameter(makeParameter());
    //Are there more parameters in the predicate
    if(token == COMMA) {moreParas = true;}
    else break;
    match(COMMA);
  }
  while(moreParas);
  match(RIGHT_PAREN);

  switch(type){
    case 'r':
      if(token != PERIOD){match(COMMA);}
      break;
    case 'q':
      if(token != Q_MARK){match(COMMA);}
  }
  return tempPred;
}