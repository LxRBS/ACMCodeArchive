//�����ˣ��Լ��ܹ���֮ƥ���F��D�������ƥ����
//���Ƕ���ͼ�����ƥ�䣬ʹ���������ʵ��
//��POJ3281����һ��
#include <cstdio>
#include <climits>
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

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 2000;
int const SIZE_OF_EDGES = 8000000;

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
	ECnt = 1;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	//Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;//����ߵ�����Ϊ0
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int L[SIZE_OF_VERTICES];//���ͼ
int Queue[SIZE_OF_VERTICES];//����
//�������������Դs����t�Ĳ��ͼ��nΪ��������
bool bfs(int s,int t,int n){
	fill(L+1,L+n+1,-1);

	int u,v,head,tail = 0;
	L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		//Ѱ�һ��в����ı�
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
            //����в�����û�б��������ģ����ǲ��
			if ( Edge[p].weight > 0 && -1 == L[v = Edge[p].to] ){
                L[Queue[tail++]=v] = L[u] + 1;
			}			
		}
	}

	return -1 != L[t];
}

//�ڲ��ͼ����������·���������Ͼ��������������������
//��������Ǹ���֮����������Сֵ
//uΪ��ǰ�ڵ㣬cfΪ�Ѿ��������Ľ����tΪ���
weight_t dfs(int u,weight_t cf,int t){
	if ( u == t ) return cf;

	weight_t tf = 0;//tf��¼u����һ����ܿ�������
	for(int p=Vertex[u];p;p=Edge[p].next){
		int v = Edge[p].to;
		weight_t c = Edge[p].weight;

		if ( L[u] + 1 == L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//����߼�ȥ��������
			Edge[(p&1)?p+1:p-1].weight += f;//����߼���
			tf += f;
		}
	}
	if ( 0 == tf ) L[u] = -1;//�޸Ĳ��ͼ
	return tf;
}

//Dinic�㷨��sΪԴ��tΪ�㣬nΪͼ��������
weight_t Dinic(int s,int t,int n){
	weight_t ret = 0;
	while( bfs(s,t,n) ){//��һ�������ֲ�ͼ
		weight_t ans;
		//�ڶ����ڷֲ�ͼ�ϲ���һ������·���Ŀ�������
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
}

int N,F,D;
unsigned char T[210];
bool read(){
    if ( EOF == scanf("%d%d%d",&N,&F,&D) ) return false;

    initGraph(N+N+F+D+2);

    //Դ��ÿ��F��һ����
    for(int i=1;i<=F;++i){
        mkEdge(N+N+F+D+1,N+N+i,getUnsigned());
    }
    //ÿ��D���㽨һ����
    for(int i=1;i<=D;++i){
        mkEdge(N+N+F+i,N+N+F+D+2,getUnsigned());
    }

    //F��Ni��һ����
    for(int i=1;i<=N;++i){
        mkEdge(i,N+i,1);

        scanf("%s",T);

        for(unsigned char *p=T,j=1;*p;++j,++p){
            if ( 'Y' == *p ) mkEdge(N+N+j,i,1);
        }
    }

    //Ni��D��һ����
    for(int i=1;i<=N;++i){
        scanf("%s",T);

        for(unsigned char *p=T,j=1;*p;++j,++p){
            if ( 'Y' == *p ) mkEdge(N+i,N+N+F+j,1);
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        printf("%d\n",Dinic(N+N+F+D+1,N+N+F+D+2,N+N+F+D+2));
    }
    return 0;
}
