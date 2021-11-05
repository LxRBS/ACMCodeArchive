/**
  x在[1,b]，y在[1,d]，问有多少对(x,y)满足gcd=k
  x、y不要求秩序
  实际上就是问gcd(x/k,y/k)=1的数量
  令n=b/k,m=d/k，且设n<=m
  答案就是
  SIGMA{μ(i)*(n/i)*(m/i),i从1到n}
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long int llt;

int const SIZE = 100007;//TODO
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

int main(){
    //freopen("1.txt","r",stdin);
    sieveEulerMobius();

    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        int a=getUnsigned();
        int b=getUnsigned();
        int c=getUnsigned();
        int d=getUnsigned();
        int k=getUnsigned();
        
        if(!k){
            printf("Case %d: 0\n",kase);
            continue;
        }

        int n=b/k;
        int m=d/k;
        if(n>m) swap(n,m);

        llt ans=0LL;
        //计算出所有互异的数对，但题目要求不计秩序，还要减掉一部分
        for(int r,i=1;i<=n;i=r+1){//整除分块
            r = min(n/(n/i),m/(m/i));
            ans += ( C[r] - C[i-1] ) * (n/i) * (m/i);
        }
        //要减去的部分就是[1~n]的数对
        llt ans2 = 0LL;
        for(int r,i=1;i<=n;i=r+1){
            r = n / (n/i);
            ans2 += ( C[r] - C[i-1] ) * (n/i) * (n/i);
        }
        printf("Case %d: %lld\n",kase,ans-(ans2>>1));
    }

    return 0;
}


