/**
 * 一共有20个标签，有N个人，每个人有若干标签和一个权值。
 * 再给Q个询问，每次询问给k个标签，问符合标签的最大权值的人是哪一个
 * 显然要状压。关键是方程。
 * Di = max{Dj, j比i多一位}，如果i本来就有，还需要考虑Di本身。
 * 例如问标签12，则将标签123,124,125,126,127,...,12K的最大值求出来，必然是其一。
 * 当然如果某个人本身的标签就是12，那还需要将这个也比较进去。
 * 因此从多位到少位进行计算即可。
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

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

int const INF = 2000000000;

int N, K, Q;
vpii D;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); K = getInt();
	D.assign(1 << K, {0, 0});
    for(int i=1;i<=N;++i){
		auto w = getInt();
		auto k = getInt();
		int st = 0;
		while(k--){
			int t = getInt() - 1;
            st |= 1 << t;
		}
		if(D[st].first < w) D[st] = {w, i};
	}
	for(int i=(1<<K)-1;i>0;--i){
		for(int j=0;j<K;++j){
			if((1 << j) & i) continue;
			if(D[i].first < D[i | (1 << j)].first) D[i] = D[i | (1 << j)];
		}
	}
    Q = getInt();
	for(int x,q=1;q<=Q;++q){
        x = getInt();
		auto st = 0;
		while(x--) st |= 1 << getInt() - 1;
		if(0 == D[st].second) printf("OMG!\n");
		else printf("%d\n", D[st].second);
	}
    return 0; 
}