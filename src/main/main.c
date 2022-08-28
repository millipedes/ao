#include <stdio.h>
#include "../lexer/include/lexer.h"
#include "../token/include/token_stack.h"
#include "../parser/include/parser.h"
#include "../symbol_table/include/symbol_table.h"
#include "../symbol_table/include/variable.h"
#include "../symbol_table/include/var_type.h"
#include "../parser/include/ast_result.h"

int main(void) {
  symbol_table * st = init_symbol_table();
  add_variable(st, init_variable("x", "string", STRING));
  add_variable(st, init_variable("y", "some string", STRING));
  add_variable(st, init_variable("z", "1.2", DOUBLE));
  // int i = find_variable(st, "x");
  // int j = find_variable(st, "y");
  // int k = find_variable(st, "z");
  // variable_dump_debug(st->udv[i]);
  // variable_dump_debug(st->udv[j]);
  // variable_dump_debug(st->udv[k]);

  lexer * lex = init_lexer("10.0 * 2.0 / 4.0\n");

  token_stack * ts = lex_source(lex);
  token_stack * rev = reverse_stack(&ts);
  ast * abstree = parse_expression(&rev, &st);
  ast_dump_debug(abstree);
  ast_result * astr = evaluate_tree(abstree, st);
  ast_result_dump_debug(astr);
  free_ast_result(astr);
  free_ast(abstree);
  while(rev)
    rev = pop_token(rev);
  while(ts)
    ts = pop_token(ts);
  free_lexer(lex);
  free_symbol_table(st);
  return 0;
}
