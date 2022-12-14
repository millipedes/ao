/**
 * @file   symbol_table.h
 * @brief  This file contains the function definitions for symbol_table.c
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef SYT_H
#define SYT_H

#include <string.h>
#include "variable.h"
#include "../../main/include/constants.h"

/**
 * This struct is used to manage the memory of each process stack frame.
 */
typedef struct SYMBOL_TABLE_T {
  /** List of user defined variables. */
  variable ** udv;
  /** The previous process stack frame. */
  struct SYMBOL_TABLE_T * previous;
  /** Quantity of user defined variables. */
  int qty_udv;
} symbol_table;

symbol_table * init_symbol_table(void);
int find_variable(symbol_table * st, const char * name);
void add_variable(symbol_table * st, variable * var);
void add_variable_at_index(symbol_table * st, variable * var, int index);
void free_symbol_table(symbol_table * st);

#endif
