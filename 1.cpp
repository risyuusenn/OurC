#include <iostream>
#include <string>

using namespace std;

int uTestNum = -1;  // Project 1 要求之 file-scope variable

enum TokenType {
  EMPTY,  // 預設值
  IDENT, INT, FLOAT,  // Identifiers int float
  ARITH_OP,  // Arithmetic Operator: + - * /
  BOOL_OP,  // Boolean Operator: = <> > < >= <=
  L_PAREN, R_PAREN,  // ( )
  ASSIGN, SEMICOLON, QUIT,  // := ; quit 
  COMMENT,  // //
  END_OF_FILE,  // EOF
  UNKNOWN  // 未知
};

enum ExceptionType {
  
};

class Token {
 private:
  TokenType type;
  string content;  // token的字串內容
 public:
  Token() {
    type = EMPTY;
    content = "";
  }

  Token(const TokenType & type, const string & content) {
    this->type = type;
    this->content = content;
  }
};


// 詞法分析器
class Lexer {
 private:
  // 此字元是數字?
  bool IsDigit(char ch) {
    if (ch >= 48 && ch <= 57) {
      return true;
    }
    return false;
  }

  // 此字元是英文字母?
  bool IsLetter(char ch) {
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
      return true;
    }
    return false;
  }

  bool IsINT(const string & string) {
    for (const auto & ch : string) {
      if (IsDigit(ch) == false) {
        return false;
      }
    }
    return true;
  }

  bool IsFLOAT(const string & string) {
    int point = 0;  // 紀錄有幾個'.'
    for (const auto & ch : string) {
      if (ch == '.') {
        point++;
      } else if (IsDigit(ch) == false) {
        return false;
      }
    }
    // 只能有一個'.'
    if (point == 1) {
      return true;
    }
    return false;
  }

  bool IsIDENT(const string & string) {
    if (IsLetter(string[0])) {  // IDENT starts with a letter
      for (const auto & ch : string) {  // and is followed by digits or letters or underlines
        if (!IsDigit(ch) && !IsLetter(ch) && ch != '_') {
          return false;
        }
      }
    }
    return false;
  }

 public:
  TokenType WhatTokenType(const string & token_string) {
    TokenType token_type = EMPTY;
    if (IsINT(token_string)) {
      token_type = INT;
    } else if (IsFLOAT(token_string)) {
      token_type = FLOAT;
    } else if (IsIDENT(token_string)) {
      token_type = IDENT;
    } else {
      token_type = UNKNOWN;
    }
  }

  // 是否無法接續字元成為其他token type?
  bool IsTerminalType(TokenType token_type) {
    
  }
};


class Scanner {
 private:
  char current_char = ' ';  // 目前讀到哪個字元
  Lexer lexer;  // 詞法(token)分析器

 public:
  Token GetNextToken() {
    string token_string;  // 目前字串
    // 若前一個token讀剩的char為有效字元，放進此token
    if (current_char != ' ' && current_char != '\n' && current_char != '\t' && current_char != EOF) {
      token_string += current_char;
    }
    // 讀掉token之間的空格或'\n'或'\t'
    while (current_char == ' ' || current_char == '\n' || current_char == '\t') {
      // 遇到EOF，結束讀取
      if (current_char == EOF) {
        break;
      }
      current_char = getchar();
    }
    // 讀token
    TokenType token_type = EMPTY;
    while (current_char != ' ' && current_char != '\n' && current_char != '\t') {
      // 遇到EOF，結束讀取
      if (current_char == EOF) {
        break;
      }
      // 遇到有效字元，判斷是否能放進此token
      if (token_string == "") {  // 目前string空的，直接放進token
        token_string += current_char;
      } else if (1) {  // 
        
      }

      current_char = getchar();
    }

    
    Token token = Token(token_type, token_string);
    return token;
  }

  void SkipRestOfLine() {
    
  }
};
 


int main() {
  cin >> uTestNum;  // Project 1 要求：讀取測試編號
  string a;
  
}