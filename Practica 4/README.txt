Codi comentat amb la implementaci� d'una possible soluci� per les pr�ctiques 1 i 2 de SO2. 
Inclou el codi, les cap�aleres i el Makefile.
Podeu fer servir aquest codi com a punt de partida per seguir fent les pr�ctiques 3 i 4 o b� com a refer�ncia pel vostre propi codi.








TO DO
Mutex global para fichero

Nodo �rbol a�adir atributo mutex de ese nodo
Inicializarlo
Insertar el nodo

Vector de threads
pthread_t vt[NUMTHREADS]

Estructura para pasar datos a los hilos

Crear threads, funci�n lectura de datos

Justo cuando voy a leer hago el mutex lock
Despu�s del fgets hago unlock
Guardar datos le�dos en matriz char**
Guardar en el arbol el nodo que corresponde a cada l�nea


Hacer join para cada hilo
