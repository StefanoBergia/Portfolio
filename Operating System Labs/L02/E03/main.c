#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status=0;
    printf("P%d\n",1);
    int pid1=0,pid2=0;
    pid1=fork();
    if(pid1!=0){
        printf("P%d\n",2);
        pid2=fork();
        if(pid2!=0){
            sleep(2);
            printf("P%d\n",4);
            waitpid(pid2,&status,0);
            sleep(5);
            printf("P%d\n",7);
            waitpid(pid1,&status,0);
            printf("P%d\n",9);

        }else {
            sleep(3);
            printf("P%d\n", 5);
        }
    }else{
        sleep(1);
        printf("P%d\n",3);
        pid2=fork();
        if(pid2!=0){
            waitpid(pid2,&status,0);
            sleep(6);
            printf("P%d\n",8);
        } else{
            sleep(4);
            printf("P%d\n",6);
        }

    }

    return 0;
}