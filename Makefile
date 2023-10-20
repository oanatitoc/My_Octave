# Copyright Oana-Alexandra Titoc 313CAb 2022-2023


# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c -o my_octave


pack:
	zip -FSr 313CA_TitocOana-Alexandra_Tema2.zip README Makefile *.c *.h

clean:
	rm -f *.o $(TARGETS)

.PHONY: pack clean

