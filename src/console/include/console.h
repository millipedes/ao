/**
 * @file   console.c
 * @brief  This file contains the function definitions for console.c
 * @author Matthew C. Lindeman
 * @date   August 29, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef SOL_H
#define SOL_H

#include "menu.h"
#include "../../lexer/include/lexer.h"
#include "../../main/include/constants.h"
#include "../../parser/include/abstract_syntax_tree.h"
#include "../../parser/include/parser.h"
#include "../../symbol_table/include/symbol_table.h"

void repl(void);

#endif
