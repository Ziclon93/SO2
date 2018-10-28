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
/**
 *
 *  Main function. Contains a simple example using a red-black-tree. 
 *
 */

int main(int argc, char **argv)
{
    int maxnum, ct,SIZE;
    char *a; 

    rb_tree *tree;
    node_data *n_data;


    list * lista_origen;
    list_data *l_data;
    list_item *l_item;

    /* Random seed */
    srand(time(NULL));

    tree = (rb_tree *) malloc(sizeof(rb_tree));

    init_tree(tree);

    FILE *fp;
    char str[100];

    /* opening file for reading */
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

    for(int i=0; i < SIZE; i++){
        if( fgets (str, 100, fp)!=NULL )
        {
            puts(str);
            str[strlen(str) -1] = '\0';
            
            //Añadimos el nodo correspondiente al arbol

            // Busca si hay un nodo igual 
            n_data = find_node(tree, str); 

            // Si lo hay aumenta el numero de accesos
            if (n_data != NULL) {
                n_data->num_vegades++;
            } else {    // Si no, hay que crear los datos   
                        // y insertar el nodo en el arbol
                        // con esos datos

                
		// Inicializamos la lista enlazada
                list *l;
                l = (list *) malloc(sizeof(list));
                init_list(l);

		// Creamos los datos para el nodo del arbol

                n_data = malloc(sizeof(node_data));

                // Key son los nodos origen
                n_data->key = str;

                // Guardamos la informacion adicional
                n_data->num_vegades = 1;
		// Asignamos la lista
                n_data->link = l;   
                
                // Insertamos el nodo
                insert_node(tree, n_data);
            }

        }
    }

    fclose(fp);


    /* opening file for reading */
    fp = fopen(argv[2] , "r");

    SIZE = 0;  //deberia valer para cualquier size

    char retrasoChar[100];
    int retraso;
    char origen[100]; 
    char destino[100];

    char row[1000];
    // deberia ser un while, hasta que no hubiera siguiente linea

    if( fgets (row, 1000, fp)!=NULL )
	{
		/* writing content to stdout */
		puts(row);
        SIZE = strlen(row);
	}


    printf("-----------FOR DEL CSV---------\n");
    while (fgets(row, SIZE, fp)){
        puts(row);
        row[strlen(row) -1] = '\0';

        spliter(row,15,retrasoChar);
        retraso = atoi(retrasoChar);
        spliter(row,17,origen);
        spliter(row,18,destino);

        printf("%d \n%s \n%s \n", retraso,origen,destino);
        printf("--------------------\n");
        
        

        // Es mas o menos como deberia ir, hay que hacer la funcion de las subcadenas
        // y mirar si hay que cambiar algo de aqui

        // esto depende de nuestra función para extraer subcadenas:
        
        // Buscamos el nodo en el arbol
        puts("ppp");
        n_data = find_node(tree, origen);
        printf("kkk %d",n_data->num_vegades);
        puts("kkk");
        
        if (n_data != NULL) {
            /*
            l_data = find_list(n_data->link, destino); 

            if (l_data != NULL) {

                l_data->num_times++;
            } else {

                l_data = malloc(sizeof(list_data));
                l_data->key = destino;
                l_data->num_times = 1;

                insert_list(n_data->link, l_data);
            }
            */
        } else { 
            puts("eee");

        // Si no está reservamos memoria y lo añadimos, aunque realmente es un caso
        // imposible
            n_data = malloc(sizeof(node_data));
            n_data->key = origen;     
            n_data->num_vegades = 1;

            insert_node(tree, n_data);
            
        }
            
        //printf("Es este: %s \n",n_data->link->first->data->key);

        // Cogemos la lista del nodo encontrado
        //lista_origen = n_data->link;
    
         //NO FUNCIONA , no sabemos porque.

        // buscamos si el destino esta en la lista

        //l_data = find_list(lista_origen, destino); 
        /*
        if (l_data != NULL) {
            // Si está sumamos un vuelo y el retraso al total
            l_data->num_times++;
            l_data->retraso = (l_data->retraso* l_data->num_times-1) + retraso/ l_data->num_times;

        } else {
            // Si no esta en la lista reservamos memoria y lo añadimos
            l_data = malloc(sizeof(list_data));
            l_data->key = a;
            l_data->retraso = retraso;
            l_data->num_times = 1;

            insert_list(lista_origen, l_data);
        }
        */
        
    }

    

    fclose(fp);

    /*

    char * value = argv[3];

    //Encontramos el nodo que corresponde al origen que buscamos
    n_data = find_node(tree, value);
    
    //cogemos el item de la lista que contiene el retraso
     l_item = n_data->link->first;

    //mientras no sea null
    while (l_item != NULL) {
        l_data = l_item->data;
        //Imprimimos el destino y el retraso previamente calculado en la inserción.
         printf("Key %s appears %d times\n", l_data->key, l_data->retraso);
        l_item = l_item->next;
    }

    
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
    char *result = malloc(sizeof(char)*4);
    int var,max= 0;

    for(int i=0; i < SIZE; i++){
        if( fgets (str, 100, fp)!=NULL )
        {
            puts(str);
            str[strlen(str) -1] = '\0';

            //Todos han sido añadidos anteriormente
            n_data = find_node(tree, str);

            var = n_data->link->num_items;

            //si el valor obtenido es superior al maximo encontrado
            if (var>max){
                //Sera de medida 4 (los 3 caracteres y el \0)
                result = str;
                max = var;
            }

        }
    }

    printf(" El aeropuerto con mas destinaciones es: %s", result);

    fclose(fp);
    */
    
}
