#include "Scanner.h"
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

Scanner::Scanner(string fileName){
  //Open the file
  file = fileName;
  in.open(file);
  //Set the Line Number
  lineNumber = 1;

  //Set up the map for tokens
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

vector<Token> Scanner::parse(){
  char c;
  c = in.get();
  while(!in.eof()){
    scanToken(c);
    c = in.get();
  }
  endToken();
  return toks;
}

void Scanner::scanToken(char v){
  tokenType t = WHITESPACE;
  //Set the token type
    switch(v){
      case ',':
        t = COMMA;
        break;
      case '.':
        t = PERIOD;
        break;
      case '?':
        t = Q_MARK;
        break;
      case '(':
        t = LEFT_PAREN;
        break;
      case ')':
        t = RIGHT_PAREN;
        break;
      case ':':
        if(in.peek() == '-'){
          colonDash();
        }
        else t = COLON;
        break;
      case '*':
        t = MULTIPLY;
        break;
      case '+':
        t = ADD;
        break;
      case '#':
        isComment(v);
        break;
      case '\'':
        scanString(v);
        break;
      case '\n':
        lineNumber ++;
      default:
        if (isalpha(v)) isKeyword(v);
        else if (isspace(v));
        else t = UNDEFINED;
    }
  if (t != WHITESPACE){
    makeToken(t, v);
  }
}

void Scanner::makeToken(tokenType t, char v){
  string value = "";
  value += v;
  Token newToken(t, value, lineNumber);
  toks.push_back(newToken);
}

void Scanner::colonDash(){
  string colonString = ":";
  colonString += in.get();
  Token newToken(COLON_DASH, colonString, lineNumber);
  toks.push_back(newToken);
}

void Scanner::isComment(char comment){
  string myComment = "";
  if(in.peek() == '|'){
    //Putting the pound into myComment variable.
    myComment += comment;
    comment = in.get();

    //Putting the OR symbol into the variable
    myComment += comment;
    comment = in.get();
    multiComment(myComment, comment);
    return;
  }
  //Single Line Comment
  else{
    while(comment != '\n'){
      myComment += comment;
      comment = in.get();
    }
    Token newToken(COMMENT, myComment, lineNumber);
    toks.push_back(newToken);
    lineNumber ++;
    return;
  }
  return;
}

bool Scanner::multiComment(string wholeC, char item){
  int newLinesAdded = 0;
//Loop till we get to another OR symbol
  while(item != '|'){
    wholeC += item;
    item = in.get();

    //Make sure new lines increase the line number.
    if(item == '\n') newLinesAdded++;

    //Make sure to stop if it is the EOF
    if(in.eof()){
      Token newToken(UNDEFINED, wholeC, lineNumber);
      toks.push_back(newToken);
      lineNumber += newLinesAdded;
      return false;
    }
  }
  //Make sure that the comment ends correctly with a |# at the end.
  if(in.peek() == '#'){
    //Put the | in the comment
    wholeC += item;
    //Put in the # in the comment
    wholeC += in.get();
    toks.push_back(Token(COMMENT, wholeC, lineNumber));
    lineNumber += newLinesAdded;
    return true;
  }
  else {
    toks.push_back(Token(UNDEFINED, wholeC, lineNumber));
    lineNumber += newLinesAdded;
  }
  return false;
}

void Scanner::isKeyword(char currentChar){
  //Get the whole identity
  string myString = "";
  myString += currentChar;
  //Peek at the next one to see if's a part of the ID name.
  while(isalnum(in.peek())){
    currentChar = in.get();
    myString += currentChar;
  }
  //See if it is a key word and make the token
  if(myString == "Facts"){
    toks.push_back(Token(FACTS, myString, lineNumber));
  }
  else if(myString == "Queries"){
    toks.push_back(Token(QUERIES, myString, lineNumber));
  }
  else if (myString == "Rules"){
    toks.push_back(Token(RULES, myString, lineNumber));
  }
  else if (myString == "Schemes"){
    toks.push_back(Token(SCHEMES, myString, lineNumber));
  }
  else  toks.push_back(Token(ID, myString, lineNumber));
}


void Scanner::scanString(char value){
  string myString = "";
  int newLinesAdded = 0;
  myString += value;
  value = in.get();
  while(value != '\''|| (value == '\'' && in.peek() == '\'')){
    myString += value;
    //If there are two single quotes next to each other, grab them both.
    //Put them in the string.
    if (value == '\'' && in.peek() == '\''){
      value = in.get();
      myString += value;
      value = in.get();
    }
    else value = in.get();

    //If any new lines appear, add it to the total line number
    if(value == '\n') newLinesAdded++;

    //Check if it gets to the end of the file
    if(in.eof()) {
      toks.push_back(Token(UNDEFINED,myString, lineNumber));
      lineNumber += newLinesAdded;
      return;
    }
  }
  myString += value;
  Token newToken(STRING, myString, lineNumber);
  toks.push_back(newToken);
  lineNumber += newLinesAdded;
  return;
}

void Scanner::endToken(){
  toks.push_back(Token(END,"",lineNumber));
}

string Scanner::toString(){
  stringstream output;
  for(int i = 0; i < toks.size(); i++){
    output << "(" << getTypeString(toks[i]) << ",\"" << toks[i].getValue() << "\"," << toks[i].getLn() << ")" << '\n';
  }
  output << "Total Tokens = " << toks.size() << endl;
  return output.str();
}
