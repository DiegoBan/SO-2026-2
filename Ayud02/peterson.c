#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int flag[2] = {0, 0};
int turn;
int contador = 0; // recurso compartido (sección crítica)

void* proceso0(void* arg) {
    for (int k = 0; k < 100000; k++) {
        // --- Peterson: entrada ---
        flag[0] = 1;
        turn = 1;
        while (flag[1] && turn == 1);

        // --- Sección crítica ---
        contador++;

        // --- Peterson: salida ---
        flag[0] = 0;
    }
    return NULL;
}

void* proceso1(void* arg) {
    for (int k = 0; k < 100000; k++) {
        // --- Peterson: entrada ---
        flag[1] = 1;
        turn = 0;
        while (flag[0] && turn == 0);

        // --- Sección crítica ---
        contador++;

        // --- Peterson: salida ---
        flag[1] = 0;
    }
    return NULL;
}

int main(void) {
    pthread_t t0, t1;

    pthread_create(&t0, NULL, proceso0, NULL);
    pthread_create(&t1, NULL, proceso1, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("Valor final del contador: %d (esperado: 200000)\n", contador);
    return 0;
}
