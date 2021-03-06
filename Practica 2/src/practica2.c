#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>	

#include "arbre-binari/red-black-tree.h"
#include "linked-list/linked-list.h"

#define MAXVALUE 10

char * spliter(char* cadena, int columnF, char* result){

    char * prov = malloc(sizeof(char)*100);
    int current = 0, column = 0;
    int i;


    for(i= 0; i < strlen(cadena); i++){

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

void recorrido(node *x){
    printf(" ReCORreMos LokoHh: %s\n", x->data->key);
    if (x->right != NIL)
        recorrido(x->right);

    if (x->left != NIL)
        recorrido(x->left);
}

/**
 *
 *  Main function. Contains a simple example using a red-black-tree. 
 *
 */

int main(int argc, char **argv)
{
    FILE *fp;
    char str[10000];
    char *row,*retrasoChar, *origen,*destino;
    int SIZE,retraso;

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
    row = malloc(sizeof(char)*1024);

    while(fgets(str, 100, fp)){
            //puts(str);
            str[3] = '\0';
            row = strdup(str);
            printf("-%s-\n", row);

            //Añadimos el nodo correspondiente al arbol

            l = (list *) malloc(sizeof(list));
            init_list(l);

            n_data = malloc(sizeof(node_data));
            
            n_data->key =malloc(sizeof(char)*4);
            strcpy(n_data->key,row);

            n_data->link = l;
            n_data->num_vegades = 1;

            insert_node(tree, n_data);

    }

    fclose(fp);

    fp = fopen(argv[2] , "r");
    

    if(fgets(str, 1024, fp)){
        puts(str);
        SIZE = sizeof(str);
    }
    
    retrasoChar = malloc(sizeof(char*));
    origen = (char*)malloc(sizeof(char)*4);
    destino = (char*)malloc(sizeof(char)*4);



    printf("-----------FOR DEL CSV---------\n");
    while (fgets(str, SIZE, fp) != NULL){
        //puts(row);
        row = str;
        row[strlen(row) -1] = '\0';

        spliter(row,15,retrasoChar);
        if (strcmp(retrasoChar,"NA") == 0){
            retraso = 0;
        }
        else{
            retraso = atoi(retrasoChar);
        }
        spliter(row,17,origen);
        spliter(row,18,destino);
        //printf("--------------------\n");
        //printf("%d \n%s \n%s \n", retraso,origen,destino);
        //printf("--------------------\n");
        // Buscamos el nodo en el arbol
        

        n_data = find_node(tree, origen);
        //printf("Nodo encontrado %s,  %d\n",n_data->key,n_data->num_vegades);
        n_data->num_vegades++;
        
        if (n_data != NULL) {
            l_data = find_list(n_data->link, destino); 

            if (l_data != NULL) {
                l_data->num_times+=1;
                l_data->retraso = (l_data->retraso* (l_data->num_times-1)) + retraso/ l_data->num_times;
                //printf("Nodo de lista ya existente %s,  %d\n",l_data->key,l_data->num_times);
            } else {

                l_data = malloc(sizeof(list_data));

                l_data->key = malloc(sizeof(char)*4);
                strcpy(l_data->key,destino);

                l_data->num_times = 1;
                l_data->retraso = retraso;

                insert_list(n_data->link, l_data);
            }
        } else { 
            puts("else: (añadimos nodo, no debería)");

        // Si no está reservamos memoria y lo añadimos, aunque realmente es un caso
        // imposible
            n_data = malloc(sizeof(node_data));
            n_data->key = origen;     
            n_data->num_vegades = 1;

            insert_node(tree, n_data);
            
        }
        
    }



    fclose(fp);

    n_data = find_node(tree, argv[3]);
    
        
    printf("Es este: %s \n",n_data->link->first->data->key);
    printf("El root es: %s\n", tree->root->left->data->key);
    recorrido(tree->root);
    

    
    delete_tree(tree);
    free(tree);

    free(row);
    free(retrasoChar);
    free(origen);
    free(destino);
    
}
