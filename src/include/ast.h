#pragma once

#include <cstddef>
typedef struct ASTStruct {
  enum ASTType {
    AST_NODE_TYPE_COMPOUND_STATEMENT,
    AST_NODE_TYPE_FUNCTION,
    AST_NODE_TYPE_FUNCTION_CALL,
    AST_NODE_TYPE_FUNCTION_CALL_ARGUMENT,
    AST_NODE_TYPE_FUNCTION_CALL_ARGUMENT_LIST,
    AST_NODE_TYPE_STRING,
    AST_NODE_TYPE_INTEGER,
    AST_NODE_TYPE_FLOAT,
    AST_NODE_TYPE_BOOLEAN,
    AST_NODE_TYPE_IDENTIFIER,
    AST_NODE_TYPE_ASSIGNMENT,
    AST_NODE_TYPE_VARIABLE,
    AST_NODE_TYPE_VARIABLE_DECLARATION,
  } type;

  struct ASTNode {
    ASTStruct **value;
    char *name;
    size_t size;
  } node;

} ast_t;

ast_t *init_ast(int type);