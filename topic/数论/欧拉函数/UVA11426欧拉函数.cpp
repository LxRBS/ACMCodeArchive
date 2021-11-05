/*
     ����n��
     ��SIGMA{ gcd(i,j) }
     ���У�i��jС�ڵ���n

     ����Ȼ�����i��j���ʣ���gcd(i,j)=1
     ��gcd(ki,kj)=k
     �����������gcd(a,b)=k����gcd(a/k,b/k)=1

     ��Sn = S(n-1) + SIGMA( gcd(i,n) )
     ����Fn = SIGMA( gcd(i,n) )

     ��ÿһ��n��Լ��x���������
     gcd(i,n) = x��iһ����hx��
     �� Fn = SIGMA( x * hx )
     �� hx = phi(n/x)

     Ҳ����˵n���ڣ���n��gcdΪx����һ����phi(n/x)��

     ����������е�Fn��Ȼ��������е�Sn
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