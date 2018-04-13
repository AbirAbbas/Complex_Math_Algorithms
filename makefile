all: clean main

run: clean all execute

main: ./bin/Question1.o ./bin/Question2.o
	gcc -o ./bin/program -Iinclude ./src/main.c ./bin/Question1.o ./bin/Question2.o -lm

./bin/Question1.o: ./src/Question1.c
	gcc -c -Iinclude ./src/Question1.c -o ./bin/Question1.o -lm
	
./bin/Question2.o: ./src/Question2.c
	gcc -c -Iinclude ./src/Question2.c -o ./bin/Question2.o -lm

execute:
	./bin/program
	
clean:
	rm -f ./bin/*.o
	rm -f ./bin/program
