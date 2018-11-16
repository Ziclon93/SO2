Codi comentat amb la implementació d'una possible solució per les pràctiques 1 i 2 de SO2. 
Inclou el codi, les capçaleres i el Makefile.
Podeu fer servir aquest codi com a punt de partida per seguir fent les pràctiques 3 i 4 o bé com a referència pel vostre propi codi.








TO DO
Mutex global para fichero

Nodo árbol añadir atributo mutex de ese nodo
Inicializarlo
Insertar el nodo

Vector de threads
pthread_t vt[NUMTHREADS]

Estructura para pasar datos a los hilos

Crear threads, función lectura de datos

Justo cuando voy a leer hago el mutex lock
Después del fgets hago unlock
Guardar datos leídos en matriz char**
Guardar en el arbol el nodo que corresponde a cada línea


Hacer join para cada hilo
