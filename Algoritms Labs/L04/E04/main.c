#include <stdio.h>

int f(int n);

int main() {
    int n;
    printf("inserisci numero-->");
    scanf("%d",&n);
    printf("%d",f(n));
    return 0;
}

int f(int n){
    if(n==0)
        return 0;
    else
        return n%10+f((n-n%10)/10);
}