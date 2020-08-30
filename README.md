# P1-Hilos. Autor: Libni Chamán

Este programa realiza un ordenamiento de un arreglo de "n" tamaño por medio de "m" hilos y muestra el tiempo del proceso de ordenamiento. Donde "n" y "m" son números enteros definidos por el usuario y "m" debe ser menor o igual al número de hilos que la máquina tenga. 

COMPILACIÓN:
  gcc -o orden -lpthread -lcurses orden.c

EJECUCIÓN:
  ./orden
 
 A continuación, el programa pide al usuario el tamaño del arreglo y espera respuesta del usuario. 
 Luego muestra el número de hilos que tiene la máquina donde se corra y espera del usuario un número entero con el número de hilos que ocupará para el proceso. 
 Finalmente muestra al usuario el arreglo inicial seguido del ordenado y el tiempo que se ha tardado en realizar el proceso de ordenamiento. 
