EXEC = program

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = main.c functii.c
OBJS = $(SRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c header4.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

distclean: clean
	rm -f output.txt