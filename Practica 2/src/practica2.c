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

char * spliter(char*cadena, int columnF){

    char * result = malloc(sizeof(char)*50);
    int current, column = 0;

    for(int i = 0; i < strlen(cadena); i++){

        if(cadena[i] == ','){
            column++;
            if (column == columnF){
                return result;
            }else{
                strcpy(result, "");
            }
        }
        else{
            current = strlen(result);
            result[current] = cadena[i];
            result[current+1] = '\0';
        }
    }

    return result;
    
}
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


    list * lista_origen;
    list_data *l_data;


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

    // No se si funciona, es mas o menos como deberia ir
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
    fp = fopen("dades/dades.csv" , "r");

    SIZE = 10001;  //deberia valer para cualquier size

    int retraso;
    char *origen, *destino;
    // deberia ser un while, hasta que no hubiera siguiente linea

    if( fgets (str, 10000, fp)!=NULL )
	{
		/* writing content to stdout */
		puts(str);
        SIZE = strlen(str);
	}

    while (fgets(str, SIZE, fp)){
        puts(str);
        str[strlen(str) -1] = '\0';

        retraso = atoi(spliter(str,15));
        origen = spliter(str,17);
        destino = spliter(str,18);

        printf("%d \n %s \n %s \n", retraso,origen,destino);
        
        
    
        // Es mas o menos como deberia ir, hay que hacer la funcion de las subcadenas
        // y mirar si hay que cambiar algo de aqui

        // esto depende de nuestra función para extraer subcadenas:
        
        // Buscamos el nodo en el arbol

        n_data = find_node(tree, origen);
        
        if (n_data != NULL) {
        // si está en el arbol incementamos el numero
            n_data->num_vegades++;
        } else { // (No deberia hacer falta, el arbol ya esta creado)

        // Si no está reservamos memoria y lo añadimos
            n_data = malloc(sizeof(node_data));
            n_data->key = origen;     
            n_data->num_vegades = 1;

            insert_node(tree, n_data);
        }
            

        // Cogemos la lista del nodo encontrado
        lista_origen = (list*) n_data->link;


        // buscamos si el destino esta en la lista
        l_data = find_list(lista_origen, destino);

        
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
        
        
    }

    fclose(fp);
}
