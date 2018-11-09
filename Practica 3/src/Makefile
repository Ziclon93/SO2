practica3: practica3.o red-black-tree.o linked-list.o
	gcc -o practica3 practica3.o ./arbre-binari/red-black-tree.o	./linked-list/linked-list.o


practica3.o: practica3.c ./arbre-binari/red-black-tree.h ./linked-list/linked-list.h
	gcc -c practica3.c

red-black-tree.o: ./arbre-binari/red-black-tree.c ./arbre-binari/red-black-tree.h
	gcc -c ./arbre-binari/red-black-tree.c


linked-list.o: ./linked-list/linked-list.c ./linked-list/linked-list.h
	gcc -c ./linked-list/linked-list.c


run:	./practica3
	./practica3


clean:
	rm practica3.o practica3 red-black-tree.o linked-list.o
