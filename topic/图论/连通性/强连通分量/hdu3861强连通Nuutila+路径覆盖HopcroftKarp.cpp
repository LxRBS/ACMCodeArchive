/**
    �����������DAG��Ȼ����һ����С·������
    Nuutila+HopcroftKarp
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second

//type of edge's weight
typedef long long weight_t;

//just as its names
int const SIZE_OF_VERTICES = 5100;
int const SIZE_OF_EDGES = 200110;

struct edge_t{
	int from,to;
	//weight_t weight;
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


inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int Stack[SIZE_OF_VERTICES], StackTop;//����ջ
bool IsInStack[SIZE_OF_VERTICES];

int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
int Low2Node[SIZE_OF_VERTICES];//Low2Node[i]��ʾLowֵΪi�Ľڵ���
int SCCCnt;//��ͨ������������
int Belong[SIZE_OF_VERTICES];//��i���������ڵ�Belong[i]��ǿ��ͨ����
int SCCSize[SIZE_OF_VERTICES];//��i����ͨ�����Ĵ�С���±��1��ʼ
vector<int> TopoOrder;//��������Ľ��
weight_t W[SIZE_OF_VERTICES],WW[SIZE_OF_VERTICES];

void dfs(int u){
    Low2Node[Dfn[u] = Low[u] = ++TimeStamp] = u;

    //��u��ÿһ����
    int v, tmplow, &low = Low[u];
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < low ) low = Low[v];
        }else if (!Belong[Low2Node[tmplow=Low[v]]] && tmplow < low){
            low = tmplow;
        }
    }

    //�ҵ�һ��SCC
    if ( Dfn[u] == low ){
        ++SCCCnt;
        while(Low[v=Stack[StackTop-1]]>=low){
            ++SCCSize[Belong[v]=SCCCnt];
            --StackTop;
            IsInStack[v] = false;
            Low[v] = low;
            WW[SCCCnt] += W[v];
        }
        if(Belong[u]!=SCCCnt) ++SCCSize[Belong[u]=SCCCnt], WW[SCCCnt]+=W[u];
        //TopoOrder.push_back(u); //��¼��������Ľ��
    }else if(!IsInStack[u]){
        IsInStack[Stack[StackTop++] = u] = true;
    }
}

//Nuutila�㷨��SCC
//Tarjan�㷨�Ľ��������˽ڵ����ջ����
void Nuutila(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(IsInStack,IsInStack+vn+1,false);
    fill(SCCSize,SCCSize+vn+1,0);
    fill(Belong,Belong+vn+1,0);
    fill(WW,WW+vn+1,0LL);

    TimeStamp = SCCCnt = 0;
    Stack[StackTop=1] = 0;
    Low[0] = -10000;//ջ���һ��������Сֵ
    //TopoOrder.clear(); //��¼������������Ҫ������

    for(int i=1;i<=vn;++i){
        if ( 0 == Dfn[i] ){
            dfs(i);
        }
    }
}

typedef pair<int, int> pii;
struct pair_hash{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};

int N,M;
vector<int> KDag[SIZE_OF_VERTICES];
unordered_set<pii, pair_hash> Set;
unordered_set<pii, pair_hash>::iterator SetIt;

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

    _Dis = 2000000000;
    int u,v;
    while( head < tail ){
        if ( DA[u = *head++] > _Dis ) continue;

        for(auto v: KDag[u]){
            if ( 0 == DB[ v ] ){
                DB[v] = DA[u] + 1;
                if ( LinkB[v] ) DA[ *tail++ = LinkB[v] ] = DB[v] + 1;
                else _Dis = DB[v];
            }
        }
    }
    return _Dis < 2000000000;
}

bool _Flag[SIZE_OF_VERTICES];//�����������
bool dfs2(int u){
    for(auto v: KDag[u]){
        if ( !_Flag[v] && DB[v] == DA[u] + 1 ){
            _Flag[v] = true;
            if ( !LinkB[v] || ( DB[v] != _Dis && dfs2(LinkB[v]) ) ){
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
            if ( !LinkA[i] ) ret += dfs2(i);
        }
    }
    return ret;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        initGraph(N = getUnsigned());
        M = getUnsigned();
        for(int a, i=0;i<M;++i){
            a = getUnsigned();
            mkEdge(a, getUnsigned());
        }

        Nuutila(N);

        //����KDAG
        Set.clear();
        for(int i=1;i<=SCCCnt;++i)KDag[i].clear();
        for(int a,b,i=2;i<ECnt;++i){
            if((a=Belong[Edge[i].from])!=(b=Belong[Edge[i].to])&&(SetIt=Set.find(mp(a, b)))==Set.end()){
                KDag[a].pb(b);
                Set.insert(SetIt, mp(a, b));
            }
        }

        printf("%d\n", SCCCnt-HopcroftKarp(SCCCnt, SCCCnt));
    }
    return 0;
}
