/**
  整点立方体，从（０，０，０）到（Ｎ，Ｎ，Ｎ）
  问从原点看过去能看到多少个点
  Ｎ在一百万
  就是问gcd=1的(x,y,z)一共有多少个
  SIGMA(μ(i)*(N/i)*(N/i)*(N/i),i从１到Ｎ)
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long int llt;

int const SIZE = 1000007;//TODO
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
        int n=getUnsigned();


        llt ans=0LL;
        //体内的点
        for(int r,i=1;i<=n;i=r+1){//整除分块
            r = min(n/(n/i),n/(n/i));
            ans += ( C[r] - C[i-1] ) * (n/i) * (n/i) * (n/i);
        }
        //一面的点
        llt ans2 = 0LL;
        for(int r,i=1;i<=n;i=r+1){//整除分块
            r = min(n/(n/i),n/(n/i));
            ans2 += ( C[r] - C[i-1] ) * (n/i) * (n/i);
        }
        //再加３个坐标轴上的点
        printf("%lld\n",ans+ans2*3LL+3LL);
    }

    return 0;
}

