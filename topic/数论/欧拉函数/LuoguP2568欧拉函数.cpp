/**
  1～N内，互质的数为质数的一共有多少对
  gcd(x,y)=p,则gcd(x/p,y/p)=1
  所以，对每一个质数p，求在1~N/p范围内互质的数一共有多少对即可
  对于给定范围[1,n]，求互质数的对数，就是求欧拉函数的和
  因此可以首先求出欧拉函数的前缀和
  假设Ci是1到i的所有欧拉函数的和，则Ci表示所有的互质数的对数且i>=j
  1～i中所有互质数的数量就是2Ci-1，因为这中间只有(1,1)重复算了两遍
*/
#include <stdio.h>
typedef long long int llt;

int const SIZE = 10000007;//TODO
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Euler[SIZE] = {0,1};
int Mobius[SIZE] = {0,1};
llt C[SIZE] = {0LL,1LL};//Ci = sigma(phi(i))
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

		C[i] = C[i-1] + Euler[i];
	}
}

int main(){
    sieveEulerMobius();

    int n;
    scanf("%d",&n);
    llt ans=0LL;
    for(int i=0;i<PCnt&&P[i]<=n;++i) ans += (C[n/P[i]]<<1)-1LL;
    printf("%lld\n",ans);
    return 0;
}

