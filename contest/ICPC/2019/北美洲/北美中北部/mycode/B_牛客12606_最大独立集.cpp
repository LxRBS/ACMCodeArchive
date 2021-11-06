/**
    ����ַ���a��b����a������������ĸ�����Ϳ��Եõ�b
    ���a��b�ǿ���swap��
    ����N���ַ����ļ��ϣ�Ҫ������ҵ�һ�������Ӽ���
    ʹ���Ӽ������������ַ������ǲ�����swap��
    ���������������ƥ�䣬Ȼ���һ�£������Ƕ���ͼ��һ��ͼ�������������
    ����֤����Ŀ��Ȼ�Ƕ���ͼ��
    
*/
#include <bits/stdc++.h>
using namespace std;
//just as its names
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 251000;
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

#define mp make_pair
#define fi first
#define se second

int N;
string A[550];
unordered_map<string, int> Dic;
unordered_map<string, int>::iterator It;

int main(){
    //freopen("1.txt","r",stdin);
    cin>>N;
    for(int i=1;i<=N;++i){
        cin>>A[i];
        Dic.insert(mp(A[i], i));
    }

    //��ͼ
    initGraph(N);
    for(int i=1;i<=N;++i){
        string& s = A[i];
        int n = s.length();
        for(int j=0;j<n;++j)for(int k=j+1;k<n;++k){
            swap(s[j], s[k]);
            if((It=Dic.find(s))!=Dic.end()){
                //i��x��һ����
                mkEdge(i, It->se);
            }
            swap(s[j], s[k]);
        }
    }

    int ans = HopcroftKarp(N+N,N+N)/2;
    printf("%d\n", N-ans);
    return 0;
}
