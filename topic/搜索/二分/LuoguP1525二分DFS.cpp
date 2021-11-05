/**
   N���ˣ�ÿ����֮����һ��Ȩֵ
   ��N���˷�Ϊ2�ѣ�Ҫ��ÿ���ڲ���Ȩֵ������С
   N��2w
   ��һ����������������w�����ܷ����������������ͼ
*/
#include <bits/stdc++.h>
using namespace std;

typedef int weight_t;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//just as its names
int const SIZE_OF_VERTICES = 20010;
int const SIZE_OF_EDGES = 200010;

struct edge_t{
	int from,to;
	weight_t weight;
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

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int N,M;
int MMax=0,MMin=2000000000;

int CurW;
int Flag[21000];
bool Ans;

void dfs(int u){
    for(int v,p=Vertex[u];p;p=Edge[p].next){
        if(Edge[p].weight>CurW){
            if(0==Flag[v= Edge[p].to]){
                Flag[v] = Flag[u] ^ 3;//1��2,2��1
                dfs(v);
                if(!Ans) return;
            }else{
                if(Flag[v]==Flag[u]){
                    Ans = false;
                    return;
                }
            }
        }
    }
    return;
}

//����Ƿ��ܹ������ȨֵС�ڵ���w��
bool check(int w){
    CurW = w;
    Ans = true;
    fill(Flag,Flag+N+1,0);
    for(int i=1;i<=N;++i)if(!Flag[i]){
        Flag[i] = 1;
        dfs(i);
        if(!Ans) return false;
    }
    return true;
}

int W[100010];
int main(){
    //freopen("1.txt","r",stdin);
    initGraph(N = getUnsigned());
    M = getUnsigned();

    int a,b,w;
    for(int i=1;i<=M;++i){
        a = getUnsigned();
        b = getUnsigned();
        mkEdge(a,b,W[i]=getUnsigned());
    }

    //ע��Ҫ��0�ӽ�ȥ����Ϊ0������һ����
    sort(W,W+M+1);
    M = unique(W,W+M+1)-W;

    int left = 0, right = M-1;
    do{
        int mid = ( left + right ) >> 1;
        if(!check(W[mid])) left = mid + 1;
        else right = mid - 1;
    }while(left<=right);
    printf("%d\n",W[left]);
    return 0;
}
