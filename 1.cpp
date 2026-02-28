#include <iostream>  // cin.peek()
#include <string>
#include <cctype>  // isspace(), isdigit(), isalpha()

using namespace std;

int uTestNum = -1;  // Project 1 要求之 file-scope variable


enum TokenType {
  EMPTY,  // 預設值
  IDENT,  // Identifiers
  INT, FLOAT,  // 
  // symbol
  ARITH_OP,  // Arithmetic Operator: + - * /
  BOOL_OP,  // Boolean Operator: = <> > < >= <=
  L_PAREN, R_PAREN,  // ( )
  ASSIGN, SEMICOLON,  // := ;
  
  QUIT,  // quit 
  END_OF_FILE,  // EOF
  UNKNOWN  // 未知
};

enum ExceptionType {
  
};

class Token {
 private:
  TokenType type;
  string value;  // token的字串內容
 public:
  Token() {
    type = EMPTY;
    value = "";
  }

  Token(const TokenType & type, const string & value) {
    this->type = type;
    this->value = value;
  }

  Token(const TokenType & type, const char & value) {
    this->type = type;
    this->value = string(1, value);  // char轉string
  }
};


class Scanner {
 private:
  char current_char = '\0';
  int current_line = 1;
  int current_column = 0;

  // 要特地處理 EOF 嗎?
  // 自定義GetNextChar()，會自動維護 current_行列 數值。
  char GetNextChar() {
    if (current_char == '\n') {  // 若前一個char是'\n'
      current_line++;
      current_column = 1;
    } else {  // 否則就右移一位
      current_column++;
    }
    return cin.get();  // 讀取一個字元並回傳
  }
 
  // 讀取下一個有效字元
  char GetNextNonWhiteChar() {
    current_char = GetNextChar();
    // 讀掉空白字元
    while (isspace(current_char)) {
      current_char = GetNextChar();
    }
    // 讀掉單行註解
    if (current_char == '/') {
      if (cin.peek() == '/') {
        while (current_char != '\n') {
          current_char = GetNextChar();
        }
      }
    }
    return current_char;
  }
  
  Token ReadWhole_IDENT() {
    string token_string = {current_char};  // token的第一個char
    char next_char = cin.peek();  // 看下一個char (還沒讀取)
    // 必須是 字母 or 數字 or '_'
    while (isdigit(next_char) || isalpha(next_char) || next_char == '_') {
      current_char = GetNextChar();
      token_string += current_char;
      next_char = cin.peek();
    }
    return Token(IDENT, token_string);
  }

  Token ReadWhole_NUM() {
    string token_string = {current_char};  // token的第一個char
    bool has_dot = (current_char == '.');  // 如果第一個char就是'.'
    // 把下個chat存入token，直到不是數字
    while (isdigit(cin.peek())) {
      current_char = GetNextChar();
      token_string += current_char;
    }
    // 若第一次遇到'.'，繼續存char直到不是數字
    if (has_dot == false && cin.peek() == '.') {
      current_char = GetNextChar();
      token_string += current_char;
      has_dot = true;
      while (isdigit(cin.peek())) {
        current_char = GetNextChar();
        token_string += current_char;
      }
    }
    // 回傳token
    if (has_dot) {
      return Token(FLOAT, token_string);
    }
    return Token(INT, token_string);
  }

  // 檢驗token的第一個char，是否可能成為合法 符號token
  bool MayBeSymbol(const char & ch) {
    switch (ch) {
      case '+': case '-': case '*': case '/': 
      case '(': case ')':                     
      case ':': case ';':                    
      case '=': case '<': case '>':                                    
        return true;
      default:
        return false;
    }
  }

  Token ReadWhole_Symbol() {
    string token_string = {current_char};  // token的第一個char
    if (current_char == ':') {
      if (cin.peek() == '=') {  // :=
        current_char = GetNextChar();
        token_string += current_char;
        return Token(ASSIGN, token_string);
      } else {  // :

      }
    }
  }

 public:
  Token GetNextToken() {
    current_char = GetNextNonWhiteChar();  // 此token的第一個char
    Token token;
    if (isalpha(current_char) || current_char == '_') {  // IDENT
      token = ReadWhole_IDENT();
    } else if (isdigit(current_char)) {  // NUM
      token = ReadWhole_NUM();
    } else if (current_char == EOF) {
      token = Token(END_OF_FILE, current_char);  // Symbol 符號
    } else if (MayBeSymbol(current_char)) {

    }


    return token;
  }
  
  // 讀掉(忽略)整行input
  void IgnoreThisLine() {
    while (current_char != '\n') {
      current_char = GetNextChar();
    }
  }

};
 

class Parser {
  
};


int main() {
  cin >> uTestNum;  // Project 1 要求：讀取測試編號
  
  
}