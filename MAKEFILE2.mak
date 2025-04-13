CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = Task2_main.c Task2_functions.c Task2_bonus.c
HDR = header2.h
OUT = task2

all: $(OUT)

$(OUT): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT) InputData.txt out.txt bonus_out.txt

clean:
	rm -f $(OUT)