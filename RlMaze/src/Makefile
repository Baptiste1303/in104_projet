CC=gcc
CFLAGS=-Wall -Werror -I../include
LDFLAGS=-L. 

all: qlearning.x

qlearning.x: qlearning.o functions.o mazeEnv.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

dfs.x: dfs.o functions.o mazeEnv.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

realclean: clean
	rm -f *.x