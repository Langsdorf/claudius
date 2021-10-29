#include "include/token.h"
#include <stdlib.h>

token_t *init_token(char *value, int type) {
  token_t *token = (token_t *)malloc(sizeof(token_t));

  token->value = value;
  token->type = (TokenStruct::tokenType)type;

  return token;
}