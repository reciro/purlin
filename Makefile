CC = clang
CFLAGS = -Wall -Wextra
OUTPUT = main

main: main.c
	$(CC) main.c $(CFLAGS) -o $(OUTPUT)

.PHONY: run
run: main
	./main

clean: 
	rm $(OUTPUT)
