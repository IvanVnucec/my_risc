.PHONY = all
all: main.a

.PHONY = run
run: main.a
	./main.a

main.a: main.o
	gcc -Wall -Werror main.o -o main.a

main.o: main.c
	gcc -Wall -Werror -c main.c

.PHONY = clean
clean:
	rm -f main.o main.a
