#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pthread.h"
#include "semaphore.h"
#include <sys/timeb.h>

void C_G(int file[2]) {
    int pidF=0;
    int semE_F[2];
    char k='K';
    int status=0;

    close(file[0]);
    printf("C\n");
    if(pipe(semE_F)==0){
        pidF=fork();
        if(pidF==0){
            close(semE_F[0]);
            printf("F\n");
            write(semE_F[1],&k,sizeof(char));
            exit(0);
        }else{
            close(semE_F[1]);
            printf("E\n");
            read(semE_F[0],&k,sizeof(char));
            printf("G\n");
            write(file[1],&k,sizeof(char));
            waitpid(pidF,&status,0);
            exit(0);
        }
    }


}

int main() {

    int semB_C[2];
    int semB_D[2];
    int pidC;
    int pidD;
    int true=1;
    int status=0;
    char k='K';

    while(true){

        printf("A\n");
        if(pipe(semB_C)==0){

            pidC=fork();
            if(pidC==0){
                C_G(semB_C);
                exit(0);
            }else{
                close(semB_C[1]);
                if(pipe(semB_D)==0){
                    pidD=fork();
                    if(pidD==0){
                        close(semB_D[0]);
                        printf("D\n");
                        printf("H\n");
                        write(semB_D[1],&k,sizeof(char));
                        exit(0);
                    }else {
                        close(semB_D[1]);
                        printf("B\n");

                        read(semB_D[0],&k,sizeof(char));
                        read(semB_C[0],&k,sizeof(char));

                        printf("I\n");
                        waitpid(pidC,&status,0);
                        waitpid(pidD,&status,0);

                    }
                }

            }
        }
        scanf("%d",&true);

    }

}