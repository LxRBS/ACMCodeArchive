/**
 * N×N的方阵，左下角能看到多少个位置
 * 如果(r, c)有大于1的gcd，就会被挡住
 * 因此本质上就是问题N-1以内互质的对数，再加上横平竖直2个位置即可
 * https://blog.csdn.net/u012061345/article/details/102801116
 * https://blog.csdn.net/u012061345/article/details/102930433
 * 莫比乌斯反演，ans = SIGMA{miu(i)*(n/i)*(n/i),i=1,...,n}
 * 其中n=N-1
 * 考虑到n/i，可以利用整除分块，计算莫比乌斯函数的同时计算出其前缀和
 * 再利用整除分块求和
 * 可以做到sqrt的复杂度
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 33;
#else
int const SIZE = 40010;
#endif

typedef long long llt;

bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Euler[SIZE] = {0,1};
int Mobius[SIZE] = {0,1};
llt C[SIZE] = {0LL, 1LL}; // miu函数的前缀和
void sieveEulerMobius(){
    llt tmp;
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i, Euler[i] = i - 1, Mobius[i] = -1;
		
		for(int j=0;j<PCnt&&(tmp=i*P[j])<SIZE;++j){
			isComp[tmp] = true;
			
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

llt N;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    sieveEulerMobius();
    cin>>N;
	--N;
    llt ans = 0;
	for(llt t,r,i=1;i<=N;i=r+1){
        t = N / i;
		r = N / t;
		ans += (C[r]-C[i-1]) * t * t;
	}
	cout<<ans+2<<endl;
    return 0;
}
