#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int seats = 1;

void* book(void* id) {
    int customer = *(int*)id;

    if (seats > 0) {
        usleep(100000);
        seats--;
        printf("Customer %d booked seat\n", customer);
    } else {
        printf("Customer %d failed\n", customer);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int c1 = 1, c2 = 2;

    pthread_create(&t1, NULL, book, &c1);
    pthread_create(&t2, NULL, book, &c2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Seats left: %d\n", seats);
    return 0;
}
