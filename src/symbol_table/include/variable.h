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
void free_variable(variable * var);

#endif
