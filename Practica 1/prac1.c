#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int compara(const void *p1, const void *p2)
{
	int *num1, *num2;
	num1 = (int *) p1;
	num2 = (int *) p2;


	//El segundo es mas grande
	if (*num1 < *num2)
		return -1;

	//El primer es mas grande
	else if (*num1 > *num2)
		return 1;
	else
		return 0;
}



int main(void)
{

	FILE *fp;
	char str[100];


	/* opening file for reading */
	fp = fopen("dades/integers.txt" , "r");
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


	//Hacemos un puntero de ints que tendrá el tamaño de lineas por el tamaño de un int.
	int *listInts = malloc(SIZE*sizeof(int));

	for(int i=0; i < SIZE; i++){
		if( fgets (str, 100, fp)!=NULL )
		{
			/* writing content to stdout */
			puts(str);

			//Gurdamos en nuestro espacio reservado por el malloc el int (convertido desde string)
			listInts[i] = atoi(str);
		}
	}

	fclose(fp);

	//Pasamos por la función qsort con nuestra función "compara"
	qsort(listInts, SIZE, sizeof(int), compara);

	//Mostramos.
	for(int i=0; i < SIZE; i++){
			printf("%d", listInts[i]);
			printf("\n");
	}

	//liberamos datos usados.
	free(listInts);

	return 0;
}