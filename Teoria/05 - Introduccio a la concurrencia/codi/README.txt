Els codis que hi ha son aquests

1) calcul_pi_1proces.c

Codi original de base

2) calcul_pi_2processos_canonades.c

Codi que es va veure a Sistemes Operatius 1. Fa servir 2 processos
(que son creats amb la crida a sistema "fork") per tal d'augmentar
l'eficiencia computacional del codi. Observeu que cal fer servir
les crides a sistema "read" i "write" per tal de comunicar els
dos processos.

3) calcul_pi_fils.c

Codi que fa servir fils per calcular el nombre pi. El fil principal
crea dos fils. Cada fil secundari s'encarrega de fer una part diferent 
del calcul mentre el fil principal espera que els fils secundaris
acabin. Els fils secundaris emmagatzemen el seu resultat en una posicio
diferent d'un vector. En acabar, el fil principal agafa el resultat
de cada fil, els suma i mostra el resultat final. Observar que aqui
no fan falta crides a sistema per comunicar els fils entre sí.

4) calcul_pi_fils_semafors.c i calcul_pi_fils_mutex.c

Aquest es un exemple que també fa servir fils per calcular el nombre
pi. En aquest cas es fan servir funcions de lock/unclock per poder
accedir a una variable global que comparteixen els fils. Hi ha dues
solucions que es poposen: la primera amb semafors, la segona amb 
mutex. Executar el codi i observar que el codi es fa molt lent. Aixo
es perque les funcions de lock/unlock son crides a sistema i cal
cridar-les molts cops. Cal evitar cridar tants cops a les funcions
lock/unlock. Com modificarieu aquest codi perque no es cridin tantes
vegades a les funcions de lock/unlock? Cal intentar aconseguir que
cada fil faci, en la mesura del possible, operacions independents
respecte els altres fils.

5) calcul_pi_fils_mutex_millorat.c

Aquest es un exemple en que es mostra com aconseguir millorar 
el rendiment del codi del punt 4. Cada fil fa servir variables locals
de la pila per fer els seus calculs sense interferir amb l'altre
fil. Al final, en acabar, cada fil accedeix a la variable global
per "compartir" el seu resultat amb l'altre fil. Observar que mentre
s'accedeix a la variable local no fan falta lock/unlock.
