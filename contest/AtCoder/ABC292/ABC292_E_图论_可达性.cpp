/**
 * 给定一个有向图，对于任意三个点a,b,c，如果存在边a->b且b->c，则必须同时有a->c
 * 问为了满足这个条件，至少要加多少条边。
 * 使用队列，对每个节点i，检查它的入边和出边，不断的更新入队。
 * 但这个方法在单链模式下是立方级别的。会T。
 * 对任意节点x，假设y是x的可达点，可以发现x到y必须有边。
 * 因此对每个点i，统计其可达点的数量即可。最后减去本来就有的边。
 * O(NM)。
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

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N, M;
vvi G;

llt proc(int u){
    llt ans = 0;
    vi flag(N + 1, 0);
    queue<int> q;
    q.push(u);
    while(!q.empty()){
        auto h = q.front(); q.pop();
        for(int v : G[h]){
            if(v == u or flag[v]) continue;
            ans += flag[v] = 1;
            q.push(v);
        }
    }
    return ans;
}

llt proc(){	
	llt ans = -M;
    for(int i=1;i<=N;++i){
        ans += proc(i);
    }
	return ans;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    // int nofkase = getInt();
    N = getInt(); M = getInt();
	G.assign(N + 1, vi());
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();		
		G[a].push_back(b);
	}
	cout << proc() << endl;
    return 0; 
}