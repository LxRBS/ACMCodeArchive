/*
    Nyaͼһ����N���ڵ�
    ÿ���ڵ�����ĳһ����
    ��x���ĳ���ڵ��ƶ���x+1���ĳ���ڵ㣬
    ��Ҫ����C��ע���·��˫���
    ������M���ߣ�ÿ��������u��v���һ���Ϊw
    �ʴӽڵ�1���ڵ�N����С����

    ���Ȳ��ܼ򵥵Ľ�����֮������нڵ�����
    ��Ϊ�������Ϊ1E5�����ƽ����Ϊ10�㣬
    ÿ��ĵ�������1E4������֮���������ߣ�
    ����1E4��ƽ������ʱ
    
    ������Ҫ����������ͼ�ķ���
    ������Ҳ�����ǵ㣬����
    ������ȻҪ����һЩ����
    1
    3 0 1
    1 1 1
    ��Ӧ����-1
*/

#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1000010;
int const SIZE_OF_EDGES = 1000010;
weight_t const INF = 2000000000;

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

//�����
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
/*
	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
*/
}

//this is for heap
struct dijkstra_t{
    int u;
    weight_t w;
    dijkstra_t(int a,weight_t b):u(a),w(b){}
};
bool operator < (dijkstra_t const&lhs,dijkstra_t const&rhs){
    return rhs.w < lhs.w || ( lhs.w == rhs.w && rhs.u < lhs.u );
}

//s is the source
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//di records the shortest distance from s to i
//pre records the previous vertex of i in the shortest path
//flag is auxiliary array
void Dijkstra(int s,int vn,weight_t d[],bool flag[]/*,int pre[]*/){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,0));

    //pre[s] = 0;
    d[s] = 0;

    while( 1 ){
        while( !q.empty() && flag[q.top().u] ) q.pop();

        if ( q.empty() ) return;

        dijkstra_t head = q.top();
        q.pop();
        int v,u = head.u;
        weight_t tmp;
        flag[u] = true;

        for(int next=Vertex[u];next;next=Edge[next].next){
            if ( !flag[v = Edge[next].to] && (tmp=d[u]+Edge[next].weight) < d[v] ){
            	//pre[v] = u;
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int N,M,C;
int Layer[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

void read(){
    scanf("%d%d%d",&N,&M,&C);

    initGraph(N+N);

    //�������
    fill(Flag,Flag+N+1,false);
    for(int i=1;i<=N;++i){
        scanf("%d",Layer+i),Flag[Layer[i]] = true;
    }

    //M����
    int a,b,w;
    for(int i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&w);
        mkEdge(a,b,w);
        mkEdge(b,a,w);
    }

    //�����֮�佨��
    for(int i=1;i<N;++i)if(Flag[i]&&Flag[i+1]){
        mkEdge(N+i,N+i+1,C);
        mkEdge(N+i+1,N+i,C);
    }

    //�����֮�佨��
    for(int i=1;i<=N;++i){
        //�㵽�㽨һ�������
        mkEdge(Layer[i]+N,i,0);
        //�㵽���ڲ㽨һ�������
        if ( Layer[i] > 1 ) mkEdge(i,Layer[i]+N-1,C);
        if ( Layer[i] < N ) mkEdge(i,Layer[i]+N+1,C);
    }
}

weight_t D[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        Dijkstra(1,N+N,D,Flag);
        printf("Case #%d: %d\n",kase,INF!=D[N]?D[N]:-1);
    }
}