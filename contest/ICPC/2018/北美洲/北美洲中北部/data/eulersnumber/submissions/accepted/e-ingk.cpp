#include<stdio.h>
int n;
int main() {
    scanf("%d",&n);
    if(n>19) n = 19;
    int i,j,k;
    double p,q,r,t;
    p = 1.0;
    r = 0.0;
    for(i=0;i<=n;i++) {
   //     printf("%d : ",i);
        if(i != 0) p *= (double)i;
        r += (1.0/p);
    //    printf("%.15lf  %lf\n",r,p);
    }
    printf("%.13lf",r);
    return 0;
}

//15 : 2.7182818284590
