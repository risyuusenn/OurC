#include <iostream>  // cin.peek()
#include <string>
#include <sstream>  
#include <vector>
#include <cctype>  // isspace(), isdigit(), isalpha()

using namespace std;

int uTestNum = -1;  // Project 1 要求之 file-scope variable

enum class TokenType {
  EMPTY,  // 預設值
  IDENT,  // Identifiers
  INT, 
  FLOAT,
  SYMBOL,  // 各種 符號 or 運算子
  QUIT,  // quit 
  END_OF_FILE,  // EOF
};

// OurC 符號Token字典
vector<string> Symbol_Dictionary = {"+", "-", "*", "/", ":=", ";", "=", "<>", "<", ">", "<=", ">=", "(", ")"};

enum class ExceptionType {
  EMPTY_ERR,  // 預設值
  LEXICAL_ERR,
  SYNTACTIC_ERR,
  SEMANTIC_ERR
};


class Token {
 public:
  TokenType type;
  string value;  // token的字串內容

  Token() {
    type = TokenType::EMPTY;
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


class OurException {
 public:
  ExceptionType error_type;
  string error_msg;

  OurException() {
    error_type = ExceptionType::EMPTY_ERR;
    error_msg = "???";
  } 

  OurException(ExceptionType error_type, char first_char) {
    this->error_type = error_type;
    stringstream ss;
    if (error_type == ExceptionType::LEXICAL_ERR) {
      ss << "Unrecognized token with first char : '" << first_char << "'\n";
    } 
    this->error_msg = ss.str();
  } 
};


class Scanner {
 private:
  char current_char = '\0';
  int current_line = 1;
  int current_column = 0;

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
        IgnoreThisLine();
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
    return Token(TokenType::IDENT, token_string);
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
      return Token(TokenType::FLOAT, token_string);
    }
    return Token(TokenType::INT, token_string);
  }

  // 查Symbol_Dictionary字典，檢驗此token是否可能成為合法symbol_token
  bool MayBeSymbol(const string & token_string) {
    for (const auto & symbol_token : Symbol_Dictionary) {  // 查Symbol_Dictionary
      if (symbol_token.size() < token_string.size()) {  // 此symbol_token長度不足，跳過，繼續查下一個symbol_token
        continue;
      } 
      // 檢查token是否符合此symbol_token
      bool may_be_symbol = true;
      for (int t = 0; t < token_string.size(); t++) {
        if (token_string[t] != symbol_token[t]) {
          may_be_symbol = false;
        }
      }
      if (may_be_symbol) {
        return true;
      }
    }
    return false;  // 沒找到任何符合的symbol_token
  }

  Token ReadWhole_Symbol() {
    string token_string = {current_char};  // token的第一個char
    while (MayBeSymbol(token_string + (char)cin.peek())) {
      current_char = GetNextChar();
      token_string += current_char;
    }
    return Token(TokenType::SYMBOL, token_string);
  }

 public:
  Scanner() {}

  Token GetNextToken() {
    current_char = GetNextNonWhiteChar();  // 讀取此token的第一個char
    Token token;
    if (isalpha(current_char) || current_char == '_') {  // IDENT
      token = ReadWhole_IDENT();
    } else if (isdigit(current_char) || current_char == '.') {  // NUM
      token = ReadWhole_NUM();
    } else if (MayBeSymbol(string(1, current_char))) {  // Symbol 
      token = ReadWhole_Symbol();
    } else if (current_char == EOF) {
      token = Token(TokenType::END_OF_FILE, current_char);  
    } else {
      throw OurException(ExceptionType::LEXICAL_ERR, current_char);
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


void Test() {
  Scanner scanner;
  Token token;
  while (token.type != TokenType::END_OF_FILE) {
    try {
      token = scanner.GetNextToken();
    } catch (OurException e) {
      cout << e.error_msg;
      if (e.error_type == ExceptionType::LEXICAL_ERR) {
        scanner.IgnoreThisLine();
      }
      continue;
    }
    cout << "type : " << int(token.type) << "\n";
    cout << "value : "<<token.value << "\n";
  }
}


int main() {
  cin >> uTestNum;  // Project 1 要求：讀取測試編號

  Test();
}