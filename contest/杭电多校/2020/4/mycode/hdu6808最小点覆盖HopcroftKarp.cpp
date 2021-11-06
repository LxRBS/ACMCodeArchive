/**
    �����ɸ��ˣ���ĳ��x�����ĳ��ʱ�̿�ʼ�ߣ��ٶȺ㶨Ϊ1��������x������Ҳ���Ը�����
    ���ڸ����ɸ�����(t,x)����ʾ��tʱ��x����������һ����
    ������Ҫ���ٸ��˲������������Ĳ���

    �����ԣ���������������һ��45��ֱ���ϣ�����һ����45��ֱ���ϣ�������һ�������
    ���ԭ���Ϊ������ֱ��ȥ���ǵ㣬�����ٵ�ֱ�߽��и���
    ���͵���С�㸲�����⣬��һ�����ƥ�伴��
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

vector<int> G[100010];

int N;
llt X[100010],T[100010];
int A[100010][2];

unordered_map<llt,int> BZ,BF;
unordered_map<llt,int>::iterator USIt;

void read(){
    N = getUnsigned();
    for(int i=1;i<=N;++i){
        T[i] = getUnsigned();
        X[i] = getUnsigned();
        G[i].clear();
    }

    BZ.clear();
    BF.clear();

    //����ÿ����
    for(int i=1;i<=N;++i){
        llt bz = X[i] - T[i];
        if((USIt=BZ.find(bz))!=BZ.end()){
            A[i][0] = USIt->second;
        }else{
            A[i][0] = BZ.size() + 1;
            BZ.insert(make_pair(bz,A[i][0]));
        }

        llt bf = X[i] + T[i];
        if((USIt=BF.find(bf))!=BF.end()){
            A[i][1] = USIt->second;
        }else{
            A[i][1] = BF.size() + 1;
            BF.insert(make_pair(bf,A[i][1]));
        }
    }
}

//just as its names
int const SIZE_OF_VERTICES = 200010;
int const SIZE_OF_EDGES = 4501000;
int const INF = 0x3F3F3F3F;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//�����
inline void mkEdge(int a,int b){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A���ֵľ��룬B���ֵľ���
int _Q[SIZE_OF_VERTICES];//��������
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = _Q, *tail = _Q;
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

void proc(){
    //��ͼ
    int na = BZ.size();
    int nb = BF.size();
    initGraph(na);

    //����
    for(int i=1;i<=N;++i){
        mkEdge(A[i][0],A[i][1]);
    }

    printf("%d\n",HopcroftKarp(na,nb));
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        read();
        proc();
    }
    return 0;
}
