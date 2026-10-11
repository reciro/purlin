CC = clang
CFLAGS = -g -Wall -Wextra
OUTPUT = purlin

main: purlin.c 
	$(CC) purlin.c $(CFLAGS) -o $(OUTPUT)

.PHONY: run
run: main
	./purlin --threads=16 --cores=16

clean: 
	rm $(OUTPUT)
