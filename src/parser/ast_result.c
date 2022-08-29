/**
 * @file   ast_result.c
 * @brief  This file contains the functions relating to the ast_result data
 * structure.  This structure is used to hold the result of the evaluate_tree
 * set of functions (i.e. type, numeric value, and literal).
 * @author Matthew C. Lindeman
 * @date   August 29, 2022
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
 * This function takes an ast_result and prints its value.
 * @param astr - The ast_result to be printed.
 * @return N/a
 */
void ast_print_result(ast_result * astr) {
  switch(astr->type) {
    case INT:
      printf("%d\n", (int)astr->numeric_value);
      break;
    case DOUBLE:
      printf("%f\n", astr->numeric_value);
      break;
    case STRING:
      printf("\"%s\"\n", astr->literal);
      break;
  }
}

/**
 * This function adds two ast_results.  Note: This is used to be in conjunction
 * with the evaluate_tree family of functions as it frees each ast_result that
 * is an argument.
 * @param   astr1 - The first argument of addition.
 * @param   astr1 - The second argument of addition.
 * @return result - The result of the addition.
 */
ast_result * ast_result_addition(ast_result * astr1, ast_result * astr2) {
  size_t one_len = 0;
  size_t two_len = 0;
  size_t result_len = 0;

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
      one_len = strnlen(astr1->literal, MAX_TOK_LEN);
      two_len = strnlen(astr2->literal, MAX_TOK_LEN);
      result_len = one_len + two_len + 1;
      result->literal = calloc(result_len, sizeof(char));
      result->type = STRING;
      strncat(result->literal, astr1->literal, result_len);
      strncat(result->literal, astr2->literal, result_len);
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
  }
  return NULL;
}

/**
 * This function subtracts two ast_results.  Note: This is used to be in
 * conjunction with the evaluate_tree family of functions as it frees each
 * ast_result that is an argument.
 * @param   astr1 - The first argument of subtraction.
 * @param   astr1 - The second argument of subtraction.
 * @return result - The result of the subtraction.
 */
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
      result->literal = calloc(qty_digits(result->numeric_value) + 2, sizeof(char));
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

/**
 * This function multiplies two ast_results.  Note: This is used to be in
 * conjunction with the evaluate_tree family of functions as it frees each
 * ast_result that is an argument.
 * @param   astr1 - The first argument of multiplication.
 * @param   astr1 - The second argument of multiplication.
 * @return result - The result of the multiplication.
 */
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
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
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

/**
 * This function divides two ast_results.  Note: This is used to be in
 * conjunction with the evaluate_tree family of functions as it frees each
 * ast_result that is an argument.
 * @param   astr1 - The first argument of division.
 * @param   astr1 - The second argument of division.
 * @return result - The result of the division.
 */
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
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
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

/**
 * This function takes an ast_result to the power of another ast_result. Note:
 * This is used to be in conjunction with the evaluate_tree family of functions
 * as it frees each ast_result that is an argument.
 * @param   astr1 - The base.
 * @param   astr1 - The power.
 * @return result - The result of the operation.
 */
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
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
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

/**
 * This function assigns value to the variable of name var in symbol_table st.
 * @param   var - The name of the variable to be logged in the symbol_table.
 * @param value - The value of the new variable.
 * @param    st - The symbol_table for the apprpriate stack frame.
 * @return   .\ - 1::Assignment Worked
 *                0::Assignment Did not Work
 */
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

/**
 * This function determines if astr1 has an equal numeric value to
 * the numeric value of astr2 (for strings, it is their length values that are
 * compared).
 * @param      astr1 - The astr to be tested for the equal to property.
 * @param      astr2 - The astr to be tested for the equal to property.
 * @return result::0 - astr1->numeric_value != astr2->numeric_value
 *         result::1 - astr1->numeric_value == astr2->numeric_value
 */
