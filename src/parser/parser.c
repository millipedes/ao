/**
 * @file   parser.c
 * @brief  This file contains the functions required for parsing input
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include"include/parser.h"

/**
 * This function parses an expression from a token stack. Essentially anything
 * that is a mathematical term (in the sense of operands of +/-).
 * @param  tok_list - the token stack to be parsed
 * @return       .\ - the abstract syntax tree of the expression
 */
ast * parse_expression(token_stack ** ts, symbol_table ** st) {
  ast * left_child = NULL;
  ast * right_child = NULL;
  if(ts[0]) {
    left_child = parse_term(ts, st);
    switch(ts[0]->current->type) {
      case TOKEN_PLUS:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast("+", TOKEN_PLUS), left_child, right_child);
      case TOKEN_MINUS:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast("-", TOKEN_MINUS), left_child, right_child);
      case TOKEN_ASSIGN:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast("=", TOKEN_ASSIGN), left_child, right_child);
      case TOKEN_EQUALITY:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast("==", TOKEN_EQUALITY), left_child, right_child);
      case TOKEN_GT_EQ:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast(">=", TOKEN_GT_EQ), left_child, right_child);
      case TOKEN_GT:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast(">", TOKEN_GT), left_child, right_child);
      case TOKEN_LT_EQ:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast("<=", TOKEN_LT_EQ), left_child, right_child);
      case TOKEN_LT:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast("<", TOKEN_LT), left_child, right_child);
      case TOKEN_L_OR:
        ts[0] = pop_token(ts[0]);
        right_child = parse_expression(ts, st);
        return binary_tree(init_ast("||", TOKEN_L_OR), left_child, right_child);
      case TOKEN_MULT:
        ts[0] = pop_token(ts[0]);
        right_child = parse_term(ts, st);
        return binary_tree(init_ast("*", TOKEN_MULT), left_child, right_child);
      case TOKEN_DIV:
        ts[0] = pop_token(ts[0]);
        right_child = parse_term(ts, st);
        return binary_tree(init_ast("/", TOKEN_DIV), left_child, right_child);
      case TOKEN_L_BRACKET:
        right_child = parse_factor(ts, st);
        return unary_tree(left_child, right_child);
      case TOKEN_R_PAREN:
      case TOKEN_R_BRACKET:
      case TOKEN_VAR:
      case TOKEN_INT:
      case TOKEN_DOUBLE:
      case TOKEN_COMMA:
      case TOKEN_STRING:
      case TOKEN_NEWLINE: // This will occur bc factor pops id i.e. newline
        return left_child;
      default:
        fprintf(stderr, "[PARSER1]: Unrecognized token: `%s`\nExiting\n",
            ts[0]->current->t_literal);
        exit(1);
    }
  } else {
    return left_child;
  }
}

/**
 * This function parses a term from the token stack.  Essentially just anything
 * that is a mathematical coefficient.
 * @param  ts - the token stack from which the term is read
 * @return .\ - the appropriate abstract syntrax tree to model the input
 */
ast * parse_term(token_stack ** ts, symbol_table ** st) {
  ast * left_child = NULL;
  ast * right_child = NULL;
  if(ts[0]) {
    left_child = parse_factor(ts, st);
    switch(ts[0]->current->type) {
      case TOKEN_VAR:
      case TOKEN_INT:
      case TOKEN_DOUBLE:
      case TOKEN_STRING:
        return left_child;
      case TOKEN_MULT:
        ts[0] = pop_token(ts[0]);
        right_child = parse_factor(ts, st);
        return binary_tree(init_ast("*", TOKEN_MULT), left_child, right_child);
      case TOKEN_DIV:
        ts[0] = pop_token(ts[0]);
        right_child = parse_factor(ts, st);
        return binary_tree(init_ast("/", TOKEN_DIV), left_child, right_child);
      case TOKEN_PLUS:
        return left_child;
        // ts[0] = pop_token(ts[0]);
        // right_child = parse_factor(ts, st);
        // return binary_tree(init_ast("+", TOKEN_PLUS), left_child, right_child);
      case TOKEN_MINUS:
        return left_child;
        // ts[0] = pop_token(ts[0]);
        // right_child = parse_factor(ts, st);
        // return binary_tree(init_ast("-", TOKEN_MINUS), left_child, right_child);
      default:
        return left_child;
    }
  } else {
    return NULL;
  }
}

/**
 * This function is meant to parse a factor, just either a number/variable or an
 * expression within a parenthesis
 * @param          ts - the token stack to be parsed
 * @return left_child - the new abstract syntax tree from the factor
 */
