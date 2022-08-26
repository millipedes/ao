#include <stdio.h>
#include "../lexer/include/lexer.h"
#include "../token/include/token_stack.h"
#include "../parser/include/parser.h"
#include "../symbol_table/include/symbol_table.h"
#include "../symbol_table/include/variable.h"
#include "../symbol_table/include/var_type.h"

/**
 * This function tests the cases in which a symbol_table can be initialized.
 * @param  N/a
 * @return N/a
 */
symbol_table_test(void) {
  symbol_table * st = init_symbol_table();
  add_variable(st, init_variable("x", "1.2", DOUBLE));
  add_variable(st, init_variable("y", "some string", STRING));
  add_variable(st, init_variable("z", "1", INT));
  int i = find_variable(st, "x");
  int j = find_variable(st, "y");
  int k = find_variable(st, "z");
  variable_dump_debug(st->udv[i]);
  variable_dump_debug(st->udv[j]);
  variable_dump_debug(st->udv[k]);
  free_symbol_table(st);
}
