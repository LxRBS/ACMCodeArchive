/*
     给定n，
     求SIGMA{ gcd(i,j) }
     其中，i、j小于等于n

     很显然，如果i、j互质，则gcd(i,j)=1
     且gcd(ki,kj)=k
     反过来，如果gcd(a,b)=k，则gcd(a/k,b/k)=1

     令Sn = S(n-1) + SIGMA( gcd(i,n) )
     再令Fn = SIGMA( gcd(i,n) )

     对每一个n的约数x，如果满足
     gcd(i,n) = x的i一共有hx个
     则 Fn = SIGMA( x * hx )
     而 hx = phi(n/x)

     也就是说n以内，与n的gcd为x的数一共有phi(n/x)个

     首先求出所有的Fn，然后求出所有的Sn
*/
#include <stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long llt;

int const SIZE = 4000001;//TODO
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Euler[SIZE] = {0,1};
void sieveEuler(){
    int tmp;
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i, Euler[i] = i - 1;

		for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
			isComp[tmp=i*P[j]] = true;

			if ( 0 == i % P[j] ){
				Euler[tmp] = Euler[i] * P[j];
				break;
			}else{
				Euler[tmp] = Euler[i] * ( P[j] - 1 );
			}
		}
	}
}

llt F[SIZE];
llt A[SIZE] = {0,0};
int main(){
    sieveEuler();

    for(int i=1;i<SIZE;++i){
        for(int j=i+i;j<SIZE;j+=i){
            F[j] += i * Euler[j/i];
        }
    }

    for(int i=2;i<SIZE;++i) A[i] = A[i-1] + F[i];

    llt n;
    while( scanf("%lld",&n),n ){
        printf("%lld\n",A[n]);
    }
    return 0;
}