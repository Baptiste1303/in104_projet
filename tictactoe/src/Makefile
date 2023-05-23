CC=gcc
CFLAGS=-Wall -Werror -I../include
LDFLAGS=-L. 

all: tictactoe.x

tictactoe.x : tictactoe.o qlearning-tictactoe.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -lm

%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

realclean: clean
	rm -f *.x