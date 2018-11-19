#pragma once

#include "linked-list.h"
#include "red-black-tree.h"

#define MAXCHAR 500

#define ATRASO_LLEGADA_AEROPUERTO 15
#define AEROPUERTO_ORIGEN 17
#define AEROPUERTO_DESTINO 18

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



rb_tree *create_tree(char *str_airports, char *str_dades);
void read_airports(void *arg);
void read_airports_data(rb_tree *tree, FILE *fp);
void insert_node_trees(flight_information *fi_list, struct parametres *par);

void th_read_airports_data(void *arg);
