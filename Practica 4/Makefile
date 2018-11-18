main: main.o red-black-tree.o linked-list.o estadisticas.o ficheros-csv.o read-write-tree.o
	gcc -o main main.o red-black-tree.o linked-list.o estadisticas.o ficheros-csv.o read-write-tree.o


main.o: main.c red-black-tree.h linked-list.h estadisticas.h ficheros-csv.h read-write-tree.h
	gcc -c main.c

red-black-tree.o: red-black-tree.c red-black-tree.h
	gcc -c red-black-tree.c


linked-list.o: linked-list.c linked-list.h
	gcc -c linked-list.c

estadisticas.o: estadisticas.c estadisticas.h
	gcc -c estadisticas.c

ficheros-csv.o: ficheros-csv.c ficheros-csv.h
	gcc -c ficheros-csv.c

read-write-tree.o: read-write-tree.c read-write-tree.h
	gcc -c read-write-tree.c




run:	./main
	./main


clean:
	rm main.o main red-black-tree.o linked-list.o  estadisticas.o ficheros-csv.o read-write-tree.o
