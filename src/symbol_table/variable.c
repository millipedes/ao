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
variable * init_variable(char * name, void * literal, var_type vt) {
  variable * var = calloc(1, sizeof(struct VARIABLE_T));
  size_t len = 0;
  var->type = vt;
  len = strnlen(name, MAX_TOK_LEN) + 1;
  var->name = calloc(len, sizeof(char));
  strncpy(var->name, name, len);
  switch(vt) {
    case DOUBLE:
      var->literal = calloc(1, sizeof(double));
      // C is awesome!! :)
      *((double *)var->literal) = *(double*)literal;
      break;
    case INT:
      var->literal = calloc(1, sizeof(int));
      // C is awesome!! :)
      *((int *)var->literal) = *(int*)literal;
      break;
    case STRING:
      // C is awesome!! :)
      len = strnlen((char *)literal, MAX_TOK_LEN) + 1;
      var->literal = calloc(len, sizeof(char));
      strncpy((char *)var->literal, literal, len);
      break;
  }
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
  printf("Value: ");
  switch(var->type) {
    case INT:
      printf("%d\n", *((int *)var->literal));
      break;
    case DOUBLE:
      printf("%f\n", *((double *)var->literal));
      break;
    case STRING:
      printf("`%s`\n", (char *)var->literal);
      break;
  }
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
