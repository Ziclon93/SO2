#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int compara(const void *p1, const void *p2)
{
	float *num1, *num2;
	num1 = (float *) p1;
	num2 = (float *) p2;

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

	//Hacemos un puntero de floats que tendrá el tamaño de lineas por el tamaño de un float.
	float *listFloats = malloc(SIZE*sizeof(float));

	for(int i=0; i < SIZE; i++){
		if( fgets (str, 100, fp)!=NULL )
		{
			/* writing content to stdout */
			puts(str);
			//Gurdamos en nuestro espacio reservado por el malloc el float (convertido desde string)
			listFloats[i] = atof(str);
		}
	}

	fclose(fp);

	//Pasamos por la función qsort con nuestra función "compara"
	qsort(listFloats, SIZE, sizeof(float), compara);

	//Mostramos.
	for(int i=0; i < SIZE; i++){
			printf("%f", listFloats[i]);
			printf("\n");
	}
	
	//liberamos datos usados.
	free(listFloats);

	return 0;
}