#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <malloc.h>
#include <memory.h>
#include <limits.h>


int analyzeFS_R(char * path,int depth,FILE * fp);
char *ret_path(char *name, char *buf);

int main(int argc, char ** argv) {
    FILE * fp=fopen("output.txt","w");
    char * sup=malloc(PATH_MAX+1);
    if(argc==2 && chdir(argv[1])==0){
        getcwd(sup,100);
        printf("Current directory: %s\n",sup);
        analyzeFS_R(sup,0,fp);
    }else
        printf("path errato");
    free(sup);
    fclose(fp);
    return 0;
}

int analyzeFS_R(char * path,int depth, FILE* fp){
    DIR * dir=NULL;
    char buf[PATH_MAX +1];
    char * p;
    int i;
    struct dirent * file=NULL;
    struct stat * file_pointer=(struct stat *)malloc(sizeof(struct stat));

    strcpy(buf,path);
    dir=opendir(path);


    if(dir!=NULL){
        while((file=readdir(dir))!=NULL){
            p=ret_path(file->d_name, buf);
            if(stat(p,file_pointer)==0){
                if(S_ISDIR(file_pointer->st_mode) && strcmp(file->d_name,".")!=0 && strcmp(file->d_name,"..")!=0){
                    for(i=0;i<depth;i++)
                        fprintf(fp," ");
                    fprintf(fp,"DIRECTORY:%s\n",file->d_name);
                    analyzeFS_R(p,depth+1,fp);

                } else if(S_ISREG(file_pointer->st_mode)){
                    for(i=0;i<depth;i++)
                        fprintf(fp," ");
                    fprintf(fp,"FILE:%s\n",file->d_name);
                }else if(S_ISLNK((file_pointer->st_mode))){
                    for(i=0;i<depth;i++)
                        fprintf(fp," ");
                    fprintf(fp,"LINK:%s\n",file->d_name);
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