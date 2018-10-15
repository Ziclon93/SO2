/**
 *
 * Main file 
 * 
 * This file calls the red-black-tree.c functions.
 *
 * Lluis Garrido, June 2018.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>	

#include "arbre-binari/red-black-tree.h"
#include "linked-list/linked-list.h"

#define MAXVALUE 10

/**
 *
 *  Main function. Contains a simple example using a red-black-tree. 
 *
 */

int main(int argc, char **argv)
{
    int maxnum, ct;
    char *a; 

    rb_tree *tree;
    node_data *n_data;

    tree = (rb_tree *) malloc(sizeof(rb_tree));

    init_tree(tree);

    FILE *fp;
    char str[1000];

    /* opening file for reading */
    fp = fopen("aeroports/aeroports.csv" , "r");

    if(fp == NULL)
    {
        perror("Error opening file");
        return(-1);
    }
    if( fgets (str, 100, fp)!=NULL )
    {
        puts(str);
    }

    int SIZE = atoi(str);


    for(int i=0; i < SIZE; i++){
        if( fgets (str, 100, fp)!=NULL )
        {
            puts(str);
            str[strlen(str) -1] = '\0';
            
            //Añadimos el nodo correspondiente al arbol

            a = str;

            n_data = find_node(tree, a); 

            if (n_data != NULL) {
                n_data->num_vegades++;
            } else {


                list *l;
                list_item *l_item;
                list_data *l_data;

                l = (list *) malloc(sizeof(list));
                init_list(l);



                n_data = malloc(sizeof(node_data));
                n_data->retraso = 0;
                n_data->key = a;
                
                n_data->num_vegades = 1;

                insert_node(tree, n_data);
            }

        }
    }

    fclose(fp);


    /* opening file for reading */
    fp = fopen("dades/dades.csv" , "r");

    SIZE = 10001;

    char**listDades = malloc(SIZE*sizeof(char*));

    for(int i=0; i < SIZE; i++){
        if( fgets (str, 1000, fp)!=NULL ){
            puts(str);
            str[strlen(str) -1] = '\0';


            char *strsplit  = strtok(str, ",");

            int retraso;
            char *origen, *destino;

            for (int val = 2; val < 19; val++){
                strsplit = strtok(NULL, ",");
                if (val == 15){
                    retraso = atoi(strsplit);
                }
                else if (val == 17){
                    origen = strsplit;
                }
                else if (val == 18){
                    destino = strsplit;
                }
            }
            

            n_data = find_node(tree, a); 

            //En nuestro caso siempre estará pero, no quiero ser redundante con el codigo.
            if (n_data != NULL){
                n_data

            }



        }
    }

    fclose(fp);
}