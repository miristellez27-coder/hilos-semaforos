
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo;

void *contar(void *arg)
{
    int id = *(int *)arg;

    for (int i = 1; i <= 10000; i++)
    {
        if (i == 4000)
        {
            // Entrar a la seccion critica
            sem_wait(&semaforo);

            printf("\n>>> HILO %d ENTRA A LA SECCION CRITICA <<<\n", id);

            printf("Hilo %d: %d\n", id, i);
        }
        else if (i > 4000 && i <= 6000)
        {
            // Continuar sin interrupciones
            printf("Hilo %d: %d\n", id, i);

            if (i == 6000)
            {
                printf(">>> HILO %d SALE DE LA SECCION CRITICA <<<\n\n", id);

                // Liberar el semaforo
                sem_post(&semaforo);
            }
        }
        else
        {
            // Impresiones fuera de la seccion critica
            sem_wait(&semaforo);

            printf("Hilo %d: %d\n", id, i);

            sem_post(&semaforo);
        }
    }

    printf("Hilo %d ha terminado.\n", id);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t hilo1, hilo2;

    int id1 = 1;
    int id2 = 2;

    // Inicializar semaforo
    sem_init(&semaforo, 0, 1);

    // Crear los dos hilos
    pthread_create(&hilo1, NULL, contar, &id1);
    pthread_create(&hilo2, NULL, contar, &id2);

    // Esperar a que terminen
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // Destruir semaforo
    sem_destroy(&semaforo);

    printf("\nAmbos hilos han terminado.\n");

    return 0;
}
