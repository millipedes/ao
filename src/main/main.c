#include <stdio.h>
#include "../lexer/include/lexer.h"
#include "../token/include/token_stack.h"
#include "../parser/include/parser.h"

int main(void) {
  lexer * lex = init_lexer("123 + 123 * 123.123\n");
  token_stack * ts = lex_source(lex);
  token_stack * rev = reverse_stack(&ts);
  ast * abstree = parse_expression(&rev);
  ast_dump_debug(abstree);
  free_ast(abstree);
  while(rev)
    rev = pop_token(rev);
  while(ts)
    ts = pop_token(ts);
  free_lexer(lex);
  return 0;
}
