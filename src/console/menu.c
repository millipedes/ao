/**
 * @file   menu.c
 * @brief  This file contains the stdio menus for the program.
 * @author Matthew C. Lindeman
 * @date   August 29, 2022
 * @bug    None known
 * @todo   Nothing
 */
#include "include/menu.h"

/**
 * This function prints the language logo.
 * @param  N/a
 * @return N/a
 */
void print_logo(void) {
  printf("===============================================\n");
  printf("| ▄▄▄· • ▌ ▄ ·. ▪   ▄▄·  ▄▄▄· ▄▄▄▄· ▄▄▌  ▄▄▄ .|\n");
  printf("|▐█ ▀█ ·██ ▐███▪██ ▐█ ▌▪▐█ ▀█ ▐█ ▀█▪██•  ▀▄.▀·|\n");
  printf("|▄█▀▀█ ▐█ ▌▐▌▐█·▐█·██ ▄▄▄█▀▀█ ▐█▀▀█▄██▪  ▐▀▀▪▄|\n");
  printf("|▐█ ▪▐▌██ ██▌▐█▌▐█▌▐███▌▐█ ▪▐▌██▄▪▐█▐█▌▐▌▐█▄▄▌|\n");
  printf("| ▀  ▀ ▀▀  █▪▀▀▀▀▀▀·▀▀▀  ▀  ▀ ·▀▀▀▀ .▀▀▀  ▀▀▀ |\n");
  printf("|       ▄▄▄· ▄▄▄·▪  ·▄▄▄▄   ▄▄▄·  ▐ ▄         |\n");
  printf("|▪     ▐█ ▄█▐█ ▄███ ██▪ ██ ▐█ ▀█ •█▌▐█        |\n");
  printf("| ▄█▀▄  ██▀· ██▀·▐█·▐█· ▐█▌▄█▀▀█ ▐█▐▐▌        |\n");
  printf("|▐█▌.▐▌▐█▪·•▐█▪·•▐█▌██. ██ ▐█ ▪▐▌██▐█▌        |\n");
  printf("| ▀█▄▀▪.▀   .▀   ▀▀▀▀▀▀▀▀•  ▀  ▀ ▀▀ █▪        |\n");
  printf("===============================================\n");
}

/**
 * This function prints the language information menu.
 * @param  N/a
 * @return N/a
 */
void print_information(void) {
  printf("|This is the REPL for the ao programming      |\n");
  printf("|language. For More Information see:          |\n");
  printf("|https://github.com/millipedes/ao             |\n");
  printf("|To run a program in ao use the source code as|\n");
  printf("|an argument for the binary.                  |\n");
  printf("===============================================\n");
}
