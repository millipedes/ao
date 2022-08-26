/**
 * @file   token_type.c
 * @brief  This file contains the related functions for the token_type
 * enumeration.
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/token_type.h"

/**
 * This funciton takes a token_type and converts it to a const char *
 * representation.
 * @param token_type - The type in question.
 * @return        .\ - The corresponding const char *.
 */
const char * token_type_to_string(token_type type) {
  switch(type) {
    case TOKEN_VAR:       return "Token Var";
    case TOKEN_INT:       return "Token Int";
    case TOKEN_DOUBLE:    return "Token Double";
    case TOKEN_PLUS:      return "Token Plus";
    case TOKEN_MINUS:     return "Token Minus";
    case TOKEN_MULT:      return "Token Mult";
    case TOKEN_DIV:       return "Token Div";
    case TOKEN_L_PAREN:   return "Token L Paren";
    case TOKEN_R_PAREN:   return "Token R Paren";
    case TOKEN_COMMA:     return "Token Comma";
    case TOKEN_POWER:     return "Token Power";
    case TOKEN_ASSIGN:    return "Token Assign";
    case TOKEN_EQUALITY:  return "Token Equality";
    case TOKEN_GT_EQ:     return "Token Gt Eq";
    case TOKEN_GT:        return "Token Gt";
    case TOKEN_LT_EQ:     return "Token Lt Eq";
    case TOKEN_LT:        return "Token Lt";
    case TOKEN_SIN:       return "Token Sin";
    case TOKEN_COS:       return "Token Cos";
    case TOKEN_TAN:       return "Token Tan";
    case TOKEN_ARC_SIN:   return "Token Arc Sin";
    case TOKEN_ARC_COS:   return "Token Arc Cos";
    case TOKEN_ARC_TAN:   return "Token Arc Tan";
    case TOKEN_LOG:       return "Token Log";
    case TOKEN_NEWLINE:   return "Token Newline";
  }
  fprintf(stderr, "[TOKEN_TYPE_TO_STRING]: Fell Through\nExiting\n");
  exit(1);
}
