/**
  1～N内，互质的数为质数的一共有多少对
  gcd(x,y)=p,则gcd(x/p,y/p)=1
  所以，对每一个质数p，求在1~N/p范围内互质的数一共有多少对即可
  利用莫比乌斯反演可得，将N/p记作n
  ans = SIGMA{μ(i)*(n/i)*(n/i)}
  再对每一个质数求和即可
  注意到n/i可以使用根号时间复杂度来做，μ函数则可以预处理前缀和
*/
#include <stdio.h>
typedef long long int llt;

int const SIZE = 10000007;//TODO
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

int main(){
    sieveEulerMobius();

    int n;
    scanf("%d",&n);
    llt ans=0LL;
    for(int i=0;i<PCnt&&P[i]<=n;++i){//对每一个质数
        for(int r,j=1,nn=n/P[i];j<=nn;j=r+1){//整除分块
            r = nn / (nn/j);
            ans += ( C[r] - C[j-1] ) * (nn/j) * (nn/j);
        }
    }
    printf("%lld\n",ans);
    return 0;
}


