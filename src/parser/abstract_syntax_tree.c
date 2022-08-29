/**
 * @file   abstract_syntax_tree.c
 * @brief  This file contains the functions relating to the abstract_syntax_tree
 * data structure.
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/abstract_syntax_tree.h"

/**
 * This function initializes a new abstract syntax tree
 * @param t_literal - the literal string of the token
 * @param      type - the type of the token
 * @return  abstree - the abstract syntax tree
 */
ast * init_ast(char * t_literal, token_type type) {
  ast * abstree = calloc(1, sizeof(struct AST_T));
  abstree->value = init_token(t_literal, type);
  abstree->children = NULL;
  if(abstree->value->type == TOKEN_INT || abstree->value->type == TOKEN_DOUBLE)
    abstree->numeric_value = atof(abstree->value->t_literal);
  else
    abstree->numeric_value = 0.0;
  abstree->no_children = 0;
  return abstree;
}

/**
 * This function is used for debugging abstract syntax trees
 * @param abstree - the abstract syntax tree to be debugged
 * @return    N/a
 */
void ast_dump_debug(ast * abstree) {
  printf("AST\n");
  printf("Token Value: `%s`, Token Type: %d, No Children: %d\n",
      abstree->value->t_literal, abstree->value->type, abstree->no_children);
  printf("Children\n");
  for(int i = 0; i < abstree->no_children; i++) {
    printf("Token Value: `%s`, Token Type: %d, No Children: %d\n",
        abstree->children[i]->value->t_literal, abstree->children[i]->value->type,
        abstree->children[i]->no_children);
  }
  printf("End of Children\n\n");
  for(int i = 0; i < abstree->no_children; i++) {
    ast_dump_debug(abstree->children[i]);
  }
}

/**
 * This function evaluates a tree.
 * @param
 * @return
 */
ast_result * evaluate_tree(ast * abstree, symbol_table ** st) {
  int variable_index = 0;
  switch(abstree->value->type) {
    case TOKEN_VAR:
      variable_index = find_variable(st[0], abstree->value->t_literal);
      if(variable_index != -1)
        return init_ast_result(st[0]->udv[variable_index]->literal,
            st[0]->udv[variable_index]->type);
      fprintf(stderr, "[EVALUATE_TREE]: Variable `%s` not found.\nExiting\n",
          abstree->value->t_literal);
      exit(1);
    case TOKEN_INT:
      return init_ast_result(abstree->value->t_literal, INT);
    case TOKEN_DOUBLE:
      return init_ast_result(abstree->value->t_literal, DOUBLE);
    case TOKEN_PLUS:
      return ast_result_addition(evaluate_tree(abstree->children[0], st),
          evaluate_tree(abstree->children[1], st));
    case TOKEN_MINUS:
      return ast_result_subtraction(evaluate_tree(abstree->children[0], st),
          evaluate_tree(abstree->children[1], st));
    case TOKEN_MULT:
      return ast_result_multiplication(evaluate_tree(abstree->children[0], st),
          evaluate_tree(abstree->children[1], st));
    case TOKEN_DIV:
      return ast_result_division(evaluate_tree(abstree->children[0], st),
          evaluate_tree(abstree->children[1], st));
    case TOKEN_POWER:
      return ast_result_power(evaluate_tree(abstree->children[0], st),
          evaluate_tree(abstree->children[1], st));
    case TOKEN_ASSIGN:
      return ast_result_assign(abstree->children[0]->value->t_literal,
          evaluate_tree(abstree->children[1], st), st);
    case TOKEN_EQUALITY:
    case TOKEN_GT_EQ:
    case TOKEN_GT:
    case TOKEN_LT_EQ:
    case TOKEN_LT:
    case TOKEN_SIN:
    case TOKEN_COS:
    case TOKEN_TAN:
    case TOKEN_ARC_SIN:
    case TOKEN_ARC_COS:
    case TOKEN_ARC_TAN:
    case TOKEN_LOG:
    case TOKEN_NEWLINE:
    default:
      fprintf(stderr, "[EVALUATE_TREE]: Unhandled Token: `%s`\nExiting\n",
          token_type_to_string(abstree->value->type));
      exit(1);
  }
}

/**
 * This function frees an abstract syntax tree
 * @param abstree - the abstract syntax tree to be freed
 * @return    N/a
 */
void free_ast(ast * abstree) {
  if(abstree) {
    if(abstree->value)
      free_token(abstree->value);
    if(abstree->children) {
      for(int i = 0; i < abstree->no_children; i++)
        if(abstree->children[i])
          free_ast(abstree->children[i]);
      free(abstree->children);
    }
    free(abstree);
  }
}
