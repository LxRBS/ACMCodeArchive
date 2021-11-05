//�������·���ٸ������·�Ľ����ͼ��Dinic
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef long long int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 5000;
int const SIZE_OF_EDGES = 500000;
weight_t const INF = 1LL<<60;

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

//���������
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

//s is the source id
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//d[i] records the shortest distance from s to i
//pre[i] records the previous node of i in the shortest path
//flag is auxiliary arrays
//returning false means there exists a negative loop in given graph
bool spfa(int s,int vn,weight_t d[],bool flag[]){
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);
	//fill(cnt,cnt+vn+1,0);
	//fill(pre,pre+vn+1,0);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	//pre[s] = 0;
	d[s] = 0;
	//cnt[s] = 1;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			weight_t t = d[u] + Edge[next].weight;

			if ( t < d[v] ){
				d[v] = t;
				//pre[v] = u;
				if ( !flag[v] ){
					//++cnt[v];
					//if ( cnt[v] > vn ) return false;

					flag[v] = true;
					q.push(v);
				}
			}
		}
	}

	return true;
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
		while( ans = dfs(s,INF,t) )
			ret += ans;
	}
	return ret;
}


int N,M;
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int A[SIZE_OF_EDGES],B[SIZE_OF_EDGES];
weight_t AB[SIZE_OF_EDGES];
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N);

    weight_t d;
    for(int i=0;i<M;++i){
        scanf("%d%d%lld",A+i,B+i,AB+i);
        mkEdge(A[i],B[i],AB[i]);mkEdge(B[i],A[i],AB[i]);
    }

    //���·
    spfa(N,N,D,Flag);

    initGraph(N+N);
    //����������·�ϣ������
    for(int i=0;i<M;++i){
        if ( D[A[i]] + AB[i] == D[B[i]] ){
            mkEdge(B[i]+N,A[i],INF);
            mkEdge(A[i],B[i]+N,0LL);
        }else if ( D[B[i]] + AB[i] == D[A[i]] ){
            mkEdge(A[i]+N,B[i],INF);
            mkEdge(B[i],A[i]+N,0LL);
        }
    }

    //��ÿ��������������в��
    for(int i=1;i<=N;++i){
        scanf("%lld",&d);
        mkEdge(i,i+N,1==i||N==i?INF:d);
        mkEdge(i+N,i,0LL);
    }

    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    read();
    printf("%lld\n",Dinic(1,N+N,N+N));
    return 0;
}
