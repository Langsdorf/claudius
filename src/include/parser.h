#pragma once

#include "ast.h"
#include "lexer.h"

typedef struct ParserStruct {
  lexer_t *lexer;
  token_t *current_token;
} parser_t;

parser_t *init_parser(lexer_t *lexer);

void *expect(parser_t *parser, int token_type);

ast_t *parse(parser_t *parser);

ast_t *parse_statement(parser_t *parser);

ast_t *parse_statements(parser_t *parser);

ast_t *parse_expression(parser_t *parser);

ast_t *parse_identifier(parser_t *parser);

ast_t *parse_function_call(parser_t *parser, char *function_name);

ast_t *parse_function_arguments(parser_t *parser);

ast_t *parse_variable_declaration(parser_t *parser);

ast_t *parse_variable(parser_t *parser);

ast_t *parse_string(parser_t *parser);