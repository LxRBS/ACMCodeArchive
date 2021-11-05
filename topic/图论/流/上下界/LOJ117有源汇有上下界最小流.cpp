/**
    ��Դ�������½���С��
    ģ����
    �ýṹ���TLEһ����
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef long long int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 100010;
int const SIZE_OF_EDGES = 126000<<2;
weight_t const INF = 0x3F3F3F3F3F3F3F3F;

struct edge_t{
	int from,to;
	weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
edge_t* EPtr;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;//ECnt��2��ʼ����ָ����0��ʾ���������^1����
	EPtr = Edge + 2;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;//����ߵ�����Ϊ0
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;//*/
}

int __L[SIZE_OF_VERTICES];//���ͼ
int Queue[SIZE_OF_VERTICES];//����
//�������������Դs����t�Ĳ��ͼ��nΪ��������
bool bfs(int s,int t,int n){
	fill(__L+1,__L+n+1,-1);

	int u,v,head,tail = 0;
	__L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		//Ѱ�һ��в����ı�
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
            //����в�����û�б��������ģ����ǲ��
			if ( Edge[p].weight > 0 && -1 == __L[v = Edge[p].to] ){
                __L[Queue[tail++]=v] = __L[u] + 1;
			}
		}
	}

	return -1 != __L[t];
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

		if ( __L[u] + 1 == __L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//����߼�ȥ��������
			Edge[p^1].weight += f;//����߼���
			tf += f;
		}
	}
	if ( 0 == tf ) __L[u] = -1;//�޸Ĳ��ͼ
	return tf;
}

//Dinic�㷨��sΪԴ��tΪ�㣬nΪͼ��������
weight_t Dinic(int s,int t,int n){
	weight_t ret = 0;
	while( bfs(s,t,n) ){//��һ�������ֲ�ͼ
		weight_t ans;
		//�ڶ����ڷֲ�ͼ�ϲ���һ������·���Ŀ�������
		while( ans = dfs(s,0x7FFFFFFFFFFFFFFF,t) )
			ret += ans;
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

weight_t J[SIZE_OF_VERTICES];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    int s = getUnsigned();
    int t = getUnsigned();
    int vn = n + 2;
    initGraph(vn);
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        int lower = getUnsigned();
        int upper = getUnsigned();
        J[a] -= lower;
        J[b] += lower;
        mkEdge(a, b, upper - lower);
    }
    mkEdge(t, s, INF);
    int ss = n + 1, tt = n + 2;
    weight_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (J[i] >= 0)
            mkEdge(ss, i, J[i]), sum += J[i];
        else
            mkEdge(i, tt, -J[i]);
    }

    weight_t flow = Dinic(ss, tt, vn);
    if (flow != sum) {
        puts("please go home to sleep");
    } else {
        printf("%lld\n", INF - Dinic(t, s, n));
    }
    return 0;
}
