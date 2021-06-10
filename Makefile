.PHONY = all
all: main

main: main.o
	gcc -Wall -Werror main.o -o main

main.o: main.c
	gcc -Wall -Werror -c main.c

.PHONY = clean
clean:
	rm -f main.o
