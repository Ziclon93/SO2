#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>	

#include "arbre-binari/red-black-tree.h"
#include "linked-list/linked-list.h"

#define MAXVALUE 10

char * spliter(char* cadena, int columnF, char* result){

    char * prov = malloc(sizeof(char*));
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
    if (x->right != NULL)
        recorrido(x->right);

    if (x->left != NULL)
        recorrido(x->left);
}

/**
 *
 *  Main function. Contains a simple example using a red-black-tree. 
 *
 */

int main(int argc, char **argv)
{

    FILE *fp1,*fp2;
    char str[100];
    char *row,*retrasoChar, *origen,*destino;
    int SIZE,retraso;

    rb_tree *tree;
    node_data *n_data;

    list *l;
    list_item *l_item;
    list_data *l_data;


    tree = (rb_tree *) malloc(sizeof(rb_tree));
    init_tree(tree);

    fp1 = fopen(argv[1] , "r");

    if(fp1 == NULL)
    {
        perror("Error opening file");
        return(-1);
    }
    if( fgets (str, 100, fp1)!=NULL )
    {
        puts(str);
    }

    SIZE = atoi(str);

    row = malloc(sizeof(char*));

    while (fgets(str, 5, fp1) != NULL){
        printf("------\n");
        //puts(str);
        str[3] = '\0';
        str[4] = '\0';
        row = strdup(str);
        printf("-%s-", row);

        //Añadimos el nodo correspondiente al arbol

        
        n_data = find_node(tree, row); 


        if (n_data != NULL) {
            n_data->num_vegades++;
            printf("ADIOS\n");
            printf("------\n");
        } 
        else {

            l = (list *) malloc(sizeof(list));
            init_list(l);

            n_data = malloc(sizeof(node_data));
            
            n_data->key =row;
            n_data->link = l;
            n_data->num_vegades = 1;
            insert_node(tree, n_data);

            printf("HOLA\n");
            printf("------\n");

        }

    }

    fclose(fp1);

    /* opening file for reading */
    fp2 = fopen(argv[2] , "r");
    

    if( fgets (row, 1000, fp2)!=NULL )
	{
		/* writing content to stdout */
		puts(row);
        SIZE = strlen(row);
	}
    
    retrasoChar = malloc(sizeof(char*));
    origen = malloc(sizeof(char*));
    destino = malloc(sizeof(char*));


    printf("-----------FOR DEL CSV---------\n");
    while (fgets(str, SIZE, fp2) != NULL){
        puts(row);
        row = strdup(str);
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
    /*
        printf("--------------------\n");
        printf("%d \n%s \n%s \n", retraso,origen,destino);
        printf("--------------------\n");
        */
        // Buscamos el nodo en el arbol
        

        n_data = find_node(tree, origen);
        printf("Nodo encontrado %s,  %d\n",n_data->key,n_data->num_vegades);
        n_data->num_vegades++;
        
        if (n_data != NULL) {
            l_data = find_list(n_data->link, destino); 

            if (l_data != NULL) {
                l_data->num_times+=1;
                l_data->retraso = (l_data->retraso* (l_data->num_times-1)) + retraso/ l_data->num_times;
                printf("Nodo de lista ya existente %s,  %d\n",l_data->key,l_data->num_times);
            } else {

                l_data = malloc(sizeof(list_data));
                l_data->key = malloc(sizeof(char*));
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


    fclose(fp2);

    n_data = find_node(tree, argv[3]);
        
    printf("Es este: %s \n",n_data->link->first->data->key);
    printf("El root es: %s\n", tree->root->data->key);
    recorrido(tree->root);
    


    delete_tree(tree);
    free(tree);
}
