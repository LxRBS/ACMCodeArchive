/**
 * 令T=(1LL<<60)-1LL，即二进制的60个1
 * 给最多100个点的树，要求给点赋权值满足：
 * 1. 相邻点的或为T
 * 2. 不相邻的点的或不能为T
 * 考虑某个点u，令其某位为0， 则其邻点该位为1，非邻点为0即可
 * 最多有100个点，因此一位不够，需要用两位来组合。
 * 考虑到树的层次或者二分图特性，可以按层次分为奇偶层，形成2个队列
 * 再取较少的那个，此时该队列的元素数量一定不超过50
 * 令该队列的所有元素最高位均为0，第i个元素第i位为0，其余为1
 * 再令另一个中的最高位均为1，与上述第i个元素相邻的点的第i为为1，其余为0
 * 这样就保证了，队列内部、队列之间的其他元素或出来都有0存在
 * 只有邻点刚好互补。
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
int const SIZE = 22;
#else
int const SIZE = 110;
#endif

typedef unsigned long long ull;
ull const MASK_59 = (1LL<<59) - 1LL;

typedef vector<int> vi;
vi G[SIZE];

int N;
vi Layer[2];
int Depth[SIZE];
ull Ans[SIZE];

void dfs(int u, int p){
    Layer[(Depth[u] = Depth[p] + 1) & 1].push_back(u);
    for(auto v: G[u]){
        if(v != p){
            dfs(v, u);
        }
    }
}

void proc(){
    fill(Ans, Ans+N+1, 0);
    Layer[0].clear(); Layer[1].clear();
    dfs(1, 0);

    vi *cur, *other;
    if(Layer[0].size() < Layer[1].size()){
        cur = Layer; other = Layer + 1;
    }else{
        cur = Layer + 1; other = Layer;
    }

    for(int u,i=0,n=cur->size();i<n;++i){
        /// 最高位为0， 第i位为0， 其他为1
        Ans[u=cur->operator[](i)] = MASK_59 ^  (1LL<<i);
        /// 跟u相邻的点，最高位为1，第i位为1
        for(auto v: G[u]){
            Ans[v] |= (1LL<<59) | (1LL<<i);
        }
    }

    for(int i=1;i<=N;++i)printf("%llu ", Ans[i]);
    puts("");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    N = getInt();
    for(int i=1;i<=N;++i) G[i].clear();
    for(int a,b,i=1;i<N;++i){
        a = getInt(); b = getInt();
        G[a].push_back(b);
        G[b].push_back(a);
    }
    proc();


    return 0;
}
