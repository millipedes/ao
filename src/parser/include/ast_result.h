#ifndef ASTR_H
#define ASTR_H

#include <string.h>
#include "../../main/include/constants.h"
#include "../../symbol_table/include/var_type.h"

/**
 * This structure is used for wrapping the result of the evaluate_tree function.
 * The reason for its existance is that you cannot return both type encoding and
 * the literal value at the same time without modifying data on the heap. This
 * seems like a less bug prone alternative.
 */
typedef struct AST_RESULT_T {
  /** The literal value of the result of the evaluated ast */
  char * literal;
  /** The numeric value of the result of the evaluated ast */
  double numeric_value;
  /** The variable type of the result of the evaluated ast */
  var_type type;
} ast_result;

ast_result * init_ast_result(char * literal, var_type type);
void ast_result_dump_debug(ast_result * astr);
ast_result * ast_result_addition(ast_result * astr1, ast_result * astr2);
ast_result * ast_result_subtraction(ast_result * astr1, ast_result * astr2);
ast_result * ast_result_multiplication(ast_result * astr1, ast_result * astr2);
ast_result * ast_result_division(ast_result * astr1, ast_result * astr2);
int qty_digits(int n);
void free_ast_result(ast_result * astr);

#endif
