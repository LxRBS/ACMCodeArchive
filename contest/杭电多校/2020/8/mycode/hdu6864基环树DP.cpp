/**
   ����ż�������Ƶ��������������
   �������������n!���Ը���p
   p��ָ��n���������ѡһ��ǡ���ǺϷ�����ĸ���
   �����и������ԣ�p=PI{1/Su}������Su��ʾu�����Ĵ�С
   ���ڻ��������ԣ����u���ǻ��ϵĵ㣬����u�ǻ��������ǳ�ĵ㣬�������Ȼ��1/Su
   ����ǻ��ϵĵ㣬����ʹ��DP������ʣ�ϸ�ڻ��������
   ���ɻ��Ƕ����ģ���˼���
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
            if(Flag[v]){//uv�ǻ��ϵı�
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
    //�Ի��ϵ�ÿһ����
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
    //�������ڵ�
    for(int i=1;i<=N;++i)if(!Flag[i]) ans = ans * Inv[Size[i]] % MOD;
    //�׳�
    ans = ans * Fac[N] % MOD;
    return ans;
}
int main(){
    //freopen("1.txt","r",stdin);
    //Ԥ������Ԫ�ͽ׳�
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

        //�һ�
        bfs();
        //ȷ��size
        dfs(Root);
        //���
        printf("%lld\n",proc());
    }
    return 0;
}
