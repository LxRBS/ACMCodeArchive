/**
 * N×N的方阵，站在左下角，问能看到多少元素
 * 考虑元素(r, c)，如果r和c有不为1的公约数，则该位置必然被挡住
 * 因此实际就是问N-1之类互质的数量，令r<c，则互质数量就是phi(c)
 * 因此求和 SIGMA{phi(c), c=1,...,N-1}
 * 显然 ans = 2 * SIGMA + 1
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
    llt ans = 0;
	for(int i=1;i<N;++i){
		ans += Euler[i];
	}
	cout<<ans+ans+1<<endl;
    return 0;
}
