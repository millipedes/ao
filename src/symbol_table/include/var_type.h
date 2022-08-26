/**
 * @file   var_type.h
 * @brief  This file contains the function definitions for var_type.c
 * @author Matthew C. Lindeman
 * @date   August 25, 2022
 * @bug    None known
 * @todo   Nothing
 */
#ifndef VRT_H
#define VRT_H

#include <stdio.h>
#include <stdlib.h>

/**
 * This enumeration is responsible for typing the variables used in the program.
 */
typedef enum {
  /** Type double, defined by c99 std. */
  DOUBLE,
  /** Type int, defined by c99 std. */
  INT,
  /** Type string, literal bytes on the program heap. */
  STRING
} var_type;

const char * var_type_to_string(var_type vt);

#endif
