#pragma once

#include "token.h"

typedef struct LexerStruct {
  char c;
  int index;
  char *contents;
} lexer_t;

lexer_t *init_lexer(char *contents);

void advance(lexer_t *l);

void skip_whitespace(lexer_t *l);

token_t *get_next_token(lexer_t *l);

token_t *advance_token(lexer_t *l, token_t *t);

token_t *parse_string(lexer_t *l);

token_t *parse_id(lexer_t *l);

char *get_as_string(lexer_t *l);