#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>	

#include "arbre-binari/red-black-tree.h"

#define MAXVALUE 10

/*
char * spliter(char* cadena, int columnF, char* result){

    printf("---------spliter-----------\n");
    char * prov = malloc(sizeof(char*));
    int current = 0, column = 0;
    int i;

    printf(" aqui estoy: %s \n",cadena);

    for(i= 0; i < strlen(cadena); i++){

        printf("----------Dentro del for----------\n");
        printf("%ld\n",strlen(cadena));

        if(cadena[i] == ','){
            column++;
            if (column == columnF){
                strcpy(result,prov);
            }else{
                strcpy(prov, "");
            }
        }
        else{
            current = strlen(prov);
            prov[current] = cadena[i];
            prov[current+1] = '\0';
        }
    }

    free(prov);
    
}
*/
/**
 *
 *  Main function. Contains a simple example using a red-black-tree. 
 *
 */

int main(int argc, char **argv)
{

    FILE *fp;
    char str[100];
    int SIZE,i;
    char *row;

    row = malloc(sizeof(char*));

    rb_tree *tree;
    node_data *n_data;


    tree = (rb_tree *) malloc(sizeof(rb_tree));

    fp = fopen(argv[1] , "r");

    if(fp == NULL)
    {
        perror("Error opening file");
        return(-1);
    }
    if( fgets (str, 100, fp)!=NULL )
    {
        puts(str);
        str[strlen(str) -1] = '\0';
    }

    SIZE = atoi(str);

    for(i=0; i < SIZE; i++){
        if( fgets (str, 100, fp)!=NULL )
        {
            puts(str);
            str[strlen(str) -1] = '\0';

            strcpy(row,str);
            
            printf("-%s-\n", row);
            //Añadimos el nodo correspondiente al arbol

            if (i==0){

                n_data = malloc(sizeof(node_data));
                n_data->key = row;
                n_data->num_vegades = 1;
                insert_node(tree, n_data);
            }
            else{
                n_data = find_node(tree, row); 

                if (n_data != NULL) {
                    n_data->num_vegades++;
                } else {
                    n_data = malloc(sizeof(node_data));
                    n_data->key = row;
                    n_data->num_vegades = 1;
                    insert_node(tree, n_data);
                }
            }
            
        }
    }

    delete_tree(tree);
    free(tree);

    fclose(fp);
    
}
