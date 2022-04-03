/**
 * ��һ������ͼ,100���㣬ÿ���߸���ͨ����ʱ��
 * �ٸ������ɸ�trip��(a, b, t)
 * ��˼��Ҫ����tʱ�̿�ʼ��a�ߵ�b
 * ÿ��trip��Ҫһ��˾�������졣
 * ���������trip������˾������
 * �����trip i�Ժ����ü����trip j���Ͱ�i��j��һ����
 * ���Ǳ���������޻�ͼ�ϵ���С·������
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
int const SIZE = 44;
#else
int const SIZE = 105;
#endif

//just as its names
int const SIZE_OF_VERTICES = SIZE * 10;
int const SIZE_OF_EDGES = SIZE * SIZE * 100;
int const INF = 0x3F3F3F3F;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//n is vertex amount of part A
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//a is index of part A and b is index of part B
inline void mkEdge(int a,int b){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A���ֵľ��룬B���ֵľ���
int Q[SIZE_OF_VERTICES];//��������
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = Q, *tail = Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//���

    _Dis = INF;
    int u,v;
    while( head < tail ){
        if ( DA[u = *head++] > _Dis ) continue;

        for(int p=Vertex[u];p;p=Edge[p].next){
            if ( 0 == DB[ v = Edge[p].to ] ){
                DB[v] = DA[u] + 1;
                if ( LinkB[v] ) DA[ *tail++ = LinkB[v] ] = DB[v] + 1;
                else _Dis = DB[v];
            }
        }
    }
    return _Dis < INF;
}

bool _Flag[SIZE_OF_VERTICES];//�����������
bool dfs(int u){
    int v;
    for(int p=Vertex[u];p;p=Edge[p].next){
        if ( !_Flag[v=Edge[p].to] && DB[v] == DA[u] + 1 ){
            _Flag[v] = true;
            if ( !LinkB[v] || ( DB[v] != _Dis && dfs(LinkB[v]) ) ){
                LinkA[ LinkB[v] = u ] = v;
                return true;
            }
        }
    }
    return false;
}

//na��A��������nb��B������
int HopcroftKarp(int na,int nb){
	fill(LinkA,LinkA+na+1,0);
	fill(LinkB,LinkB+nb+1,0);

    int ret = 0;
    while( bfs(na,nb) ){
        fill(_Flag,_Flag+nb+1,false);
        for(int i=1;i<=na;++i){
            if ( !LinkA[i] ) ret += dfs(i);
        }
    }
    return ret;
}


typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef tuple<int, int, int> Tuple;



int N, M, K;
int Origin[SIZE][SIZE];
int D[SIZE][SIZE];

void Floyd(){
    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j){
            D[i][j] = Origin[i][j] ? Origin[i][j] : INF;
        }
        D[i][i] = 0;
    }
    for(int k=1;k<=N;++k)for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
    }
}

Tuple Trip[SIZE*10];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt(); K = getInt();
    for(int a,b,w,i=0;i<M;++i){
        a = getInt(); b = getInt(); w = getInt();
        Origin[a][b] = w;
    }
    for(int u,v,t,i=1;i<=K;++i){
        u = getInt(); v = getInt(); t = getInt();
        Trip[i] = {t, u, v};
    }
    /// ����һ��Floyd
    Floyd();

    /// ��trip��һ����
    sort(Trip+1, Trip+K+1);

    /// ��һ������ͼ����·������
    /// ���ֱ�ӽ�����ͼ���ɣ�����K����
    initGraph(K);
    for(int i=1;i<=K;++i){        
        int a = get<1>(Trip[i]);
        int b = get<2>(Trip[i]);
        int ti = get<0>(Trip[i]) + D[a][b];
        /// ��Trip[i]���Ƿ�������Trip[j]
        for(int j=i+1;j<=K;++j){
            int tj = get<0>(Trip[j]);
            int u = get<1>(Trip[j]);
            if(ti + D[b][u] <= tj){
#ifndef ONLINE_JUDGE
            cout<<i<<" "<<j<<endl;
#endif
                mkEdge(i, j);
            }
        }
    }
    int ans = HopcroftKarp(K, K);
    cout<<K-ans<<endl;
    return 0;
}




