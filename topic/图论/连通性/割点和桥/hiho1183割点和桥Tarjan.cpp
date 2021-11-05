//����ͼ��ͬʱ���������ţ����Դ����رߣ���Ȼ����û���ر�
#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_VERTICES = 20010;
int const SIZE_OF_EDGES = 220010;

struct edge_t{
    int from,to;
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

inline void initGraph(int n){
    ECnt = 2;
    fill(Vertex,Vertex+n+1,0);
}

//˫���
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int TimeStamp;
int Dfn[SIZE_OF_VERTICES],Low[SIZE_OF_VERTICES];
//int AddBlocks[SIZE_OF_VERTICES];//ABi��ʾɾ��i��֮�������Ŀ���
bool IsBridge[SIZE_OF_EDGES];//��i�Ƿ�Ϊ��
bool IsCut[SIZE_OF_VERTICES];//��i�Ƿ�Ϊ���
bool IsVisited[SIZE_OF_EDGES];//�ߵı�����飬���ر�ʱ����
int BridgeCnt;//�ŵ�����

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    int v,son = 0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            //*
            //��
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
                ++BridgeCnt;
            }
            //*/

            //*
            //���ϸ�������2
            if ( u != pre && Dfn[u] <= Low[v] ){
                IsCut[u] = true;
                //++AddBlocks[u];
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //���ϸ�������1
    if ( u == pre && son > 1 ) IsCut[u] = true;
    //if ( u == pre ) AddBlocks[u] = son - 1;
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    //fill(AddBlocks,AddBlocks+vn+1,0);
    fill(IsCut,IsCut+vn+1,false);
    fill(IsBridge,IsBridge+ECnt,false);
    fill(IsVisited,IsVisited+ECnt,false);
    TimeStamp = BridgeCnt = 0;

    for(int i=1;i<=vn;++i)if(0==Dfn[i])dfs(i,i);
}

//������
void output1(int vn){
    bool first = true;
    for(int i=1;i<=vn;++i){
        if ( !IsCut[i] ) continue;
        if ( first ) first = false, printf("%d",i);
        else printf(" %d",i);
    }
    if ( first ) printf("Null");
    printf("\n");
}

//�����
pair<int,int> Ans[SIZE_OF_VERTICES];
void output2(){
    int ans = 0;
    for(int i=2;i<ECnt;i+=2)if ( IsBridge[i] ){
        int a = Edge[i].from, b = Edge[i].to;
        if ( a > b ) swap(a,b);
        Ans[ans].first = a;
        Ans[ans++].second = b;
    }
    sort(Ans,Ans+ans);
    for(int i=0;i<ans;++i)printf("%d %d\n",Ans[i].first,Ans[i].second);
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    int n = getUnsigned();
    int m = getUnsigned();

    initGraph(n);
    for(int i=0;i<m;++i){
        mkEdge(getUnsigned(),getUnsigned());//������˫���
    }

    Tarjan(n);
    output1(n);output2();
    return 0;
}
