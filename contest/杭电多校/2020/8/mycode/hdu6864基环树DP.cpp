/**
   有向偶环仙人掌的拓扑序计数问题
   拓扑序计数等于n!乘以概率p
   p是指从n排列中随机选一个恰好是合法排序的概率
   对于有根树而言，p=PI{1/Su}，其中Su表示u子树的大小
   对于基环树而言，如果u不是环上的点，或者u是环上深度最浅的点，其概率仍然是1/Su
   如果是环上的点，可以使用DP来求概率，细节还不甚清楚
   若干环是独立的，相乘即可
*/
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef long long llt;

llt const MOD = 998244353;
int const SIZE = 5010;

vector<int> Graph[SIZE];
vector<int> Tree[SIZE];
typedef pair<int,int> pii;
vector<pii> Edge;

int N,M,Root;

bool Flag[SIZE];
int D[SIZE];
int Father[SIZE];

void bfs(){
    fill(Flag,Flag+N+1,false);
    fill(D,D+N+1,0);

    queue<int> q;
    q.push(Root);
    Flag[Root] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int v: Graph[u]){
            if(Flag[v]){//uv是环上的边
                if(D[v]>D[u]){
                    Edge.push_back({u,v});
                }
            }else{
                Flag[v] = true;
                D[v] = D[u] + 1;
                Tree[Father[v] = u].push_back(v);
                q.push(v);
            }
        }
    }
}

int Size[SIZE];
void dfs(int u){
    Size[u] = 1;
    for(int v: Tree[u]){
        dfs(v);
        Size[u] += Size[v];
    }
}

llt Inv[SIZE] = {0LL, 1LL};
llt Fac[SIZE] = {1LL, 1LL};
llt F[SIZE][SIZE];
llt proc(){
    llt ans = 1LL;

    fill(Flag,Flag+N+1,false);
    //对环上的每一条边
    for(auto e: Edge){
        int u = e.first;
        int v = e.second;
        vector<int> a(1, 0), b(1, 0);
        for(int z1=u,z2=Father[v];z1!=z2;z1=Father[z1],z2=Father[z2]){
            a.push_back(Size[z1]);
            b.push_back(Size[z2]);
            Flag[z1] = Flag[z2] = true;
        }
        int na = a.size()-1, nb = b.size()-1;
        for(int i=0;i<=na;++i)for(int j=0;j<=nb;++j){
            if(0==i&&0==j)F[i][j]=1;
            else if(0==i)F[i][j]=F[i][j-1]*Inv[b[j]]%MOD;
            else if(0==j)F[i][j]=F[i-1][j]*Inv[a[i]+Size[v]]%MOD;
            else F[i][j]=(F[i-1][j]+F[i][j-1])*Inv[a[i]+b[j]]%MOD;
        }
        ans = ans * F[na][nb] % MOD;
    }
    //计算树节点
    for(int i=1;i<=N;++i)if(!Flag[i]) ans = ans * Inv[Size[i]] % MOD;
    //阶乘
    ans = ans * Fac[N] % MOD;
    return ans;
}
int main(){
    //freopen("1.txt","r",stdin);
    //预处理逆元和阶乘
    for(int i=2;i<SIZE;++i){
        llt k = MOD / i;
        llt r = MOD % i;
        Inv[i] = (MOD-k)*Inv[r]%MOD;
        Fac[i] = Fac[i-1] * i % MOD;
    }

    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        Father[Root = getUnsigned()] = 0;

        Edge.clear();
        for(int i=1;i<=N;++i){
            Graph[i].clear();
            Tree[i].clear();
        }

        for(int a,b,i=0;i<M;++i){
            a = getUnsigned();
            b = getUnsigned();
            Graph[a].push_back(b);
            Graph[b].push_back(a);
        }

        //找环
        bfs();
        //确定size
        dfs(Root);
        //求答案
        printf("%lld\n",proc());
    }
    return 0;
}
