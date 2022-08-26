/**
 * @file   token.c
 * @brief  This file contains the functions for the token structure.
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include "include/token.h"

/**
 * This function initializes a token
 * @param t_literal - the token literal as represented by a string
 * @param      type - the token type
 * @return        t - the new token
 */
token * init_token(char * t_literal, token_type type) { 
  token * t = calloc(1, sizeof(struct TOKEN_T));
  size_t len = (strnlen(t_literal, MAX_TOK_LEN) + 1);
  t->t_literal = calloc(len, sizeof(char));
  strncpy(t->t_literal, t_literal, len);
  t->type = type;
  return t;
}

/**
 * This function dumps the debugging info for a token (i.e. prints it and all
 * related values).
 * @param    t - the token to be debugged
 * @return N/a
 */
void token_dump_debug(token * t) {
  if(t) {
    printf("Token:\n");
    if(t->t_literal)
      printf("t_literal: `%s` ", t->t_literal);
    printf("type: `%s`\n", token_type_to_string(t->type));
  } else {
    fprintf(stderr, "[TOKEN DUMP DEBUG]: uninitialized token sent to debug."
        "\nExiting.\n");
    exit(1);
  }
  printf("--\n");
}

/**
 * This function frees a given token
 * @param    t - the token to be freed
 * @return N/a
 */
void free_token(token * t) {
  if(t) {
    if(t->t_literal)
      free(t->t_literal);
    free(t);
  }
}
