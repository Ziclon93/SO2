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

#include "red-black-tree.h"

#define MAXVALUE 10

/**
 *
 *  Main function. Contains a simple example using a red-black-tree. 
 *
 */

int main(int argc, char **argv)
{
  int a, maxnum, ct;

  rb_tree *tree;
  node_data *n_data;

  /*--------------Nuestro codigo--------------*/

  FILE *fp;
	char str[100];

	/* opening file for reading */
	fp = fopen("../aeroports/aeroports.csv" , "r");

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

	char**listIATA = malloc(SIZE*sizeof(char*));

	for(int i=0; i < SIZE; i++){
		if( fgets (str, 100, fp)!=NULL )
		{
			puts(str);
			str[strlen(str) -1] = '\0';

			listIATA[i] = malloc((strlen(str) +1) * sizeof(char));

			//Metemos el string a la lista correspondiente.

			strcpy(listIATA[i],str);

		}
	}

	fclose(fp);


	/* opening file for reading */
	fp = fopen("../dades/dades.csv" , "r");

  SIZE = 1001;

	char**listDades = malloc(SIZE*sizeof(char*));

	for(int i=0; i < SIZE; i++){
		if( fgets (str, 100, fp)!=NULL )
		{
			puts(str);
			str[strlen(str) -1] = '\0';

			listDades[i] = malloc((strlen(str) +1) * sizeof(char));

			//Metemos el string a la lista correspondiente.

			strcpy(listDades[i],str);

		}
	}

	fclose(fp);









 /*---------------------SU CODIGO -----------------------*/
  if (argc != 2)
  {
    printf("Usage: %s maxnum\n", argv[0]);
    exit(1);
  }

  maxnum = atoi(argv[1]);

  printf("Test with red-black-tree\n");

  /* Random seed */
  srand(time(NULL));

  /* Allocate memory for tree */
  tree = (rb_tree *) malloc(sizeof(rb_tree));

  /* Initialize the tree */
  init_tree(tree);

  for (ct = 0; ct < maxnum; ct++) {
    /* Generate random key to be inserted in the tree */
    a = rand() % MAXVALUE + 1;

    /* Search if the key is in the tree */
    n_data = find_node(tree, a); 

    if (n_data != NULL) {

      /* If the key is in the tree increment 'num' */
      n_data->num_vegades++;
    } else {

      /* If the key is not in the tree, allocate memory for the data
       * and insert in the tree */

      n_data = malloc(sizeof(node_data));
      
      /* This is the key by which the node is indexed in the tree */
      n_data->key = a;
      
      /* This is additional information that is stored in the tree */
      n_data->num_vegades = 1;

      /* We insert the node in the tree */
      insert_node(tree, n_data);
    }
  }
  
  /* We now dump the information of the tree to screen */

  ct = 0;

  for(a = 1; a <= MAXVALUE; a++)
  {
    n_data = find_node(tree, a);

    if (n_data) { 
      printf("El numero %d apareix %d cops a l'arbre.\n", a, n_data->num_vegades);
      ct += n_data->num_vegades;
    }
  }

  printf("Nombre total que vegades que s'ha accedit a l'arbre: %d\n", ct);
  
  /* Delete the tree */
  delete_tree(tree);
  free(tree);
  
  return 0;
}

