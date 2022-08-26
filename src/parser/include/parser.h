/**
 * @file   parser.h
 * @brief  This file contains the function definitions for parser.c
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef PAR_H
#define PAR_H

#include <math.h>
#include "abstract_syntax_tree.h"

ast * parse_expression(token_stack ** ts);
ast * parse_term(token_stack ** ts);
ast * parse_factor(token_stack ** ts);
ast * binary_tree(ast * parent, ast * left_child, ast * right_child);
ast * unary_tree(ast * parent, ast * child);
ast * simplify_tree(ast * abstree);

#endif

