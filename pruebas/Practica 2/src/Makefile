practica2: practica2.o red-black-tree.o linked-list.o
	gcc -o practica2 practica2.o ./arbre-binari/red-black-tree.o	./linked-list/linked-list.o
	
	
practica2.o: practica2.c ./arbre-binari/red-black-tree.h ./linked-list/linked-list.h
	gcc -c practica2.c
	
red-black-tree.o: ./arbre-binari/red-black-tree.c ./arbre-binari/red-black-tree.h
	gcc -c ./arbre-binari/red-black-tree.c


linked-list.o: ./linked-list/linked-list.c ./linked-list/linked-list.h
	gcc -c ./linked-list/linked-list.c


run:	./practica2
	./practica2 ./aeroports/aeroports.csv ./dades/dades.csv ORI


clean:
	rm practica2.o practica2 red-black-tree.o linked-list.o
