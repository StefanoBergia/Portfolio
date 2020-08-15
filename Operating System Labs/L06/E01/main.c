#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char * strup(char *str);

int main(int argc, char **argv) {
    int pid1=0,pid2=0;
    char str[100+1];
    int file[2];
    int sgn[2];
    int n;
    char k='K';

    printf("Program start...\n");

    if(pipe(file)==0 && pipe(sgn)==0) {
        pid1 = fork();
        if (pid1 == 0) {
            // pid1 output
            close(file[1]); //pid1 legge
            close(sgn[0]);
            pid1 = getpid();

            while (1) {
                n=read(file[0],str,100);
                if (strcmp(str, "end\n") == 0) {
                    fprintf(stdout, "output chiuso\n");
                    write(sgn[1],&k,1);
                    close(file[0]);
                    close(sgn[1]);
                    exit(0);
                }
                fprintf(stdout, "OUTPUT->%s", strup(str));
                write(sgn[1],&k,1);
            }

        } else {
            pid2 = fork();
            if (pid2 == 0) {
                // pid2 input
                close(file[0]); //pid1 legge
                close(sgn[1]);

                do {
                    fprintf(stdout, "Inizio conversazione...\n");
                    fgets(str, 100, stdin);
                    write(file[1],str,100);
                    read(sgn[0],&k,1);
                } while (strcmp(str, "end\n") != 0);
                fprintf(stdout, "input chiuso\n");
                exit(0);

            } else {
                wait((int *) 0);
                wait((int *) 0);
            }
            printf("Program ended\n");
        }
    }
    return 0;
}

char * strup(char *str){
    int i=0;
    char * out=malloc(100+1);
    for(i=0;str[i]!='\0';i++)
        out[i]=toupper(str[i]);
    return out;
}