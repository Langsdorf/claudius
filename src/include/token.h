#pragma once

typedef struct TokenStruct {
  enum tokenType {
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_EQUALS,
    TOKEN_TYPE_SEMICOLON,
    TOKEN_TYPE_COMMA,
    TOKEN_TYPE_EXCLAMATION_POINT,
    TOKEN_TYPE_EOF
  } type;

  char *value;

} token_t;

token_t *init_token(char *value, int type);
