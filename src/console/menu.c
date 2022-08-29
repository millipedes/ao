#include "include/menu.h"

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

void print_information(void) {
  printf("|This is the REPL for the ao programming      |\n");
  printf("|language. For More Information see:          |\n");
  printf("|https://github.com/millipedes/ao             |\n");
  printf("|To run a program in ao use the source code as|\n");
  printf("|an argument for the binary.                  |\n");
  printf("===============================================\n");
}
