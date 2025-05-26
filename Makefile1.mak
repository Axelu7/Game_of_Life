CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = Task1_main.c Task1_functions.c

OBJS = $(SRCS:.c=.o)

EXEC = Game_of_Life

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC)