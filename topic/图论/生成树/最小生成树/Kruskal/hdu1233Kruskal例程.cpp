#include <cstdio>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 101

//���鼯�ṹ
int Father[SIZE];
void init(int n){for(int i=0;i<=n;Father[i]=i++);}
int find(int x){return Father[x]==x?x:Father[x]=find(Father[x]);}
void unite(int x,int y){Father[find(y)]=Father[find(x)];}

int N;

//�߽ṹ
struct edge_t{
	int s;
	int e;
	weight_t w;
}Edge[SIZE*SIZE/2];
int ECnt = 0;

//���أ����ڱ�����
bool operator < (edge_t const&lhs,edge_t const&rhs){
	if ( lhs.w != rhs.w ) return lhs.w < rhs.w;
	if ( lhs.s != rhs.s ) return lhs.s < rhs.s;
	return lhs.e < rhs.e;
}

//���ɱ�
inline void mkEdge(int a,int b,weight_t w){
	if ( a > b ) swap(a,b);

	Edge[ECnt].s = a;
	Edge[ECnt].e = b;
	Edge[ECnt++].w = w;
}

//Kruskal�㷨��vn�ǵ��������en�Ǳߵ�����������MST�ĳ���
weight_t Kruskal(int vn,int en){
	init(vn);//���鼯��ʼ��
	sort(Edge,Edge+en);//������

	weight_t ans = 0;
	for(int i=0;i<en;++i){
		//�ñ��Ѵ�����MST��
		if ( find(Edge[i].s) == find(Edge[i].e) )
			continue;

		//���ñ߼���MST
		ans += Edge[i].w;
		unite(Edge[i].s,Edge[i].e);
		--vn;

		//MST����ȫ����
		if ( 1 == vn ) break;
	}

	return ans;
}

bool read(){
	scanf("%d",&N);
	if ( 0 == N ) return false;
	
	ECnt = 0;
	for(int i=0;i<N*(N-1)/2;++i){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		mkEdge(a,b,w);
	}
	
	return true;
}

int main(){
	while( read() ){
		printf("%d\n",Kruskal(N,ECnt));
	}
	return 0;
}