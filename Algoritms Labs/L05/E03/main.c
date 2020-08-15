#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAXC 10

int generaCombinazioni(char ** lettere,char * sol,int livello,int n,int count,FILE * fout);

int main(int argc,char ** argv) {
    FILE *fp;
    char **lettere;
    char * sup;
    int n,i,count;
    if(argc==3){
        fp=fopen(argv[1],"r");
        fscanf(fp,"%d",&n);
        lettere=(char **)malloc(n*sizeof(char *));
        sup=(char *)malloc(n);
        for(i=0;i<n;i++)
        {
            lettere[i]=(char *)malloc(MAXC);
            fscanf(fp,"%s",lettere[i]);
        }
        fclose(fp);
        fp=fopen(argv[2],"w");
        count=generaCombinazioni(lettere,sup,0,n,0,fp);
        fclose(fp);
        printf("%d combinazioni generate",count);
        for(i=0;i<n;i++)
            free(lettere[i]);
        free(lettere);
        free(sup);
    }
    return 0;
}

int generaCombinazioni(char ** lettere,char * sol, int livello,int n,int count,FILE * fout){    //uso la proprietà del prodotto
    int j,nr;
    if(livello>=n){
        for(j=0;j<n;j++)
            fprintf(fout,"%c",sol[j]);
        fprintf(fout," ");
        return count+1;
    }
    nr=strlen(lettere[livello]);
    for(j=0;j<nr;j++){
        sol[livello]=lettere[livello][j];
        count=generaCombinazioni(lettere,sol,livello+1,n,count,fout);
    }
    return count;

}