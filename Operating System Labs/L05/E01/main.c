#include <stdio.h>

int main() {
    int n;
    while(!feof(stdin)){
        fscanf(stdin,"%d",&n);
        if(n%2==0)
            fprintf(stdout,"%d\n",n);
        else
            fprintf(stderr,"%d\n",n);
    }
    return 0;
}