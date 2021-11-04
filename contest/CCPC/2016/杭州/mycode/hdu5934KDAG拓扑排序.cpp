/*
   ƽ������N��ը�����и��Ե��𱬷���
   �����ը��Χ��������ը��������Щը��Ҳ������
   ����������ը���������С����
   ��Ȼ���A������B����A��B��һ����
   �ڵ�A�����������пɴ��̶������������Ҫ�������Ϊ0�ĵ�
   ��Ҳ�п�����һ��ǿ��ͨ���������Ҫ���㣬�õ�DAG
   �ٰ��������Ϊ0�ĵ�ķ��ü�����
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[1100*1100];
int ECnt;
int Vertex[1100];

inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}
int Stack[1100], StackTop;//����ջ
bool IsInStack[1100];

int TimeStamp;
int Dfn[1100], Low[1100];

int SCCCnt;//��ͨ������������
int Belong[1100];//��i���������ڵ�Belong[i]��ǿ��ͨ����
int SCCSize[1100];//��i����ͨ�����Ĵ�С���±��1��ʼ

void dfs(int u){
    Dfn[u] = Low[u] = ++TimeStamp;

    //��ջ
    IsInStack[ Stack[StackTop++] = u ] = true;

    //��u��ÿһ����
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];
        }else if ( IsInStack[v] && Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //�ҵ�һ��SCC
    if ( Dfn[u] == Low[u] ){
        ++SCCCnt;
        do{
            IsInStack[ v = Stack[--StackTop] ] = false;
            ++SCCSize[ Belong[v] = SCCCnt ];
        }while( v != u );
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(IsInStack,IsInStack+vn+1,false);
    fill(SCCSize,SCCSize+vn+1,0);

    TimeStamp = SCCCnt = StackTop = 0;

    for(int i=1;i<=vn;++i){
        if ( 0 == Dfn[i] ){
            dfs(i);
        }
    }
}

int Cost[1100];
int X[1100],Y[1100],R[1100];
int N;

//idx��jdx��һ����
bool f(int idx,int jdx){
    long long int x = X[idx] - X[jdx];
    long long int y = Y[idx] - Y[jdx];
    long long int r = R[idx];
    return x*x+y*y<=r*r;
}

void read(){
    initGraph(N = getInt());

    for(int i=1;i<=N;++i){
        X[i] = getInt();
        Y[i] = getInt();
        R[i] = getInt();
        Cost[i] = getInt();
        for(int j=1;j<i;++j){
            if(f(i,j)) mkEdge(i,j);
            if(f(j,i)) mkEdge(j,i);
        }
    }
}

int Degree[1100];
int Ans[1100];
int proc(){
    //��ǿ��ͨ����
    Tarjan(N);

    //��ÿһ��ǿ��ͨ��������СȨֵ
    fill(Ans,Ans+SCCCnt+1,1000000);
    for(int i=1;i<=N;++i){
        if(Cost[i]<Ans[Belong[i]]){
            Ans[Belong[i]] = Cost[i];
        }
    }
    //����KDAG����¼��������
    int from,to;
    fill(Degree,Degree+SCCCnt+1,0);
    for(int i=2;i<ECnt;++i){
        //from��to��һ����
        if ( (from=Belong[Edge[i].from]) != (to=Belong[Edge[i].to]) ){
                ++Degree[to];
        }
    }
    //�����Ϊ0���ۼ�
    int ret = 0;
    for(int i=1;i<=SCCCnt;++i){
        if(0==Degree[i]){
            ret += Ans[i];
        }
    }
    return ret;
}

int main(){
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case #%d: %d\n",kase,proc());
    }
    return 0;
}
