#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int seats = 1;
pthread_mutex_t lock;

void* book(void* id) {
    int customer = *(int*)id;

    pthread_mutex_lock(&lock);

    if (seats > 0) {
        usleep(100000);
        seats--;
        printf("Customer %d booked seat\n", customer);
    } else {
        printf("Customer %d failed\n", customer);
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int c1 = 1, c2 = 2;

    // Инициализация mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init failed\n");
        return 1;
    }

    // Создание потоков
    pthread_create(&t1, NULL, book, &c1);
    pthread_create(&t2, NULL, book, &c2);

    // Ожидание завершения потоков
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Уничтожение mutex
    pthread_mutex_destroy(&lock);

    printf("Seats left: %d\n", seats);
    return 0;
}
