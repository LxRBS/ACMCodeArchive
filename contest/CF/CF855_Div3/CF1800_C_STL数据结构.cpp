/**
 * 一共有N张牌，包括两种牌：
 * 英雄牌，power总是0；奖励牌，有一个正的power
 * 依次处理每张牌，如果是奖励牌，可以扔掉也可以放入堆顶；如果是英雄牌，就将目前堆顶的奖励牌加到结果
 * 问结果最大是多少
 * 对每张英雄牌，只需选取之前奖励牌中没用用过的最大即可
 * 用最大堆或者排序二叉树都能解决
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 66;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N;

llt proc(){
	llt ans = 0;
	multiset<int> s;
    for(int x,i=0;i<N;++i){
        x = getInt();
		if(0 == x){
			if(!s.empty()){
				ans = ans + *--s.end();
				s.erase(--s.end());
			}
		}else{
			s.insert(x);
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    int nofkase = getInt();
	// int nofkase; cin >> nofkase;
	while(nofkase--){
        N = getInt();
		printf("%lld\n", proc());
	}
    return 0; 
}