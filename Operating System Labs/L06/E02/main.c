#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int pipe_p_c[2];
    int pipe_c_p[2];
    char msg='k';

    if(pipe(pipe_p_c)==0 && pipe(pipe_c_p)==0){
        if(fork()==0){
            //figlio
            close(pipe_c_p[0]);//scrive su 1
            close(pipe_p_c[1]);//legge su 0
            while(msg=='k') {
                read(pipe_p_c[0], &msg, 1);
                sleep(1);
                fprintf(stdout, "I'm the child (PID=%d)\n", getpid());
                write(pipe_c_p[1], &msg, 1);
            }
        } else{
            //padre

            close(pipe_p_c[0]);//scrive su 1
            close(pipe_c_p[1]);//legge su 0
            while(msg=='k') {
                sleep(1);
                write(pipe_p_c[1], &msg, 1);
                fprintf(stdout, "I'm the father (PID=%d)\n", getpid());
                read(pipe_c_p[0],&msg,1);

            }
        }
    }
    return 0;
}