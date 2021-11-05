#include <iostream>
using namespace std;
typedef long long llt;
#define SIZE 100001

//筛法求欧拉函数以及质因子
int Cnt[SIZE] = {0};     //质因子的个数
int PFac[SIZE][20] = {0};//质因子
int Euler[SIZE] = {0};   //欧拉函数
void sieve(){
	Euler[1] = 1;
	for(int i=2;i<SIZE;++i){
		if ( Euler[i] ) continue;

		for(int j=i;j<SIZE;j+=i){
			if ( !Euler[j] ) Euler[j] = j;

			Euler[j] = Euler[j] / i * ( i - 1 ); 
			PFac[j][Cnt[j]++] = i;
		}
	}
}


//容斥原理的递归实现，求[1,d]中与x不互质的个数
int fun(int idx,int x,int d){
	int ans = 0;

	for(int i=idx;i<Cnt[x];++i){
		int p = PFac[x][i];    
		ans += d / p - fun(i+1,x,d/p);
	}

	return ans;
}

int main(){
	sieve();

	int nofkase;
	scanf("%d",&nofkase);
	for(int kase=1;kase<=nofkase;++kase){
		int a,b,c,d,k;
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);

		printf("Case %d: ",kase);
		if ( 0 == k ){
			printf("0\n");
			continue;
		}

		b /= k;
		d /= k;

		if ( b < d ){
			a = b;
			b = d;
			d = a;
		}

		llt ans = 0;
		for(int i=1;i<=d;++i){
			ans += Euler[i];
		}

		for(int i=d+1;i<=b;++i){
			ans += d - fun(0,i,d);
		}

		printf("%I64d\n",ans);
	}
	return 0;
}