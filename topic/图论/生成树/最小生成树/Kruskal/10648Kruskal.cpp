#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 200001

//���鼯����
int Father[SIZE];

//���鼯����
inline void init(int n){
	for(int i=0;i<n;++i) 
		Father[i] = i;
}
//���鼯����
inline int find(int x){
	return x == Father[x] ? x : Father[x] = find(Father[x]);
}
//���鼯����
inline void unite(int x,int y){
	x = find(x);
	y = find(y);
	x < y ? Father[y] = x : Father[x] = y;
}

//�ߵĽṹ
int Vertex[SIZE];
struct edge_t{
    int s;
	int e;
	int weight;
}Edge[SIZE];
bool operator < (edge_t const&l,edge_t const&r){
	if ( l.weight != r.weight ) return l.weight < r.weight;
	if ( l.s != r.s ) return l.s < r.s;
	return l.e < r.e;
}

//Kruskal�㷨��vnΪ���������enΪ�ߵ�����������MST�ĳ���
int Kruskal(int vn,int en){
	init(vn);

    sort(Edge,Edge+en);

	int ans = 0;
	for(int i=0;i<en;++i){
		if ( find(Edge[i].s) != find(Edge[i].e) ){
			ans += Edge[i].weight;
			unite(Edge[i].s,Edge[i].e);
                --vn;
		}
            if ( 1 == vn ) break;
	}
	return ans;
}

int main(){
	int m,n;
	while( scanf("%d%d",&m,&n) ){
		if ( 0 == n && 0 == m ) return 0;

		int sum = 0;
		for(int i=0;i<n;++i){
			scanf("%d%d%d",&Edge[i].s,&Edge[i].e,&Edge[i].weight);
			sum += Edge[i].weight;
		}

		printf("%d\n",sum - Kruskal(m,n));
	}

	return 0;
}