ast * parse_factor(token_stack ** ts, symbol_table ** st) {
  ast * parent = NULL;
  ast * left_child = NULL;
  ast * right_child = NULL;
  switch(ts[0]->current->type) {
    case TOKEN_VAR:
      left_child = init_ast(ts[0]->current->t_literal, ts[0]->current->type);
      ts[0] = pop_token(ts[0]);
      if(ts[0]->current->type != TOKEN_POWER)
        return left_child;
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts, st);
      return binary_tree(init_ast("^", TOKEN_POWER), left_child, right_child);
    case TOKEN_STRING:
      left_child = init_ast(ts[0]->current->t_literal, ts[0]->current->type);
      ts[0] = pop_token(ts[0]);
      return left_child;
    case TOKEN_INT:
    case TOKEN_DOUBLE:
      left_child = init_ast(ts[0]->current->t_literal, ts[0]->current->type);
      ts[0] = pop_token(ts[0]);
      if(ts[0]->current->type != TOKEN_POWER)
        return left_child;
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts, st);
      return binary_tree(init_ast("^", TOKEN_POWER), left_child, right_child);
    case TOKEN_L_PAREN:
      ts[0] = pop_token(ts[0]);
      left_child = parse_expression(ts, st);
      if(ts[0]->current->type == TOKEN_R_PAREN) {
        ts[0] = pop_token(ts[0]);
        if(ts[0]->current->type != TOKEN_POWER)
          return left_child;
        ts[0] = pop_token(ts[0]);
        right_child = parse_factor(ts, st);
        return binary_tree(init_ast("^", TOKEN_POWER), left_child, right_child);
      } else {
        fprintf(stderr, "[PARSER4]: UnMatched Parenthesis\nExiting\n");
        exit(1);
      }
    case TOKEN_L_BRACKET:
      ts[0] = pop_token(ts[0]);
      parent = init_ast("[]", TOKEN_L_BRACKET);
      parent = add_child(parent, parse_expression(ts, st));
      while(ts[0]->current->type != TOKEN_R_BRACKET) {
        if(ts[0]->current->type == TOKEN_COMMA)
          ts[0] = pop_token(ts[0]);
        parent = add_child(parent, parse_expression(ts, st));
      }
      ast_dump_debug(parent);
      return parent;
    case TOKEN_MULT:
      ts[0] = pop_token(ts[0]);
      right_child = parse_term(ts, st);
      return binary_tree(init_ast("*", TOKEN_MULT), left_child, right_child);
    case TOKEN_DIV:
      ts[0] = pop_token(ts[0]);
      right_child = parse_term(ts, st);
      return binary_tree(init_ast("/", TOKEN_DIV), left_child, right_child);
    case TOKEN_SIN:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts, st);
      return unary_tree(init_ast("sin", TOKEN_SIN), right_child);
    case TOKEN_COS:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts, st);
      return unary_tree(init_ast("cos", TOKEN_COS), right_child);
    case TOKEN_TAN:
      ts[0] = pop_token(ts[0]);
      right_child = parse_factor(ts, st);
      return unary_tree(init_ast("tan", TOKEN_TAN), right_child);
    case TOKEN_ARC_SIN:
      ts[0] = pop_token(ts[0]); 
      right_child = parse_factor(ts, st);
      return unary_tree(init_ast("arcsin", TOKEN_ARC_SIN), right_child);
    case TOKEN_ARC_COS:
      ts[0] = pop_token(ts[0]); 
      right_child = parse_factor(ts, st);
      return unary_tree(init_ast("arccos", TOKEN_ARC_COS), right_child);
    case TOKEN_ARC_TAN:
      ts[0] = pop_token(ts[0]); 
      right_child = parse_factor(ts, st);
      return unary_tree(init_ast("arctan", TOKEN_ARC_TAN), right_child);
    case TOKEN_LOG:
      ts[0] = pop_token(ts[0]); 
      right_child = parse_factor(ts, st);
      return unary_tree(init_ast("log", TOKEN_LOG), right_child);
    default:
      fprintf(stderr, "[PARSER3]: Unrecognized token: `%s` type: `%s`\nExiting\n",
          ts[0]->current->t_literal, token_type_to_string(ts[0]->current->type));
      exit(1);
  }
}

/**
 * This function takes a parent tree, allocates space for children, then sets
 * the children to be left and right children respectively
 * @param      parent - the parent node of the tree
 * @param  left_child - the left child of the tree
 * @param right_child - the right child of the tree
 * @return     parent - the new tree with children left_child and right_child
 */
ast * binary_tree(ast * parent, ast * left_child, ast * right_child) {
  parent->children = calloc(2, sizeof(struct AST_T *));
  parent->children[0] = left_child;
  parent->children[1] = right_child;
  parent->no_children = 2;
  return parent;
}

/**
 * This function generates a unary tree with a parent-child relationship
 * @param  parent - the parent of the tree
 * @param   child - the child of the tree
 * @return parent - the new tree
 */
ast * unary_tree(ast * parent, ast * child) {
  parent->children = calloc(1, sizeof(struct AST_T *));
  parent->children[0] = child;
  parent->no_children = 1;
  return parent;
}
