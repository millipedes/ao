/**
 * @file   variable.c
 * @brief  This file contains the functions related to the variable data
 * structure.
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include "include/variable.h"

/**
 * This funciton initializes a variable with name and literal value.
 * @param    name - The name of the new variable.
 * @param literal - The literal value of the variable (akin to *id*).
 * @param      vt - The variable type.
 * @return
 */
variable * init_variable(char * name, char * literal, var_type vt) {
  variable * var = calloc(1, sizeof(struct VARIABLE_T));
  size_t name_len = strnlen(name, MAX_TOK_LEN);
  size_t literal_len = strnlen(literal, MAX_TOK_LEN);
  var->type = vt;
  var->name = calloc(name_len + 1, sizeof(char));
  var->literal = calloc(literal_len + 1, sizeof(char));
  strncpy(var->name, name, name_len);
  strncpy(var->literal, literal, literal_len);
  // If there is a numeric qty to the variable, record it otherwise make it 0
  if(vt == DOUBLE || vt == INT)
    var->numeric_value = atof(literal);
  else
    var->numeric_value = 0;
  return var;
}

/**
 * This function is used in debugging the variable data structure.
 * @param var - The variable to be debugged.
 * @return N/a
 */
void variable_dump_debug(variable * var) {
  printf("Variable\n");
  printf("Name: `%s`\n", var->name);
  printf("Literal: `%s`\n", var->literal);
  printf("Numeric Qty: %f\n", var->numeric_value);
  printf("--\n");
}

/**
 * This function frees a variable.
 * @param  var - The variable to be freed.
 * @return N/a
 */
void free_variable(variable * var) {
  if(var) {
    if(var->name)
      free(var->name);
    if(var->literal)
      free(var->literal);
    free(var);
  }
}
