/**
   ������Ӷ�������ʹ��Ϊǿ��ͨͼ
   �������KDAG��Ȼ�������Ⱥͳ���Ϊ�����������
*/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair

typedef pair<int, int> pii;
struct pair_hash{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 20100;
int const SIZE_OF_EDGES = 300010;

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
        }
        if(Belong[u]!=SCCCnt) ++SCCSize[Belong[u]=SCCCnt];
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

int N,M;
int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int InDeg[SIZE_OF_VERTICES],OutDeg[SIZE_OF_VERTICES];
int main(){
    //freopen("1.txt","r",stdin);
    while(2==scanf("%d%d",&N,&M)){
        initGraph(N);
        for(int a,i=0;i<M;++i){
            a = getUnsigned();
            mkEdge(a, getUnsigned());
        }

        Nuutila(N);

        if(1==SCCCnt){
            puts("0");
            continue;
        }
        //���KDAG��ʵ���ϲ�����ֻҪ����ȼ���
        fill(InDeg,InDeg+SCCCnt+1,0);
        fill(OutDeg,OutDeg+SCCCnt+1,0);
        //for(int i=1;i<=SCCCnt;++i)Kdag[i].clear();
        for(int a,b,i=2;i<ECnt;++i){
            if((a=Belong[Edge[i].from])!=(b=Belong[Edge[i].to])){
                ++InDeg[b];++OutDeg[a];
            }
        }

        int acnt = 0, bcnt = 0;
        for(int i=1;i<=SCCCnt;++i){
            if(!InDeg[i]) ++acnt;
            if(!OutDeg[i]) ++bcnt;
        }
        printf("%d\n",max(acnt, bcnt));
    }
    return 0;
}
