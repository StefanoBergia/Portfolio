#include <stdio.h>
#include <malloc.h>
#include <values.h>

char ** leggilabirinto(FILE* fp,int *R, int *C);
void print_lab(char ** lab, int R, int C);
void percorso_min(char ** lab, int R,int C,int i, int j,int count,int* min,char ** best_path);

int main(int argc, char ** argv) {
    char ** labirinto,** sol;
    int min=INT_MAX,R,C,i,j,flag=1;
    FILE* fp;
    if(argc==2){
        fp=fopen(argv[1],"r");
        labirinto=leggilabirinto(fp,&R,&C);
        fclose(fp);

        sol=(char **)malloc(R*sizeof(char*));
        for(i=0;i<R;i++)
            sol[i]=(char *)malloc(C*sizeof(char));

       // print_lab(labirinto,R,C);

        percorso_min(labirinto,R,C,0,0,0,&min,sol);

        printf("lunghezza percorso:%d\n",min);
        sol[0][0]='I';
        print_lab(sol,R,C);


    }
    return 0;
}

char ** leggilabirinto(FILE* fp,int *R, int *C){
    int i,j;
    char ** lab;
    char sup;
    if(fscanf(fp,"%d %d",R,C)){
        lab=(char **)malloc(*R*sizeof(char*));
        for(i=0;i<*R;i++){
            lab[i]=(char *)malloc((*C+1)*sizeof(char));
            fscanf(fp,"%s",lab[i]);
        }
    }
    return  lab;
}

void print_lab(char ** lab, int R, int C){
    int i,j;
    for(i=0;i<R;i++){
        for(j=0;j<C;j++)
            printf(" %c ",lab[i][j]);
        printf("\n");
    }
}

void percorso_min(char ** lab, int R,int C,int i, int j,int count,int* min,char ** best_path){
    int x,y;
    if(i<0 || j<0 || i>=R || j>=C || lab[i][j]=='X' || lab[i][j]=='#')
        return;

    if(lab[i][j]=='U'){
        if(count<*min){
            *min=count;
            for(x=0;x<R;x++){
                for(y=0;y<C;y++)
                    best_path[x][y]=lab[x][y];
            }
        }
        return;
    }

    lab[i][j]='#';

    percorso_min(lab,R,C,i+1,j,count+1,min,best_path);
    percorso_min(lab,R,C,i-1,j,count+1,min,best_path);
    percorso_min(lab,R,C,i,j+1,count+1,min,best_path);
    percorso_min(lab,R,C,i,j-1,count+1,min,best_path);

    lab[i][j]='-';

    return;
}