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

void manager(int sig){
    if(sig==SIGUSR1){
        sleep(1);
    }else if (sig==SIGUSR2){
        sleep(1);
    }else if(sig==SIGCHLD){
        sleep(1);
    }
}

int main(int argc, char **argv) {
    int pid1=0,pid2=0;
    char str[100+1];
    FILE * fp;
    (void) signal(SIGUSR1,manager);
    (void) signal(SIGUSR2,manager);
    (void) signal(SIGCHLD,manager);

    printf("Program start...\n");
    pid1=fork();
    if(pid1==0){
        // pid1 output
        pid1=getpid();
        pause();
        fp=fopen(argv[1],"r");
        fscanf(fp,"%d",&pid2);
        fclose(fp);
        fprintf(stdout,"pid output, %d ricevuto, invio segnale di risposta\n",pid2);
        kill(pid2,SIGUSR2);
        pause();
        fprintf(stdout,"messaggio ricevuto\n");
        while(1){
            fp=fopen(argv[1],"r");
            fgets(str,100,fp);
            fclose(fp);
            if(strcmp(str,"end\n")==0) {
                fprintf(stdout,"output chiuso\n");
                kill(pid2, SIGUSR2);
                exit(0);
            }
            fprintf(stdout,"OUTPUT->%s",strup(str));
            kill(pid2,SIGUSR2);
            pause();
        }

    }else{
        pid2=fork();
        if(pid2==0){
            // pid2 input
            fp=fopen(argv[1],"w");
            pid2=getpid();
            fprintf(fp,"%d",pid2);
            fclose(fp);
            fprintf(stdout,"scambio pid input %d\n",pid2);
            kill(pid1,SIGUSR1);
            pause();

            do{
                fprintf(stdout,"Inizio conversazione...\n");
                fgets(str,100,stdin);
                fp=fopen(argv[1],"w");
                fprintf(fp,"%s",str);
                fclose(fp);
                kill(pid1,SIGUSR1);
                pause();
            }while(strcmp(str,"end\n")!=0);
            fprintf(stdout,"input chiuso\n");
            kill(getppid(),SIGCHLD);
            exit(0);

        } else
            pause();
        printf("Program ended\n");
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