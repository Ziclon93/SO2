#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "arbre-binari/red-black-tree.h"
#include "linked-list/linked-list.h"

#define MAXVALUE 10
#define MAXLINE      200
#define MAGIC_NUMBER 0x0133C8F9

int menu()
{
    char str[5];
    int opcio;

    printf("\n\nMenu\n\n");
    printf(" 1 - Creacio de l'arbre\n");
    printf(" 2 - Emmagatzemar arbre a disc\n");
    printf(" 3 - Llegir arbre de disc\n");
    printf(" 4 - Consultar informacio de l'arbre\n");
    printf(" 5 - Sortir\n\n");
    printf("   Escull opcio: ");

    fgets(str, 5, stdin);
    opcio = atoi(str);

    return opcio;
}

char * spliter(char* cadena, int columnF, char* result){

    char * prov = malloc(sizeof(char)*100);
    int current = 0, column = 0;

    for(int i = 0; i < strlen(cadena); i++){

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

int calcular_numero_nodes(node *n){
    int r = 0;
	int l = 0;

	if (n->right != NIL)
		r = calcular_numero_nodes(n->right);

	if (n->left != NIL)
		l = calcular_numero_nodes(n->left);

	return r + l + 1;

}

int calcular_lista_num(list *l){
    list_item *current;
    int result = 0;
    current = l->first;
    while (current != NULL){
        result +=1;
        current = current->next;
    }
    return result;
}

void guardar_llista(list *l, FILE *fp){
	int n_vols, retras;
	list_item *item;
	item = l->first;

	while(item != NULL){
		// Guardem el destí
		fwrite(item->data->key, sizeof(char), 3, fp);

		// Guardem el nombre de vols
		//n_vols = item->data->num_times;
		fwrite(&(item->data->num_times), sizeof(int), 1, fp);

		// Guardem el retràs
		//retras = item->data->retraso;
		fwrite(&(item->data->retraso), sizeof(int), 1, fp);

		item = item->next;
	}
}

void guardar_node(node_data *d, FILE *fp){
	//int n_elements;
	// Guardem l'origen
	fwrite(d->key, sizeof(char), 3, fp);

	// Calculem i guardem el número d'elements
	//n_elements = calcular_lista_num(d->link);
	fwrite(&(d->num_vegades), sizeof(int), 1, fp);

	// Guardem els elements de la llista
	guardar_llista(d->link, fp);

}


void guardar_arbre(node *n, FILE *fp){

	if (n->left != NIL){
        guardar_arbre(n->left,fp);
    }

	guardar_node(n->data, fp);

    if (n->right != NIL){
        guardar_arbre(n->right,fp);
    }
}

void carregar_llista(list *l, int n, FILE *fp){
	list_data *data;
	int n_vols, retras;

	for(int i = 0; i < n; i++){
		data = malloc(sizeof(list_data));
		data->key = malloc(sizeof(char)*4);

		fread(data->key, sizeof(char), 3, fp);
		data->key[3] = '\0';

		fread(&n_vols, sizeof(int), 1, fp);
		data->num_times = n_vols;

		fread(&retras, sizeof(int), 1, fp);
		data->retraso = retras;

		insert_list(l, data);
	}
}

void carregar_arbre(rb_tree *tree, int n, FILE *fp){
	node_data *n_data;;
	int n_elem;

	for(int i = 0; i < n; i++){


		n_data = malloc(sizeof(node_data));
		n_data->key = malloc(sizeof(char) * 4);

		n_data->link = malloc(sizeof(list));
		init_list(n_data->link);
		fread(n_data->key, sizeof(char), 3, fp);
		n_data->key[3] = '\0';

		fread(&n_elem, sizeof(int), 1, fp);

		carregar_llista(n_data->link, n_elem, fp);
		insert_node(tree, n_data);
	}
}

int creacio_arbre(char *aeroports, char *dades, rb_tree  *tree){
  char str[10000];
  char *row,*retrasoChar, *origen,*destino;
  int SIZE,retraso;
  FILE *fp;

  node_data *n_data;

  list *l;
  list_item *l_item;
  list_data *l_data;

  tree = (rb_tree *) malloc(sizeof(rb_tree));
  init_tree(tree);

  fp = fopen(aeroports , "r");

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

  fp = fopen(dades , "r");


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
}

void calcular_retard(node_data *node){
		// Calcular retards
		list_item *item = malloc(sizeof(list_item));
		int media;

		item = node->link->first;

		while(item != NULL){
			media = item->data->retraso / item->data->num_times;
			printf("%s: %d\n", item->data->key, media);
			item = item->next;
		}

		free(node);
		free(item);
}

/**
 *
 *  Main procedure
 *
 */

int main(int argc, char **argv){
    char str1[MAXLINE], str2[MAXLINE];
    int opcio;
	rb_tree *tree;
	FILE *fp;

    if (argc != 1)
        printf("Opcions de la linia de comandes ignorades\n");

    do {
        opcio = menu();
        printf("\n\n");

        switch (opcio) {
            case 1:   // Creacio de l'arbre
                printf("Introdueix fitxer que conte llistat d'aeroports: ");
                fgets(str1, MAXLINE, stdin);
                str1[strlen(str1)-1]=0;

                printf("Introdueix fitxer de dades: ");
                fgets(str2, MAXLINE, stdin);
                str2[strlen(str2)-1]=0;

                creacio_arbre(str1, str2, tree);

                break;

            case 2:   // Emmagatzemar arbre a disc
				if(!tree){
					printf("No hi ha cap arbre carregat\n");

				}else{
		        	printf("Introdueix el nom de fitxer en el qual es desara l'arbre: ");
		            fgets(str1, MAXLINE, stdin);
		            str1[strlen(str1)-1]=0;

					fp = fopen(str1, "w");
		            if(!fp) {
		             	perror("Error opening file");
		              	return(-1);
		            }

			        int mn = MAGIC_NUMBER;
			        fwrite(&mn, sizeof(int), 1, fp);

			        int num_nodes = calcular_numero_nodes(tree->root);
			        fwrite(&num_nodes, sizeof(int), 1, fp);
			        printf("numero de nodos: %d", num_nodes);

			        guardar_arbre(tree->root,fp);
			        fclose(fp);
				}
                break;

            case 3:   // Llegir arbre de disc

				if (tree != NULL){
					delete_tree(tree);
					free(tree);
				}

                printf("Introdueix nom del fitxer que conte l'arbre: ");
                fgets(str1, MAXLINE, stdin);
                str1[strlen(str1)-1]=0;

				fp = fopen(str1, "r");
				if(!fp) {
					perror("Error opening file");
					return(-1);
				}
				int magic, n_nodes;
				fread(&magic, sizeof(int), 1, fp);

				if(magic == MAGIC_NUMBER){
					fread(&n_nodes, sizeof(int), 1, fp);
					tree = (rb_tree *) malloc(sizeof(rb_tree));
					init_tree(tree);
					carregar_arbre(tree, n_nodes, fp);
				}
				fclose(fp);

                break;

            case 4:   // Consultar informacio de l'arbre
                printf("Introdueix aeroport per cercar retard o polsa enter per saber l'aeroport amb mes destins: ");
                fgets(str1, MAXLINE, stdin);
                str1[strlen(str1)-1]=0;

				if (strlen(str1) != 0)

				calcular_retard(find_node(tree, str1));
				else{
					/* Aeroport amb més destins */
				}

                break;

            case 5:   // Sortir
                //Alliberar memoria
                delete_tree(tree);
                free(tree);

                break;

            default:
                printf("Opcio no valida\n");

        } /* switch */
    }
    while (opcio != 5);

    return 0;
}
