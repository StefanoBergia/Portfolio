#include <stdio.h>

#define MAXC 11

float valutaHorner(float P[MAXC], float x);

int main() {

    int n,i,n_intervalli,a,b;
    float coefficienti[MAXC];
    float base,integrale=0;

    for (i=0;i<MAXC;i++)
        coefficienti[i]=0;

    do {
        printf("inserisci grado del polinomio: ");
        scanf("%d", &n);
    }while(n>10 || n<0);

    for (i=0;i<=n;i++) {
        printf("inserisci coefficiente di grado %d ",i);
        scanf("%f", &coefficienti[i]);
    }

    printf("inserisci estremi di integrazione e numero di intervalli ");
    scanf("%d %d %d",&a,&b,&n_intervalli);

    base=((float)(b-a))/(float)n_intervalli;

    for(i=0;i<n_intervalli;i++)
        integrale+=base*valutaHorner(coefficienti,a+i*base+base/2);

    printf("il valore dell'integrale è %f ",integrale);

    return 0;
}

float valutaHorner(float P[MAXC], float x){
    int i;
    float val=P[MAXC-1];
    for(i=MAXC-2;i>=0;i--){
        val=val*x+P[i];
    }
    return val;
}