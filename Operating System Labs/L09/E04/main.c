#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pthread.h"
#include "semaphore.h"
#include <sys/timeb.h>

sem_t semA;
sem_t semB;
sem_t semC;
sem_t semD;
sem_t semE;
sem_t semF;
sem_t semG;
sem_t semH;
sem_t semI;

void * A(void * par){
    while(1){
        sem_wait(&semA);
        printf("A\n");
        sem_post(&semB);
        sem_post(&semC);
        sem_post(&semD);
    }
}

void * B(void * par){
    while(1){
        sem_wait(&semB);
        printf("B\n");
        sem_post(&semI);
    }
}

void * C(void * par){
    while(1){
        sem_wait(&semC);
        printf("C\n");
        sem_post(&semE);
        sem_post(&semF);
    }
}

void * D(void * par){
    while(1){
        sem_wait(&semD);
        printf("D\n");
        sem_post(&semH);
    }
}

void * E(void * par){
    while(1){
        sem_wait(&semE);
        printf("E\n");
        sem_post(&semG);
    }
}

void * F(void * par){
    while(1){
        sem_wait(&semF);
        printf("F\n");
        sem_post(&semG);
    }
}

void * G(void * par){
    while(1){
        sem_wait(&semG);
        sem_wait(&semG);
        printf("G\n");
        sem_post(&semI);
    }
}

void * H(void * par){
    while(1){
        sem_wait(&semH);
        printf("H\n");
        sem_post(&semI);
    }
}

void * I(void * par){
    char block=0;
    while(1){
        sem_wait(&semI);
        sem_wait(&semI);
        sem_wait(&semI);
        printf("I\n");

        scanf("%c",&block);

        sem_post(&semA);
    }

}

int main() {

    sem_init(&semA,0,1);
    sem_init(&semB,0,0);
    sem_init(&semC,0,0);
    sem_init(&semD,0,0);
    sem_init(&semE,0,0);
    sem_init(&semF,0,0);
    sem_init(&semG,0,0);
    sem_init(&semH,0,0);
    sem_init(&semI,0,0);

    pthread_t a,b,c,d,e,f,g,h,i;

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

    return 0;
}