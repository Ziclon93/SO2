#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>	

#include "arbre-binari/red-black-tree.h"
#include "linked-list/linked-list.h"

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
    int SIZE;

    rb_tree *tree;
    node_data *n_data;

    list *l;
    list_item *l_item;
    list_data *l_data;


    tree = (rb_tree *) malloc(sizeof(rb_tree));
    init_tree(tree);

    fp = fopen(argv[1] , "r");

    if(fp == NULL)
    {
        perror("Error opening file");
        return(-1);
    }
    if( fgets (str, 100, fp)!=NULL )
    {
        puts(str);
    }

    SIZE = atoi(str);
    char *pruebas = "AKA";

    for(int i=0; i < SIZE; i++){
        if( fgets (str, 100, fp)!=NULL )
        {
            puts(str);
            str[strlen(str) -1] = '\0';
            if ( i%2 != 0){
                pruebas = str;
            }
            
            //Añadimos el nodo correspondiente al arbol
            printf("Esta es la comparación: %ld, %ld, %d\n", strlen(pruebas), strlen(str), strcmp(str,pruebas));

            
            n_data = find_node(tree, str); 


            if (n_data != NULL) {
                n_data->num_vegades++;
                printf("hey :%s, num vegades: %d\n",n_data->key, n_data->num_vegades);        
            } 
            else {

                l = (list *) malloc(sizeof(list));
                init_list(l);

                n_data = malloc(sizeof(node_data));
                n_data->key = str;
                n_data->link = l;
                n_data->num_vegades = 1;
                insert_node(tree, n_data);
                printf("JUE\n");

            }
            
        }
    }
    
    n_data = find_node(tree, pruebas); 
    printf("FINAL : %s\n", n_data->key);

    if(n_data != NULL){
        printf("Numero de vegades en nodo: %d\n", n_data->num_vegades);
    }
    
    delete_tree(tree);
    free(tree);

    fclose(fp);
    
}
