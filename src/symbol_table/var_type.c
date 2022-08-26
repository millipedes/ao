/**
 * @file   var_type.c
 * @brief  This file contains the functions relating to the var_type
 * enumeration.
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/var_type.h"

/**
 * This function takes a var_type and converts it to a string.
 * @param vt - The var_type to be converted.
 * @return
 */
const char * var_type_to_string(var_type vt) {
  switch(vt) {
    case DOUBLE: return "Double";
    case INT:    return "Int";
    case STRING: return "String";
  }
  fprintf(stderr, "[VAR_TYPE_TO_STRING]: Fell Through\nExiting\n");
  exit(1);
}
