#pragma once

#include "linked-list.h"
#include "red-black-tree.h"

#define MAXCHAR 500

#define ATRASO_LLEGADA_AEROPUERTO 15
#define AEROPUERTO_ORIGEN 17
#define AEROPUERTO_DESTINO 18

//NUMTHREADS ahora sera el numero de consumidores que tenemos
#define NUMTHREADS 10 
#define NUMLINES 1000


typedef struct flight_information {
    char origin[4];
    char destination[4];
    int delay;
} flight_information;

struct parametres {
  /*int i;
  int j;
  char *str;
  */
  rb_tree *tree;
  FILE *fp;
};

typedef struct read_params{
    FILE *fp;

    int sending;

    struct buffer *buff;
	
} read_params;

typedef struct process_params{
    rb_tree *tree;

    int sending;
    int end;

    struct buffer *buff;
} process_params;

struct cell{

	char str[1000];
	int size;

};

struct buffer{
	int size;

	struct cell *cell[NUMTHREADS];
};



rb_tree *create_tree(char *str_airports, char *str_dades);
void read_airports(void *arg);
//void read_airports_data(rb_tree *tree, FILE *fp);
void insert_node_trees(char *origin,char *desination, int delay , struct parametres *par);

void *th_read_airports_data(void *arg);
void *productor(void *arg);
void *consumidor(void *arg);
void *leer_fichero(void *arg);
void *procesar_fichero(void *arg);
