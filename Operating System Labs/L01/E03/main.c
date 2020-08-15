#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <malloc.h>
#include <memory.h>
#include <limits.h>
#include <fcntl.h>


int copyFS_R(char * path,char* dest,int depth);
char *ret_path(char *name, char *buf);
int copy_file(char *src,char * dest);

int main(int argc, char ** argv) {
    //FILE * fp=fopen("output.txt","w");
    char * sup=malloc(PATH_MAX+1);
    if(argc==3 && chdir(argv[1])==0){
        getcwd(sup,100);
        printf("Current directory: %s\n",sup);
        copyFS_R(sup,argv[2],0);
    }else
        printf("path errato");
    free(sup);
    return 0;
}

int copyFS_R(char * path,char* dest,int depth){

    DIR * dir=NULL;
    char buf[PATH_MAX +1];
    char buf2[PATH_MAX +1];
    char * p;
    char *p2;
    struct dirent * file=NULL;
    struct stat * file_pointer=(struct stat *)malloc(sizeof(struct stat));

    strcpy(buf,path);
    strcpy(buf2,dest);
    dir=opendir(path);


    if(dir!=NULL){
        while((file=readdir(dir))!=NULL){
            p=ret_path(file->d_name, buf);
            p2=ret_path(file->d_name, buf2);
            if(stat(p,file_pointer)==0){
                if(S_ISDIR(file_pointer->st_mode) && strcmp(file->d_name,".")!=0 && strcmp(file->d_name,"..")!=0){
                    mkdir(p2, S_IRUSR | S_IWUSR | S_IXUSR);
                    copyFS_R(p,p2,depth+1);

                } else if(S_ISREG(file_pointer->st_mode)){
                    copy_file(p,p2);
                }

            }
            free(p);
        }
        closedir(dir);
        free(file_pointer);
    }
    return -1;
}

char * ret_path(char *name, char *buf){
    char * ret= malloc(PATH_MAX +1);
    strcpy(ret,buf);
    strcat(ret,"/");
    strcat(ret,name);
    return ret;
}

int copy_file(char *src,char * dest){
    int fpi,  fpo;
    fpi=open(src,O_RDONLY);
    fpo=open(dest,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    char buf[100];

    if(fpi!=-1 && fpo!=-1){
        while(read(fpi,buf,100)!=0){
            write(fpo,buf,100);
        }
        close(fpi);
        close(fpo);
    } else
        return -1;
}
