/**
 * @file   console.c
 * @brief  This file is responsible for the functions relating to the language
 * REPL.
 * @author Matthew C. Lindeman
 * @date   August 29, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/console.h"

/**
 * This function starts the REPL and will not end until the user sends the
 * command "exit".
 * @param  N/a
 * @return N/a
 */
void repl(void) {
  char buf[MAX_TOK_LEN];
  lexer * lex = NULL;
  token_stack * ts = NULL;
  token_stack * rev = NULL;
  ast * abstree = NULL;
  ast_result * astr = NULL;
  symbol_table * st = init_symbol_table();
  print_logo();
  print_information();
  while(1) {
    printf("|> ");
    fgets(buf, MAX_TOK_LEN, stdin);
    if(!strncmp("exit\n", buf, MAX_TOK_LEN))
      break;
    lex = init_lexer(buf);
    ts = lex_source(lex);
    rev = reverse_stack(&ts);
    abstree = parse_expression(&rev, &st);
    astr = evaluate_tree(abstree, &st);
    ast_result_dump_debug(astr);
    free_ast(abstree);
    free_ast_result(astr);
    while(rev)
      rev = pop_token(rev);
    while(ts)
      ts = pop_token(ts);
    free_lexer(lex);
  }
  free_symbol_table(st);
}
