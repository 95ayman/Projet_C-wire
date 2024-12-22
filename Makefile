all: exec

exec: main.o AVL_Function.o Filter.o Printfile.o
	gcc main.o AVL_Function.o Filter.o Printfile.o -o exec

main.o: main.c function.h
	gcc -c main.c -o main.o
dataAVL.o: AVL_Function.c function.h
	gcc -c AVL_Function.c -o AVL_Function.o
Filter.o: Filter.c function.h
	gcc -c Filter.c -o Filter.o
Printfile.o: Printfile.c function.h
	gcc -c Printfile.c -o Printfile.o

clean:
	rm -f *.o
	rm -f exec
