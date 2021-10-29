#include "include/main.h"

#include "include/lexer.h"
#include "include/token.h"

using namespace std;

lexer_t *init_lexer(char *contents) {
  lexer_t *lexer = (lexer_t *)malloc(sizeof(lexer_t));

  lexer->contents = contents;
  lexer->index = 0;
  lexer->c = contents[0];

  return lexer;
}

void advance(lexer_t *l) {
  if (l->c != '\0' && l->index < strlen(l->contents)) {
    l->index++;
    l->c = l->contents[l->index];
  }
}

void skip_whitespace(lexer_t *l) {
  while (l->c == ' ' || l->c == '\t' || l->c == '\n' || l->c == '\r') {
    advance(l);
  }
}

token_t *get_next_token(lexer_t *l) {
  while (l->c != '\0' && l->index < strlen(l->contents)) {

    skip_whitespace(l);

    if (isalnum(l->c))
      return parse_id(l);

    if (l->c == '"') {
      token_t *token = parse_string(l);

      return token;
    }

    switch (l->c) {
    case '=':
      return advance_token(
          l, init_token(get_as_string(l), TokenStruct::TOKEN_TYPE_EQUALS));
      break;

    case ';':
      return advance_token(
          l, init_token(get_as_string(l), TokenStruct::TOKEN_TYPE_SEMICOLON));
      break;

    case ',':
      return advance_token(
          l, init_token(get_as_string(l), TokenStruct::TOKEN_TYPE_COMMA));
      break;

    case '!':
      return advance_token(
          l, init_token(get_as_string(l),
                        TokenStruct::TOKEN_TYPE_EXCLAMATION_POINT));
      break;

    default:
      cout << "Token " << l->c << "not found" << endl;
      exit(1);
      break;
    }
  }

  return init_token(get_as_string(l), TokenStruct::TOKEN_TYPE_EOF);
  ;
}

token_t *advance_token(lexer_t *l, token_t *t) {
  advance(l);
  return t;
}

token_t *parse_string(lexer_t *l) {

  advance(l); // skip current <">

  char *value = (char *)malloc(sizeof(char));

  value[0] = '\0';

  while (l->c != '"') {
    if (l->c == '\0') {
      cout << "Unterminated string" << endl;
      exit(1);
    }

    char *s = get_as_string(l);
    value =
        (char *)realloc(value, sizeof(char) * (strlen(value) + strlen(s) + 1));

    strcat(value, s);

    advance(l);
  }

  advance(l); // skip current <">

  return init_token(value, TokenStruct::TOKEN_TYPE_STRING);
}

token_t *parse_id(lexer_t *l) {
  char *value = (char *)malloc(sizeof(char));

  value[0] = '\0';

  while (isalnum(l->c) && l->c != '\0' && l->c != '"') {
    char *s = get_as_string(l);
    value =
        (char *)realloc(value, sizeof(char) * (strlen(value) + strlen(s) + 1));

    strcat(value, s);

    advance(l);
  }

  return init_token(value, TokenStruct::TOKEN_TYPE_IDENTIFIER);
}

char *get_as_string(lexer_t *l) {
  char *s = (char *)malloc(sizeof(char));
  s[0] = l->c;
  s[1] = '\0';

  return s;
}
