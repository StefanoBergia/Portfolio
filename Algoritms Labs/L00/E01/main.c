#include <stdio.h>

#define NVAL 5

int main(int argc,char**argv) {

    FILE *fp;
    float mediaColonne[NVAL];
    float mediaRighe=0;
    int n_supp;
    int i,j;


    printf(argv[1]);

    fp=fopen(argv[1],"r");

    for (i=0;i<NVAL;i++)
        mediaColonne[i]=0;

    i=0;
    printf("\n");

    while (!feof(fp)){
        mediaRighe=0;
        for(j=0;j<NVAL && !feof(fp);j++){
            fscanf(fp,"%d",&n_supp);
            mediaRighe+=n_supp;
            mediaColonne[j]+=n_supp;
        }
        mediaRighe/=(float)NVAL;
        i++;
        printf("Media riga %d : %f\n",i,mediaRighe);
    }

    for (j=0;j<NVAL;j++)
    {
        mediaColonne[j]/=(float)i;
        printf("Media colonna %d : %f\n",j,mediaColonne[j]);
    }

    fclose(fp);

    return 0;
}