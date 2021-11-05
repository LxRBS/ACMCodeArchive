/**
 * 给一个有向无环图，没有重边，没有自环
 * 再给一个K，
 * 要么找到一个独立集，点数恰好是ceil(K/2)
 * 要么找到一个简单环，其点数最多是K
 * 深搜的时候，根据回边判环即可
 * 如果所有环的点数都超过K，则从中隔点取就能取出独立集
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

int const SIZE = 100100;
int N, M, K;
vector<int> G[SIZE];
int Depth[SIZE];
int Pre[SIZE];
int Parent[SIZE];

int CycSize= SIZE + SIZE;
int Anchor;

void dfs(int u, int parent){
    // cout<<u<<" "<<parent<<endl;
    Depth[u] = Depth[Parent[u] = parent] + 1;
    for(auto v: G[u]){
        if(v == parent) continue;
        if(Depth[v]){ // 之前已经搜索过
            if(Depth[v] < Depth[u] && CycSize > Depth[u]-Depth[v]+1){ // 回边
                Pre[Anchor = u] = v;
                CycSize = Depth[u]-Depth[v]+1;
            }            
        }else{
            dfs(v, u);
        }
    } 
}

int main(){
    // freopen("1.txt","r",stdin);

    N = getUnsigned();
    M = getUnsigned();
    K = getUnsigned();
    for(int a, b, i=0;i<M;++i){
        a = getUnsigned();
        b = getUnsigned();
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(1, 0);
    // cout<<CycSize<<endl;
    if(SIZE+SIZE==CycSize){
        printf("1\n");
        int t[2] = {0, 0};
        for(int i=1;i<=N;++i){
            ++t[Depth[i]&1];
        }
        int n = (K + 1) >> 1;
        if(t[0]>=n){
            for(int i=1,j=0;j<n;++i){
                if(!(Depth[i]&1)){
                    printf("%d ", i);
                    ++j;
                }
            }
        }else if(t[1]>=n){
            for(int i=1,j=0;j<n;++i){
                if(Depth[i]&1){
                    printf("%d ", i);
                    ++j;
                }
            }
        }else{
            throw runtime_error("tree");
        }
        printf("\n");
    }else if(CycSize>K){
        printf("1\n");
        int n = (K + 1) >> 1;
        for(int u=Anchor,j=0;j<n;++j,u=Parent[Parent[u]]){
            printf("%d ",u);
        }
        printf("\n");
    }else if(CycSize<=K){
        printf("2\n%d\n", CycSize);
        printf("%d", Anchor);
        for(int dst=Pre[Anchor],u=Parent[Anchor];u!=dst;u=Parent[u]){
            printf(" %d", u);
        }
        printf(" %d\n", Pre[Anchor]);
    }else{
        throw runtime_error("no chance here");
    }
    return 0;
}
