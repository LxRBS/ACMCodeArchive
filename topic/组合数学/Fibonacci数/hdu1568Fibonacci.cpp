/*
    求Fibonacci数列的前4位

    Fn = {[(1+sqrt5)/2]^n - [(1-sqrt5)/2]^n} / sqrt5
    对其取对数以后，小数点部分再做10的幂

    Fn的后一部分非常小，没有影响

    log(Fn) = n * log( (1+sqrt5)/2 ) - log( sqrt5 )
*/

#include <stdio.h>
#include <math.h>

int Fib[40] = {0,1};
double const sqrt5 = sqrt(5.0);
double const logSqrt5 = log10(sqrt5);
double const opSqrt5 = ( 1.0 + sqrt5 ) * 0.5;
double const logOpSqrt5 = log10(opSqrt5);

inline double logFib(int n){
    return logOpSqrt5 * (double)n - logSqrt5;
}

int main(){
    for(int i=2;i<21;++i) Fib[i] = Fib[i-1] + Fib[i-2];

    int n;
    while( EOF != scanf("%d",&n) ){
        if ( n < 21 ){
            printf("%d\n",Fib[n]);
            continue;
        }
        double x = logFib(n);
        x -= (int)x;
        x = pow(10.0,x+3.0);
        printf("%d\n",(int)x);
    }
    return 0;
}
