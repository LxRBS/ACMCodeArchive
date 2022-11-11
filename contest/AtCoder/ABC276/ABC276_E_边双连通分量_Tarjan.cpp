/**
 * һ����ά���飬#��ʾ�ϰ�����ʾͨ·��S��ʾ���
 * ���Ƿ���ڴ�S��ʼ�ҵ�S�����ļ�·�����ҳ��ȴ��ڵ���4
 * ���ǵ���ά�����ͼ�����S������һ������������4�ı�˫��ͨ��������·������
 * ģ����
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
int const SIZE = 23;
#else
int const SIZE = 1E6+13;
#endif

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = SIZE;
int const SIZE_OF_EDGES = SIZE * 8;

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

//˫���
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int Stack[SIZE_OF_VERTICES],StackTop;//����ջ
int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
//bool IsBridge[SIZE_OF_EDGES];//��i�Ƿ�Ϊ��
bool IsVisited[SIZE_OF_EDGES];//�ߵı�����飬���ر�ʱ���ô���������ж�
int Belong2BiCC[SIZE_OF_VERTICES];//��i���ڵ�Bi��˫��ͨ��������1��ʼ
int Represent[SIZE_OF_VERTICES];//Ri��ʾ��i����˫�Ĵ���Ҳ���Ǳ����С���Ǹ���
int BiCCCnt;//˫��ͨ����������

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    //��ջ
    Stack[StackTop++] = u;

    //��u��ÿһ����
    int v,son=0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            /*//��
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    if ( Low[u] == Dfn[u] ){//u�����ϵĵ���ͬһ��������
        Represent[Belong2BiCC[u] = ++BiCCCnt] = u;
        do{
            Belong2BiCC[v=Stack[--StackTop]] = BiCCCnt;
            if ( v < Represent[BiCCCnt] ) Represent[BiCCCnt] = v;
        }while( v != u );
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(Belong2BiCC,Belong2BiCC+vn+1,0);
    fill(IsVisited,IsVisited+ECnt,false);
    //fill(IsBridge,IsBridge+ECnt,false);
    BiCCCnt = StackTop = 0;

    TimeStamp = 0;

    for(int i=1;i<=vn;++i)if ( 0 == Dfn[i] )dfs(i,i);
}


int H, W;
char A[SIZE_OF_VERTICES];

bool proc(){
    int vn = H*W;
    initGraph(vn);
    char * ch;
    int idx;
    int sidx = -1;
    for(int i=0;i<H;++i)for(int j=0;j<W;++j){
        if('#' == *(ch=A+(idx=i*W+j))) continue;

        ++idx;
        if(i != H - 1 && '#' != *(ch+W)){            
            mkEdge(idx, idx+W);
        }
        if(j != W - 1 && '#' != *(ch + 1)){
            mkEdge(idx, idx + 1);
        }

        if('S' == *ch) sidx = idx;
    }
    assert(sidx != -1);

    Tarjan(vn);
    int cnt = 0;
    for(int i=1;i<=vn;++i){
        if(Belong2BiCC[i] == Belong2BiCC[sidx]){
            if(++cnt >= 4) return true;            
        }
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    scanf("%d%d", &H, &W);
    char * p = A;
    for(int i=0;i<H;++i) {
        scanf("%s", p);
        p += W;    
    }
    puts(proc()?"Yes":"No");
    return 0;
}