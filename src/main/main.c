#include "../console/include/console.h"

int main(int argc, char *argv[]) {
  if(argc < 2)
    repl();
  else
    interpret(argv[1]);
  return 0;
}

