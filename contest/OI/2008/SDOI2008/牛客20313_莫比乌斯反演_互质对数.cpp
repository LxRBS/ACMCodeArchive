/**
 * N×N的方阵，左下角能看到多少个位置
 * 如果(r, c)有大于1的gcd，就会被挡住
 * 因此本质上就是问题N-1以内互质的对数，再加上横平竖直2个位置即可
 * https://blog.csdn.net/u012061345/article/details/102801116
 * 莫比乌斯反演，ans = SIGMA{miu(i)*(n/i)*(n/i),i=1,...,n}
 * 其中n=N-1
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
	for(llt i=1;i<=N;++i){
		ans += Mobius[i] * (N / i) * (N / i);
	}
	cout<<ans+2<<endl;
    return 0;
}
