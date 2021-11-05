/**
    给定abcdk，问
    在[a,b][c,d]之间有多少对(x,y)满足
    gcd(x,y)=k
    考虑[1,N][1,M]之间有多少对(x,y)满足条件，令其为f(N,M)，则
    f(N,M) = SIGMA(miu(d)*(N/k/d)*(M/k/d)),d从1到min(N/k,M/k)
    所以答案 ans = f(b,d)-f(a-1,d)-f(c-1,b)+f(a-1,c-1);
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long int llt;

int const SIZE = 55000;//TODO
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Euler[SIZE] = {0,1};
int Mobius[SIZE] = {0,1};
llt C[SIZE] = {0LL,1LL};//Ci = sigma(miu(i))
void sieveEulerMobius(){
    int tmp;
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i, Euler[i] = i - 1, Mobius[i] = -1;

		for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
			isComp[tmp=i*P[j]] = true;

			if ( 0 == i % P[j] ){
				Euler[tmp] = Euler[i] * P[j];
				Mobius[tmp] = 0;
				break;
			}else{
				Euler[tmp] = Euler[i] * ( P[j] - 1 );
				Mobius[tmp] = - Mobius[i];
			}
		}

		C[i] = C[i-1] + Mobius[i];
	}
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//求[1,n][1,m]之间有多少对数满足gcd==k
int f(int n,int m,int k){
    n /= k, m /= k;
    if(n>m) swap(n,m);

    int ans = 0;
    for(int r,i=1;i<=n;i=r+1){
        r = min(n/(n/i),m/(m/i));
        ans += (C[r]-C[i-1]) * (n/i) * (m/i);
    }
    return ans;
}
int main(){
    //freopen("1.txt","r",stdin);
    sieveEulerMobius();

    int nofkase = getUnsigned();
    while(nofkase--){
        int a = getUnsigned();
        int b = getUnsigned();
        int c = getUnsigned();
        int d = getUnsigned();
        int k = getUnsigned();
        printf("%d\n",f(b,d,k)-f(a-1,d,k)-f(c-1,b,k)+f(a-1,c-1,k));
    }
    return 0;
}
