#include "TokenClass.h"
#include <string>
using namespace std;

Token::Token(tokenType t, string v, int n){
  type = t;
  value = v;
  line = n;
}
