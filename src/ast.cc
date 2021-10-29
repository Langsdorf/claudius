#include "include/ast.h"
#include "include/main.h"

#include <cstddef>
#include <stdlib.h>

ast_t *init_ast(int type) {
  ast_t *ast = (ast_t *)malloc(sizeof(ast_t));
  ast->type = (ASTStruct::ASTType)type;

  ast->node.value = NULL;
  ast->node.name = NULL;
  ast->node.size = 0;

  return ast;
}