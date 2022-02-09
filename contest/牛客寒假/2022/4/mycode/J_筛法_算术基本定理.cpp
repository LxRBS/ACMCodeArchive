/**
 * 区间合数的最小公倍数，考虑算术基本定理，实际上就是求区间内每个质因子的最高次幂
 * 对每个数暴力除即可，可以即时记录答案
*/
#include <bits/stdc++.h>
using namespace std;


#ifndef ONLINE_JUDGE
int const SIZE = 30010;
#else
int const SIZE = 30010;
#endif

typedef long long llt;

bool isComp[SIZE] = {false};
int P[SIZE];
int PCnt = 0;
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

llt const MOD = 1000000007LL;

int Cnt[SIZE] = {0};

llt powMod(llt a, llt n){
	llt ans = 1LL;
	for(int i=0;i<n;++i) ans = ans * a % MOD;
	return ans;
}

llt proc(int n){
	llt ans = 1;
	for(int p,i=0;i<PCnt;++i){
        p = P[i];
		int k = 0;
		while(0==n%p) n/=p, ++k;
		if(k>Cnt[p]){
            ans = ans * powMod(p, k-Cnt[p]);
			Cnt[p] = k;
		}
		if(1==n) break;
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    sieve();
	int a, b;
	cin>>a>>b;
	if(1==a && 1==b){
		cout<<-1<<endl; return 0;
	}

	if(1 == a) ++a;
	llt ans = 1LL;
	bool flag = false;
	for(int i=a;i<=b;++i){
		if(isComp[i]){
            ans = ans * proc(i) % MOD;
			flag = true;
		}
	}
	cout<<(flag?ans:-1)<<endl;
    return 0;
}
