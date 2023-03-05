/**
 * 给定一个以1为根的树，问是否是对称的。首先要判断子树是否相等，需要用到树哈希
 * 对所有子树首先递归计算一遍哈希值
 * 对1的所有儿子，有且只能有一个奇数节点，且该奇数节点必须也是对称的
 * 再写一遍递归去检查。其实可以只用一次递归。
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
using ull = unsigned long long;

const ull MSK = std::chrono::steady_clock::now().time_since_epoch().count();

inline ull shift(ull x){
    x ^= MSK;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= MSK;
    return x;
}

llt const MOD = 998244353LL;

int N;
vvi G;
vector<ull> H;

void dfs(int u, int p){
    H[u] = 1;
    for(int v : G[u]){
        if(v == p) continue;
        dfs(v, u);
        H[u] += shift(H[v]);
    }
    return;
}

bool check(int u, int p){
    map<ull, vi> m;
    for(int v : G[u])if(v != p)m[H[v]].push_back(v);
    int c = 0;
    for(const auto & p : m){
        if(0 == p.second.size() % 2){

        }else{
            if(++c > 1) return false;
            auto b = check(p.second[0], u);
            if(!b) return false;
        }
    }    
    return true;
}

bool proc(){
    H.assign(N + 1, 0);
    dfs(1, 0);
    return check(1, 0);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    int nofkase = getInt();
    while(nofkase--){
        G.assign((N = getInt()) + 1, vi());
        for(int a,b,i=1;i<N;++i){
            a = getInt(); b = getInt();
            G[a].push_back(b);
            G[b].push_back(a);
        }
        puts(proc()?"YES":"NO");
    }
    return 0; 
}