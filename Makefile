chess: main.o rules.o pieces.o saveload.o undo.o utility.o
	gcc ./bin/main.o ./bin/rules.o ./bin/pieces.o ./bin/saveload.o ./bin/undo.o ./bin/utility.o -o ./bin/chess

utility.o:
	gcc -c -I./ ./src/utility.c -o ./bin/utility.o

undo.o:
	gcc -c -I./ ./src/undo.c -o ./bin/undo.o

saveload.o:
	gcc -c -I./ ./src/saveload.c -o ./bin/saveload.o

pieces.o: utility.o
	gcc -c -I./ ./src/pieces.c -o ./bin/pieces.o

rules.o: pieces.o utility.o undo.o
	gcc -c -I./ ./src/rules.c -o ./bin/rules.o

main.o: rules.o
	gcc -c -I./ ./src/main.c -o ./bin/main.o
