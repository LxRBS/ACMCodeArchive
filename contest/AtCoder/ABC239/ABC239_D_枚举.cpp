/**
 * 给定AB和CD，Taka在[A, B]中选一个数
 * Aoki在[C, D]中选一个数，如果两数之和是质数，则A胜，否则T胜
 * 问谁能赢。ABCD规模只有100
 * 因此做一个双重循环即可
*/
#include <bits/stdc++.h>
using namespace std;

bool isPrime[200] = {false};
int P[200] = {2, 3, 5};
int PCnt = 3;
void init(){
	auto f = [](int n){
        for(int i=2;i*i<=n;++i)if(n%i==0)return false;
		return true;
	};
	for(int i=7;i<=200;i+=2){
        if(f(i)) P[PCnt++] = i;
	}
	for(int i=0;i<PCnt;++i)isPrime[P[i]] = true;
}

int A, B, C, D;

bool proc(){
	auto f = [](int n){
		for(int i=C;i<=D;++i){
			if(isPrime[n+i]) return false;
		}
		return true;
	};
	for(int i=A;i<=B;++i){
		if(f(i)) return true;
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    init();
    while(cin>>A>>B>>C>>D){
		cout<<(!proc()?"Aoki":"Takahashi")<<endl;
	}	
    return 0;
}
