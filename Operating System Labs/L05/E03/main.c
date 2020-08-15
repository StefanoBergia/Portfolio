#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void manager(int sig){
    if(sig==SIGUSR1){
        sleep(1);
    }
}

int main() {
    int pid=0;
    (void) signal(SIGUSR1,manager);
    (void) signal(SIGUSR2,manager);
    printf("Program start...\n");
    pid=fork();
    if(pid==0){
        pause();
        printf("Child Woke-up\n");
        while(1){
            sleep(1);
            kill(pid,SIGUSR2);
            pause();
            printf("Child Woke-up\n");
        }
    } else{
        do{
            sleep(1);
            kill(pid,SIGUSR1);
            pause();
            printf("Father Woke-up\n");
        }while(1);
    }
    return 0;
}