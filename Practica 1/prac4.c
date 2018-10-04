#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int compara(const void *p1, const void *p2)
{
	char *string1, *string2;
	int num1, num2;
	string1 = *((char**) p1);
	string2 = *((char**) p2);

	//Solo medimos cuan largo es cada uno.
	num1 = strlen(string1);
	num2 = strlen(string2);


	//comparamos cual de los dos mide más en cuestion de caracteres.
	if (num1 < num2)
		return -1;
	else if (num1 > num2)
		return 1;
	else
		return 0;
}

int main(void)
{

	FILE *fp;
	char str[100];

	/* opening file for reading */
	fp = fopen("dades/strings.txt" , "r");
	if(fp == NULL)
	{
		perror("Error opening file");
		return(-1);
	}
	if( fgets (str, 100, fp)!=NULL )
	{
		/* writing content to stdout */
		puts(str);
	}

	int SIZE = atoi(str);

	//Lista de punteros de punteros que apuntaran a los caracteres (tan larga como lineas hayan)
	char**listStrings = malloc(SIZE*sizeof(char*));

	for(int i=0; i < SIZE; i++){
		if( fgets (str, 100, fp)!=NULL )
		{
			/* writing content to stdout */
			puts(str);

			//Queremos substituir el '\n' por el '\0' para que la memoria no este separada por los \n que coje al leer y de los warnings
			str[strlen(str) -1] = '\0';

			//Declaramos el espacio que reservaremos para cada caracter, eso es el tamaño del string + 1 porque también queremos el '\0'
			// multiplicado por el tamaño de caracteres especiales
			listStrings[i] = malloc((strlen(str) +1) * sizeof(char));

			//Metemos el string a la lista correspondiente.
			strcpy(listStrings[i],str);

		}
	}

	fclose(fp);

	//llamamos a la función qsort con nuestro compara
	qsort(listStrings, SIZE, sizeof(char*), compara);

	//mostramos resultado
	for(int i=0; i < SIZE; i++){
			printf("%s", listStrings[i]);
			//se libera espacio utilizado
			free(listStrings[i]);
			printf("\n");
	}

	//se libera espacio utilizado.
	free(listStrings);
	return 0;
}