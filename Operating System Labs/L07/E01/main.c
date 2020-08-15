#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char ** argv){
    int * vet;
    int n,i,j;
    n = atoi (argv[1]);
    vet=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        if(fork())
            vet[i]=0;
        else
            vet[i]=1;
    }

    for (j=0; j<n; j++) {
        printf("%d", vet[j]);
    }
    printf("\n");

}