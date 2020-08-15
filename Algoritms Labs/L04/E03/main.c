#include <stdio.h>
#include <malloc.h>

int * H(int n);
int Hi(int *v,int n);

int main() {
    int *s,n,i,j;
    printf("inserisci numero-->");
    scanf("%d",&n);
    s=H(n);
    printf("i primi %d numeri della sequenza di Hofstadter sono:\n",n);
    for(i=0,j=1;i<n;i++,j++){
        printf("%d ",s[i]);
        if(j%10==0)
            printf("\n");
    }
    free(s);
    return 0;
}

int * H(int n)
{
    int * seq=(int *)malloc(n*sizeof(int));     //alloco dinamicamnte un vettore in cui verrà salvata la sequenza
    int i;
    for(i=0;i<n;i++)
        seq[i]=-1;                              //imposto tutti i valori del vettore a -1 (dato che non ci possono essere numeri della sequenza con tale valore)

    seq[0]=0;
    for(i=1;i<n;i++){
        seq[i]=Hi(seq,i);                       //mi calcolo la sequenza valore per valore
    }

    return seq;

}

int Hi(int * v,int n){
    if(n<0)
        return 0;
    else if (v[n]>=0)                           //se  nel vettore soluzione è già presente H(n) non eseguo la ricorsione
        return v[n];
    else
        return n-Hi(v,Hi(v,Hi(v,n-1)));         //eseguo la ricorsione

}