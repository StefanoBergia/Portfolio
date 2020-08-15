#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void forkbomb(int n,int t);

int main(int argc, char ** argv) {
    int i;
    int status=0;
    if(argc==3){
        forkbomb(atoi(argv[1]),atoi(argv[2]));
    }
    sleep(10);
    for(i=0;i<16;i++){
        wait(&status);
    }
    return 0;

}

void forkbomb(int n,int t){
    if(n>0) {
        if (fork()) {
            if (fork()) {
                forkbomb(n - 1, t);
            } else {
                forkbomb(n - 1, t);
            }
        } else {
            sleep(t);
            printf("processo %d terminato\n",getpid());
        }
    }
}