CC=gcc
CFLAGS=-Wall -Werror -I./include
LDFLAGS=-L./src 

all: src/dfs.x

src/dfs.x: src/dfs.o src/functions.o src/mazeEnv.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

src/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o

realclean: clean
	rm -f src/*.x