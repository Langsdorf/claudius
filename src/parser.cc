#include "include/parser.h"
#include "include/ast.h"
#include "include/lexer.h"
#include "include/main.h"
#include "include/token.h"
#include <cstdlib>
#include <iostream>

parser_t *init_parser(lexer_t *lexer) {
  parser_t *parser = (parser_t *)malloc(sizeof(parser_t));

  parser->lexer = lexer;
  parser->current_token = get_next_token(lexer);

  return parser;
}

void *expect(parser_t *parser, int token_type) {
  if (parser->current_token->type == token_type) {
    parser->current_token = get_next_token(parser->lexer);
  } else {
    printf("Unexpected token %s (%d)", parser->current_token->value,
           parser->current_token->type);
    exit(1);
  }

  return NULL;
}

ast_t *parse(parser_t *parser) { return parse_statements(parser); }

ast_t *parse_statement(parser_t *parser) {
  switch (parser->current_token->type) {
  case TokenStruct::TOKEN_TYPE_IDENTIFIER:
    return parse_identifier(parser);
  }

  return NULL;
}

ast_t *parse_statements(parser_t *parser) {
  ast_t *compound = init_ast(ASTStruct::AST_NODE_TYPE_COMPOUND_STATEMENT);
  ast_t *statment = parse_statement(parser);

  compound->node.value = (ast_t **)malloc(sizeof(ast_t *));
  compound->node.value[0] = statment;

  while (parser->current_token->type == TokenStruct::TOKEN_TYPE_SEMICOLON) {
    expect(parser, TokenStruct::TOKEN_TYPE_SEMICOLON);
    compound->node.size++;
    ast_t *next_statement = parse_statement(parser);

    compound->node.value = (ast_t **)realloc(
        compound->node.value, sizeof(ast_t *) * (compound->node.size + 1));
    compound->node.value[compound->node.size] = next_statement;
  }

  return compound;
}

ast_t *parse_expression(parser_t *parser) {
  switch (parser->current_token->type) {
  case TokenStruct::TOKEN_TYPE_STRING:
    return parse_string(parser);
  }
}

ast_t *parse_identifier(parser_t *parser) {
  if (strcmp(parser->current_token->value, "str") == 0 ||
      strcmp(parser->current_token->value, "int") == 0) {
    return parse_variable_declaration(parser);
  } else {
    return parse_variable(parser);
  }
}

ast_t *parse_function_call(parser_t *parser, char *function_name) {
  expect(parser,
         TokenStruct::TOKEN_TYPE_EXCLAMATION_POINT); // function declaration

  ast_t *function_call = init_ast(ASTStruct::AST_NODE_TYPE_FUNCTION_CALL);

  ast_t *function_arguments = parse_function_arguments(parser);

  function_call->node.value = (ast_t **)malloc(sizeof(ast_t *));
  function_call->node.value[0] = function_arguments;
  function_call->node.name = function_name;

  return function_call;
}

ast_t *parse_function_arguments(parser_t *parser) {
  ast_t *function_arguments =
      init_ast(ASTStruct::AST_NODE_TYPE_FUNCTION_CALL_ARGUMENT_LIST);
  function_arguments->node.value = (ast_t **)malloc(sizeof(ast_t *));

  ast_t *function_argument =
      init_ast(ASTStruct::AST_NODE_TYPE_FUNCTION_CALL_ARGUMENT);
  function_argument->node.value = (ast_t **)malloc(sizeof(ast_t *));

  ast_t *variable = parse_variable(parser);

  function_argument->node.value[0] = variable;
  function_arguments->node.value[0] = function_argument;

  while (parser->current_token->type == TokenStruct::TOKEN_TYPE_COMMA &&
         parser->current_token->type != TokenStruct::TOKEN_TYPE_SEMICOLON) {
    expect(parser, TokenStruct::TOKEN_TYPE_COMMA);

    ast_t *new_argument =
        init_ast(ASTStruct::AST_NODE_TYPE_FUNCTION_CALL_ARGUMENT);
    new_argument->node.value = (ast_t **)malloc(sizeof(ast_t *));

    ast_t *new_variable = parse_variable(parser);

    new_argument->node.value[0] = new_variable;

    function_arguments->node.size++;

    function_arguments->node.value = (ast_t **)realloc(
        function_arguments->node.value,
        sizeof(ast_t *) * (function_arguments->node.size + 1));

    function_arguments->node.value[function_arguments->node.size] =
        new_argument;
  }

  return function_arguments;
}

ast_t *parse_variable_declaration(parser_t *parser) {
  char *var_type = parser->current_token->value;

  expect(parser, TokenStruct::TOKEN_TYPE_IDENTIFIER); // var type

  char *string = parser->current_token->value;

  expect(parser, TokenStruct::TOKEN_TYPE_IDENTIFIER); // var name
  expect(parser, TokenStruct::TOKEN_TYPE_EQUALS);     // equals

  if (strcmp(var_type, "str") == 0 &&
      parser->current_token->type != TokenStruct::TOKEN_TYPE_STRING) {
    printf("Expected string, not %s\n", parser->current_token->value);
    exit(1);
  }

  ast_t *value = parse_expression(parser);

  ast_t *variable = init_ast(ASTStruct::AST_NODE_TYPE_VARIABLE_DECLARATION);

  variable->node.value = (ast_t **)malloc(sizeof(ast_t *));
  variable->node.value[0] = value;
  variable->node.name = string;

  return variable;
}

ast_t *parse_variable(parser_t *parser) {
  char *token_value = parser->current_token->value;
  expect(parser, TokenStruct::TOKEN_TYPE_IDENTIFIER); // var name

  if (parser->current_token->type ==
      TokenStruct::TOKEN_TYPE_EXCLAMATION_POINT) {
    return parse_function_call(parser, token_value);
  }

  ast_t *variable = init_ast(ASTStruct::AST_NODE_TYPE_VARIABLE);

  variable->node.name = token_value;

  return variable;
}

ast_t *parse_string(parser_t *parser) {
  char *token_value = parser->current_token->value;

  ast_t *string = init_ast(ASTStruct::AST_NODE_TYPE_STRING);

  string->node.value = (ast_t **)malloc(sizeof(ast_t *));
  string->node.name = token_value;

  expect(parser, TokenStruct::TOKEN_TYPE_STRING);

  return string;
}