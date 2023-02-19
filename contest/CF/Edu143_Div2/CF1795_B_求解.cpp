/**
 * 数轴上给定一些区间。定义f(x)为覆盖x的区间的数量。
 * 给定k,问是否能够删除掉一些区间，使得f(k)比其他f(x)都要大
 * 如果恰好有一个区间就是[k, k]，则显然可以
 * 再如果有区间[..., k]和[k, ...]则也可以。
 * 否则不行。
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

char getChar(){
	char ch = __hv007();
	while( ch != 'o' && ch != 'x' ) ch = __hv007();
	return ch;
}

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 1E9+7LL;

int N, K;
vpii A;

bool proc(){
	int st = 0;
	int ok = 0;
	for(const auto & p : A){
		// if(p.first < K && K < p.second){
		// 	st |= 1;
		// }
        if(p.first == K){
			st |= 2;
		}
		if(p.second == K){
			st |= 4;
		}
		if(p.first == p.second && p.first == K){
			ok = 1;
		}
	}	
	if(ok) return true;
	if(6 == st) return true;
	return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
	// int nofkase; cin >> nofkase;
	for(int kase=1;kase<=nofkase;++kase){
        N = getInt(); K = getInt();
		A.assign(N, {0, 0});
		for(auto & p : A) p.first = getInt(), p.second = getInt();
		puts(proc()?"YES":"NO");
	}
	return 0; 
}