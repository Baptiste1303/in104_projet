CC=gcc
CFLAGS=-Wall -Werror -I../include
LDFLAGS=-L. 

all: dfs.x

dfs.x: dfs.o functions.o mazeEnv.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

realclean: clean
	rm -f *.x