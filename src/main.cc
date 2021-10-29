#include "include/main.h"

#include "include/parser.h"
#include <iostream>

int main() {

  lexer_t *lexer =
      init_lexer("str names = \"hello, claudius\";print! name, name2;");

  parser_t *parser = init_parser(lexer);

  ast_t *root = parse(parser);

  std::cout << "root: " << root->type << std::endl;

  return 0;
}