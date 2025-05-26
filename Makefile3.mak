EXEC = proiect

SRC = main.c functions.c

HEADER = header3.h

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(EXEC)


.PHONY: all clean