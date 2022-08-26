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

typedef struct VARIABLE_T {
  char * name;
  char * literal;
  double numeric_qty;
  var_type type;
} variable;

variable * init_variable(char * name, char * literal, var_type vt);
void variable_dump_debug(variable * var);
void free_variable(variable * var);

#endif