ast_result * ast_result_equality(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_EQUALITY]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
    case DOUBLE:
      result->numeric_value
        = astr1->numeric_value == astr2->numeric_value ? 1 : 0;
      result->literal = calloc(1, sizeof(char));
      result->literal[0] = result->numeric_value == 1 ? '1' : '0';
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      result->numeric_value
        = strncmp(astr1->literal, astr2->literal, MAX_TOK_LEN)
        == 0 ? 1 : 0;
      result->literal = calloc(1, sizeof(char));
      result->literal[0] = result->numeric_value == 1 ? '1' : '0';
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
  }
  return NULL;
}

/**
 * This function determines if astr1 has a greater or equal numeric value to
 * the numeric value of astr2 (i.e. undefined for strings).
 * @param      astr1 - The astr to be tested for the greater or equal to
 * property.
 * @param      astr2 - The astr to be tested for the less than property.
 * @return result::0 - astr1->numeric_value < astr2->numeric_value
 *         result::1 - astr1->numeric_value >= astr2->numeric_value
 */
ast_result * ast_result_gteq(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_GTEQ]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
    case DOUBLE:
      result->numeric_value
        = astr1->numeric_value >= astr2->numeric_value ? 1 : 0;
      result->literal = calloc(1, sizeof(char));
      result->literal[0] = result->numeric_value == 1 ? '1' : '0';
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_GTEQ]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function determines if astr1 has a greater numeric value to the numeric
 * value of astr2 (i.e. undefined for strings).
 * @param      astr1 - The astr to be tested for the greater than property.
 * @param      astr2 - The astr to be tested for the less than or equal to
 * property.
 * @return result::0 - astr1->numeric_value <= astr2->numeric_value
 *         result::1 - astr1->numeric_value > astr2->numeric_value
 */
ast_result * ast_result_gt(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_GT]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
    case DOUBLE:
      result->numeric_value
        = astr1->numeric_value > astr2->numeric_value ? 1 : 0;
      result->literal = calloc(1, sizeof(char));
      result->literal[0] = result->numeric_value == 1 ? '1' : '0';
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_GT]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function determines if astr1 has a lower than or equal to the numeric
 * value of astr2 (i.e. undefined for strings).
 * @param      astr1 - The astr to be tested for the less than or equal to
 * property.
 * @param      astr2 - The astr to be tested for the greater than property.
 * @return result::0 - astr1->numeric_value > astr2->numeric_value
 *         result::1 - astr1->numeric_value <= astr2->numeric_value
 */
ast_result * ast_result_lteq(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_LTEQ]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
    case DOUBLE:
      result->numeric_value
        = astr1->numeric_value <= astr2->numeric_value ? 1 : 0;
      result->literal = calloc(1, sizeof(char));
      result->literal[0] = result->numeric_value == 1 ? '1' : '0';
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_LTEQ]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function determines if astr1 has a lower numeric value than astr2 (i.e.
 * undefined for strings).
 * @param      astr1 - The astr to be tested for the less than property.
 * @param      astr2 - The astr to be tested for the greater than or equal to
 * property.
 * @return result::0 - astr1->numeric_value >= astr2->numeric_value
 *         result::1 - astr1->numeric_value < astr2->numeric_value
 */
ast_result * ast_result_lt(ast_result * astr1, ast_result * astr2) {
  if(astr1->type != astr2->type) {
    fprintf(stderr, "[ASTR_LT]: Type Mismatch:\n1) %s\n2) %s\n"
      "Exiting\n", var_type_to_string(astr1->type),
      var_type_to_string(astr2->type));
    exit(1);
  }
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr1->type) {
    case INT:
    case DOUBLE:
      result->numeric_value
        = astr1->numeric_value < astr2->numeric_value ? 1 : 0;
      result->literal = calloc(1, sizeof(char));
      result->literal[0] = result->numeric_value == 1 ? '1' : '0';
      result->type = INT;
      free_ast_result(astr1);
      free_ast_result(astr2);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_LT]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function takes the sin of astr.
 * @param    astr - The ast result to take the sin of.
 * @return result - The resulf of the sin.
 */
