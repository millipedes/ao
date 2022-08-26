/**
 * @file   token_type.h
 * @brief  This file contains the function definitions for token_type.c
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef TT_H
#define TT_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  TOKEN_VAR,
  TOKEN_FILE_NAME,
  TOKEN_INT,
  TOKEN_DOUBLE,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MULT,
  TOKEN_DIV,
  TOKEN_L_PAREN,
  TOKEN_R_PAREN,
  TOKEN_COMMA,
  TOKEN_POWER,
  TOKEN_SIN,
  TOKEN_COS,
  TOKEN_TAN,
  TOKEN_ARC_SIN,
  TOKEN_ARC_COS,
  TOKEN_ARC_TAN,
  TOKEN_LOG,
  TOKEN_NEWLINE
} token_type;

const char * token_type_to_string(token_type type);

#endif
