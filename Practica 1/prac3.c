#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int compara(const void *p1, const void *p2)
{
	double *num1, *num2;
	num1 = (double *) p1;
	num2 = (double *) p2;


	//El segundo es mas grande
	if (*num1 < *num2)
		return -1;

	//El primero es mas grande
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
	fp = fopen("dades/float.txt" , "r");
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

	//Hacemos un puntero de doubles que tendrá el tamaño de lineas por el tamaño de un double.
	double *listDouble = malloc(SIZE*sizeof(double));

	for(int i=0; i < SIZE; i++){
		if( fgets (str, 100, fp)!=NULL )
		{
			/* writing content to stdout */
			puts(str);
			//Gurdamos en nuestro espacio reservado por el malloc el double (convertido desde string)
			listDouble[i] = atof(str);
		}
	}

	fclose(fp);

	//Pasamos por la función qsort con nuestra función "compara"
	qsort(listDouble, SIZE, sizeof(double), compara);

	//Mostramos.
	for(int i=0; i < SIZE; i++){
			printf("%f", listDouble[i]);
			printf("\n");
	}

	//liberamos datos usados.
	free(listDouble);
	
	return 0;
}