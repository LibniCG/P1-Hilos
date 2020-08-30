#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 2 /* Máximo de hilos que se pueden ocupar */

int *num; /* Variable para el arreglo */
void *ordenamiento(void *param); /* ordenamiento del arreglo */
int comp(const void *a, const void *b);
int num_cpus(); /* Información de la máquina */

int main(){
    pthread_t workers[NUM_THREADS];
    pthread_attr_t attr;

    clock_t tInicio, tFinal;
    double seg;

    int lim, numHilos;
    int lim1[2], lim2[2];
    int i, bandera = 0; 

    /* Obtener largo del arreglo */
    printf("\n Largo del arreglo: ");
    scanf("%d", &lim);

    /* Obtener el número de hilos que tiene la máquina */
    num_cpus();

    /* Validación para número de hilos */
    do {
        /* El usr indica el número de hilos a ocupar */
        printf("\n Número de hilos a ocupar: ");
        scanf("%d", &numHilos);
        bandera = 0;
        if(numHilos > 2 || numHilos == 0){
            bandera = 1;
            printf("\n Error, intente de nuevo.\n");
        }
    } while(bandera == 1);

    if(bandera == 0) {
        /* Reservación de memoria para el arreglo */
        num = (int*)malloc(lim*sizeof(int));
        
        /* Llenado del arrelgo */
        printf(" \n Arreglo inicial: ");
        for(i = 0; i <= lim; i++){
            num[i]  = random() % 100;
            if(i < lim){
                printf(" %d, ", num[i]);
            } else {
                printf(" %d ", num[i]);
            }
        }

        /***** HILOS *****/

        /* get the deafault atributes */
        pthread_attr_init(&attr);

        /* Validar número de hilos */
        lim1[0] = 0;
        if( numHilos == 1) {
            tInicio = clock();
            lim1[1] = lim;

            /* Creación del hilo */
            pthread_create(&workers[0], &attr, ordenamiento, &lim1);
        } else { 
            tInicio = clock();
            /* Definición de limites */
            lim1[1] = lim/2;
            lim2[0] = lim/2 + 1;
            lim2[1] = lim + 1;

            /* Creación de hilos */
            pthread_create(&workers[0], &attr, ordenamiento, &lim1);
            pthread_create(&workers[1], &attr, ordenamiento, &lim2);
        } 

        /* now wait for the thread to exit */
        for(i = 0; i < numHilos; i++){
            pthread_join(workers[i],NULL);
        }

        /* Ordenamiento del arreglo final */ 
        qsort(&num[lim1[0]], lim + 1, sizeof(int), comp); 
        tFinal = clock();
        
        printf(" \n Arreglo ordenado: ");
        for(i = 0; i <= lim; i++){
            if(i < lim){
                printf(" %d, ", num[i]);
            } else {
                printf(" %d \n\n", num[i]);
            }
        }

        seg = (double)(tFinal - tInicio) / CLOCKS_PER_SEC;
        printf(" Se ha tardado: %f milisegundos en ejecutarse con %d hilo(s). \n\n", seg, numHilos);

        free(num);
    }
}

void *ordenamiento(void *param) {
    int *par = (int*)param;
    int lower = par[0];
    int upper = par[1];

    qsort(&num[lower], upper-lower, sizeof(int), comp);  

    pthread_exit(0);   
}

int comp(const void *a, const void *b) {
    return(*(int*)a - *(int*)b);
}

int num_cpus(){
    unsigned int eax=11, ebx=0, ecx=1, edx=0;
    asm volatile 
    (
        "cpuid":
        "=a" (eax),
        "=b" (ebx),
        "=c" (ecx),
        "=d" (edx)
        : "0" (eax), "2" (ecx)
        : ) ;
        printf("\n Hilos disponibles: %d\n", ebx);
    return eax*ebx;
}