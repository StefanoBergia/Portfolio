#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pthread.h"
#include "semaphore.h"
#include <sys/timeb.h>


sem_t semB_C_D;
sem_t semI;
sem_t semE_F;
sem_t semG;
sem_t semH;

void * A(void * par){
    printf("A\n");
    sem_post(&semB_C_D);
    sem_post(&semB_C_D);
    sem_post(&semB_C_D);
    pthread_exit(0);
}

void * B(void * par){
    sem_wait(&semB_C_D);
    printf("B\n");
    sem_post(&semI);
    pthread_exit(0);
}

void * C(void * par){
    sem_wait(&semB_C_D);
    printf("C\n");
    sem_post(&semE_F);
    sem_post(&semE_F);
    pthread_exit(0);
}

void * D(void * par){
    sem_wait(&semB_C_D);
    printf("D\n");
    sem_post(&semH);
    pthread_exit(0);
}

void * E(void * par){
    sem_wait(&semE_F);
    printf("E\n");
    sem_post(&semG);
    pthread_exit(0);
}

void * F(void * par){
    sem_wait(&semE_F);
    printf("F\n");
    sem_post(&semG);
    pthread_exit(0);
}

void * G(void * par){
    sem_wait(&semG);
    sem_wait(&semG);
    printf("G\n");
    sem_post(&semI);
    pthread_exit(0);
}

void * H(void * par){
    sem_wait(&semH);
    printf("H\n");
    sem_post(&semI);
    pthread_exit(0);
}

void * I(void * par){
    sem_wait(&semI);
    sem_wait(&semI);
    sem_wait(&semI);
    printf("I\n");
    pthread_exit(0);

}

int main() {
    int true=1;
    sem_init(&semB_C_D,0,0);
    sem_init(&semI,0,0);
    sem_init(&semE_F,0,0);
    sem_init(&semG,0,0);
    sem_init(&semH,0,0);

    pthread_t a,b,c,d,e,f,g,h,i;

    while(true){
        pthread_create(&a,NULL,A,NULL);
        pthread_create(&b,NULL,B,NULL);
        pthread_create(&c,NULL,C,NULL);
        pthread_create(&d,NULL,D,NULL);
        pthread_create(&e,NULL,E,NULL);
        pthread_create(&f,NULL,F,NULL);
        pthread_create(&g,NULL,G,NULL);
        pthread_create(&h,NULL,H,NULL);
        pthread_create(&i,NULL,I,NULL);

        pthread_join(a,NULL);
        pthread_join(b,NULL);
        pthread_join(c,NULL);
        pthread_join(d,NULL);
        pthread_join(e,NULL);
        pthread_join(f,NULL);
        pthread_join(g,NULL);
        pthread_join(h,NULL);
        pthread_join(i,NULL);

        scanf("%d",&true);
    }

    return 0;
}