ast_result * ast_result_sin(ast_result * astr) {
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr->type) {
    case INT:
      result->numeric_value = sin(astr->numeric_value);
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr);
      return result;
    case DOUBLE:
      result->numeric_value = sin(astr->numeric_value);
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_SIN]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function takes the arc_sin of astr.
 * @param    astr - The ast result to take the arc_sin of.
 * @return result - The resulf of the arc_sin.
 */
ast_result * ast_result_arc_sin(ast_result * astr) {
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr->type) {
    case INT:
      result->numeric_value = asin(astr->numeric_value);
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr);
      return result;
    case DOUBLE:
      result->numeric_value = asin(astr->numeric_value);
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_ARCSIN]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function takes the cos of astr.
 * @param    astr - The ast result to take the cos of.
 * @return result - The resulf of the cos.
 */
ast_result * ast_result_cos(ast_result * astr) {
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr->type) {
    case INT:
      result->numeric_value = cos(astr->numeric_value);
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr);
      return result;
    case DOUBLE:
      result->numeric_value = cos(astr->numeric_value);
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_COS]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function takes the arc_cos of astr.
 * @param    astr - The ast result to take the arc_cos of.
 * @return result - The resulf of the arc_cos.
 */
ast_result * ast_result_arc_cos(ast_result * astr) {
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr->type) {
    case INT:
      result->numeric_value = acos(astr->numeric_value);
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr);
      return result;
    case DOUBLE:
      result->numeric_value = acos(astr->numeric_value);
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_ARC_COS]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function takes the tan of astr.
 * @param    astr - The ast result to take the tan of.
 * @return result - The resulf of the tan.
 */
ast_result * ast_result_tan(ast_result * astr) {
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr->type) {
    case INT:
      result->numeric_value = tan(astr->numeric_value);
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr);
      return result;
    case DOUBLE:
      result->numeric_value = tan(astr->numeric_value);
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_TAN]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function takes the arc_tan of astr.
 * @param    astr - The ast result to take the arc_tan of.
 * @return result - The resulf of the arc_tan.
 */
ast_result * ast_result_arc_tan(ast_result * astr) {
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr->type) {
    case INT:
      result->numeric_value = atan(astr->numeric_value);
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr);
      return result;
    case DOUBLE:
      result->numeric_value = atan(astr->numeric_value);
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_TAN]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function takes the base 2 logarithm of astr.
 * @param    astr - The ast result to take the logarithm of.
 * @return result - The resulf of the logarithm.
 */
ast_result * ast_result_log(ast_result * astr) {
  ast_result * result = calloc(1, sizeof(struct AST_RESULT_T));
  switch(astr->type) {
    case INT:
      result->numeric_value = log(astr->numeric_value);
      result->literal = calloc(qty_digits(result->numeric_value) + 1, sizeof(char));
      sprintf(result->literal, "%d", (int)result->numeric_value);
      result->type = INT;
      free_ast_result(astr);
      return result;
    case DOUBLE:
      result->numeric_value = log(astr->numeric_value);
      // If negative string has one more space, '-'
      result->literal = (result->numeric_value > 0)
        ? calloc(10 + qty_digits(result->numeric_value), sizeof(char))
        : calloc(11 + qty_digits(result->numeric_value), sizeof(char));
      sprintf(result->literal, "%.8f", result->numeric_value);
      result->type = DOUBLE;
      free_ast_result(astr);
      return result;
    case STRING:
      fprintf(stderr, "[AST_RESULT_TAN]: Division not Implemented for"
          " Strings\nExiting\n");
      exit(1);
  }
  return NULL;
}

/**
 * This function determines the number of whole number digits in a number.
 * @param   n - The number to get the property of.
 * @return .\ - How may whole number digits in n.
 */
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
