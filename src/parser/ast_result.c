/**
 * @file   ast_result.c
 * @brief  This file contains the functions relating to the ast_result data
 * structure.  This structure is used to hold the result of the evaluate_tree
 * set of functions (i.e. type, numeric value, and literal).
 * @author Matthew C. Lindeman
 * @date   
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include "include/ast_result.h"

/**
 * This function initializes an ast_result.
 * @param literal - The literal value of the result.
 * @param    type - The variable type of the result of the ast.
 * @return   astr - The initialized ast result.
 */
ast_result * init_ast_result(char * literal, var_type type) {
  ast_result * astr = calloc(1, sizeof(struct AST_RESULT_T));
  size_t len = 0;
  len = strnlen(literal, MAX_TOK_LEN) + 1;
  astr->literal = calloc(len, sizeof(char));
  strncpy(astr->literal, literal, len);
  astr->type = type;
  if (astr->type == INT)
    astr->numeric_value = atoi(literal);
  else if(astr->type == DOUBLE)
    astr->numeric_value = atof(literal);
  else
    astr->numeric_value = 0;
  return astr;
}

/**
 * This function is used in debugging the ast_results.
 * @param astr - The ast_result to be debugged.
 * @return N/a
 */
void ast_result_dump_debug(ast_result * astr) {
  printf("Ast Result\n");
  printf("Literal Value: `%s`\n", astr->literal);
  printf("Numeric Value: %f\n", astr->numeric_value);
  printf("Type: `%s`\n", var_type_to_string(astr->type));
  printf("--\n");
}

/**
 * This function adds two ast_results.  Note: This is used to be in conjunction
 * with the evaluate_tree family of functions as it frees each ast_result that
 * is an argument.
 * @param astr1 - The first argument of addition.
 * @param astr1 - The second argument of addition.
 * @return
 */
ast_result * ast_result_addition(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_ADDITION]: Type Mismatch:\n1) %s\n2) %s\nExiting\n",
        var_type_to_string(astr1->type), var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
      result->numeric_value = astr1->numeric_value + astr2->numeric_value;
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case DOUBLE:
      result->numeric_value = astr1->numeric_value + astr2->numeric_value;
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      size_t one_len = strnlen(astr1->literal, MAX_TOK_LEN);
      size_t two_len = strnlen(astr2->literal, MAX_TOK_LEN);
      size_t result_len = one_len + two_len + 1;
      result->literal = calloc(result_len, sizeof(char));
      strncat(result->literal, astr1->literal, result_len);
      strncat(result->literal, astr2->literal, result_len);
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
  }
  return NULL;
}

ast_result * ast_result_subtraction(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_SUBTRACTION]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
      result->numeric_value = astr1->numeric_value - astr2->numeric_value;
      result->literal = calloc(qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case DOUBLE:
      result->numeric_value = astr1->numeric_value - astr2->numeric_value;
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_SUB]: Subtraction not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

ast_result * ast_result_multiplication(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_MULTIPLICATION]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
      result->numeric_value = astr1->numeric_value * astr2->numeric_value;
      result->literal = calloc(qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case DOUBLE:
      result->numeric_value = astr1->numeric_value * astr2->numeric_value;
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_MULT]: Multiplication not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

ast_result * ast_result_division(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_DIVISION]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
      result->numeric_value = astr1->numeric_value / astr2->numeric_value;
      result->literal = calloc(qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case DOUBLE:
      result->numeric_value = astr1->numeric_value / astr2->numeric_value;
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_DIV]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

ast_result * ast_result_power(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_POWER]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
      result->numeric_value = pow(astr1->numeric_value, astr2->numeric_value);
      result->literal = calloc(qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case DOUBLE:
      result->numeric_value = pow(astr1->numeric_value, astr2->numeric_value);
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_DIV]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

ast_result * ast_result_assign(char * var, ast_result * value,
    symbol_table ** st) {
  int variable_index = find_variable(st[0], var);
  if(variable_index != -1) {
    free_variable(st[0]->udv[variable_index]);
    add_variable_at_index(st[0],
        init_variable(var, value->literal, value->type), variable_index);
    if(st[0]->udv[variable_index]) {
      free_ast_result(value);
      return init_ast_result("1", INT);
    }
  } else {
    add_variable(st[0], init_variable(var, value->literal, value->type));
    if(st[0]->udv[st[0]->qty_udv - 1]) {
      free_ast_result(value);
      return init_ast_result("1", INT);
    }
  }
  return init_ast_result("0", INT);
}

int qty_digits(int n) {
  if (n < 10)         return 1;
  if (n < 100)        return 2;
  if (n < 1000)       return 3;
  if (n < 10000)      return 4;
  if (n < 100000)     return 5;
  if (n < 1000000)    return 6;
  if (n < 10000000)   return 7;
  if (n < 100000000)  return 8;
  if (n < 1000000000) return 9;
  return -1;
}

/**
 * This function frees an ast_result.
 * @param astr - The ast_result to be freed.
 * @return N/a
 */
void free_ast_result(ast_result * astr) {
  if(astr) {
    if(astr->literal)
      free(astr->literal);
    free(astr);
  }
}
