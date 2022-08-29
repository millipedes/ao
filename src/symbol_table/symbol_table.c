/**
 * @file   symbol_table.c
 * @brief  This file contains the functions related to the symbol_table data
 * structure.
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#define _POSIX_C_SOURCE 200809L
#include "include/symbol_table.h"

/**
 * This function initializes a symbol table to have no ancestors nor any
 * variables.
 * @param N/a
 * @return st - The newly initialized symbol_table.
 */
symbol_table * init_symbol_table(void) {
  symbol_table * st = calloc(1, sizeof(struct SYMBOL_TABLE_T));
  st->udv = NULL;
  st->qty_udv = 0;
  st->previous = NULL;
  return st;
}

/**
 * This function finds the name of the variable queried by the parameter.
 * @param   st - The symbol_table to be queried.
 * @param name - The name of the variable to be found.
 * @return  -1 - The variable was not found.
 *           i - The variable was found at index i.
 */
int find_variable(symbol_table * st, const char * name) {
  for(int i = 0; i < st->qty_udv; i++)
    if(!strncmp(st->udv[i]->name, name, MAX_TOK_LEN))
      return i;
  return -1;
}

/**
 * This function adds a variable to the symbol_table.
 * @param   st - The symbol_table for the given process stack.
 * @param  var - The variable to be added to the symbol_table.
 * @return N/a
 */
void add_variable(symbol_table * st, variable * var) {
  st->qty_udv++;
  if(st->qty_udv == 1)
    st->udv = calloc(1, sizeof(struct VARIABLE_T *));
  else
    st->udv = realloc(st->udv, st->qty_udv * sizeof(struct VARIABLE_T *));
  st->udv[st->qty_udv - 1] = var;
}

void add_variable_at_index(symbol_table * st, variable * var, int index) {
  if(st->udv[index])
    st->udv[index] = var;
}

/**
 * This function frees a symbol_table.
 * @param   st - The symbol_table to be freed.
 * @return N/a
 */
void free_symbol_table(symbol_table * st) {
  if(st) {
    if(st->udv) {
      for(int i = 0; i < st->qty_udv; i++)
        if(st->udv[i])
          free_variable(st->udv[i]);
      free(st->udv);
    }
    if(st->previous)
      free_symbol_table(st->previous);
    free(st);
  }
}
