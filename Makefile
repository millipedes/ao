CC=gcc -g -Wall -Wextra -std=c99
CFILES=$(wildcard src/*/*.c)
HFILES=$(wildcard src/*/include/*.h)
OBJFILES=$(CFILES:.c=.o)
OBJPATH=src/objects/
EXEFILE=bin/main

all:$(OBJFILES)
	$(CC) $(OBJFILES) -o $(EXEFILE) -lm

%.o: %.c $(HFILES)%.h
	$(CC) -c $(CFILES) $< -o $@ -lm

vim:
	nvim $(CFILES) 

vimh:
	nvim $(HFILES) 

run:
	$(EXEFILE)

memcheck:
	valgrind $(EXEFILE) --leak-check=full --read-var-info

file:
	$(EXEFILE) docs/phase1.ao

fmemcheck:
	valgrind $(EXEFILE) docs/phase1.ao --leak-check=full --read-var-info

debug:
	gdb -q $(EXEFILE)

feh:
	feh docs/uml.png&

plant:
	plantuml docs/uml.txt
	convert docs/uml.png -channel RGB -negate docs/uml.png

git-add:
	git add Makefile README.md src/ docs/ tests/ TODO.txt

clean:
	rm $(OBJFILES)
