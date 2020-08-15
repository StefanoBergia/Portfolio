#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define N 12

void exchange_fork(int fp,int i,int j,int n);

int main (int argc, char **argv)
{
    int i=0,n=0,j=0,count=0,supp=0,pid;
    int  fd;
    fd = open (argv[1], O_RDWR);
    if (fd == -1){
        fprintf(stderr,"Cannot open file %s\n", argv[1]);
        exit(-1);
    }
    lseek (fd, 0, SEEK_SET);

    count = read (fd, &n, sizeof (int));
    if (count <= 0){
        fprintf (stderr, "Error reading file\n");
        exit (-1);
    }
    for (i=0; i<n-1; i++) {
        if(pid=fork()==0){
            exchange_fork(fd,i,0,n);
            exit(0);
        }else
            waitpid(pid,&supp,0);
    }


    lseek (fd, 1*sizeof(int), SEEK_SET);
    for(i=0;i<n;i++){
        read(fd,&j,sizeof(int));
        printf("%d\n",j);
    }


    return (0);
}

void exchange_fork(int fp,int i,int j,int n) {
    int supp = 0,pid=0;
    int x = 0, y = 0;
    if (j < n-i-1) {
        lseek(fp, (j+1) * sizeof(int), SEEK_SET);
        read(fp, &x, sizeof(int));
        read(fp, &y, sizeof(int));

       // printf("%d-%d ",x,y);


        if (x > y) {
            lseek(fp, (j+1) * sizeof(int), SEEK_SET);
            write(fp, &y, sizeof(int));
            write(fp, &x, sizeof(int));

            /*lseek(fp, (j+1) * sizeof(int), SEEK_SET);
            read(fp, &x, sizeof(int));
            read(fp, &y, sizeof(int));

            printf("-> %d-%d ",x,y);*/


        }
        //printf("\n");
        if(pid=fork()==0)
            exchange_fork(fp,i,j+1,n);
        else
            waitpid(pid,&supp,0);
    }
}