/**
 * @file   variable.h
 * @brief  This file contains the function defintions for the variable.c file.
 * structure.
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef VAR_H
#define VAR_H

#include <stdlib.h>
#include <string.h>
#include "var_type.h"
#include "../../main/include/constants.h"

/**
 * This structure is used to represent a variable in the symbol_table
 */
typedef struct VARIABLE_T {
  /** The name of the variable */
  char * name;
  /** The value of the variable */
  void * literal;
  /** The type of the variable */
  var_type type;
} variable;

variable * init_variable(char * name, void * literal, var_type vt);
void variable_dump_debug(variable * var);
void free_variable(variable * var);

#endif
