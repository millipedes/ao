/**
 * @file   token.h
 * @brief  This file contains the function definitions for token.c
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef TOK_H
#define TOK_H

#include <string.h>
#include "token_type.h"
#include "../../main/include/constants.h"

/**
 * This structure is used to represent a token.
 */
typedef struct TOKEN_T {
  /** The literal string of the token */
  char * t_literal;
  /** The type of the token */
  token_type type;
} token;

token * init_token(char * t_literal, token_type type);
void token_dump_debug(token * t);
void free_token(token * t);

#endif
