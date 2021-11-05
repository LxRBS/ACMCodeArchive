#include <cstdio>
#include <queue>
#include <vector>
#include <bitset>
using namespace std;
typedef vector<int> vi;

struct point_t{
	int x,y;
}P[1001];

int N,D;

inline int dist2(point_t const&a,point_t const&b){
    int x = a.x - b.x;
	int y = a.y - b.y;
	return x * x + y * y;
}

inline bool isOK(point_t const&a,point_t const&b){return D * D >= dist2(a,b);}
inline bool isOK(int x,int y){return x * x + y * y <= ( D + 15 ) * ( D + 15 );}
inline bool isOK(int idx){
	int x = P[idx].x, y = P[idx].y;
	return 500 - x <= D || x + 500 <= D 
	    || 500 - y <= D || y + 500 <= D;
}

//[0,N)��ʾͼ�еĵ㣬N��ʾ��㣬N+1��ʾ�յ�
int Graph[1002][1002];//ͼ���ڽӾ���
int Cnt[1002];

//��ͼ
void mkGraph(){
    fill(Cnt,Cnt+N+2,0);
	
	//ͼ�еĵ�
	for(int i=0;i<N-1;++i)
		for(int j=i+1;j<N;++j)
		    if ( isOK(P[i],P[j]) )
		        Graph[i][Cnt[i]++] = j, Graph[j][Cnt[j]++] = i;

	//ȷ�����
	for(int i=0;i<N;++i)if(isOK(P[i].x,P[i].y))
		Graph[N][Cnt[N]++] = i;

	//ȷ���յ�
	for(int i=0;i<N;++i)if(isOK(i))
		Graph[i][Cnt[i]++] = N + 1;
}

//spfa�㷨,sΪԴ
int Dist[1003];
bool Flag[1003];
int Path[1003];//��¼�����·����Path[i]��iǰ����Ǹ��ڵ�
bool spfa(int s){
	Path[s] = -1;

    fill(Dist,Dist+N+2,INT_MAX);
	Dist[s] = 0;

	fill(Flag,Flag+N+2,false);
	Flag[s] = true;

	queue<int> q;
	q.push(s);

	while( !q.empty() ){
        int u = q.front();
		q.pop();
        Flag[u] = false;

		//��u��ÿһ���ڵ�
		for(int i=0;i<Cnt[u];++i){
			int v = Graph[u][i];
			int tmp = Dist[u] + 1;

			if ( tmp < Dist[v] ){
				Path[v] = u;
				Dist[v] = tmp;
				if ( !Flag[v] ) q.push(v), Flag[v] = true;
			}
		}
	}
	return true;
}

void prnPath(int idx){
	if ( -1 != Path[idx] )
		prnPath(Path[idx]);

	if ( -1 == Path[idx] || N + 1 == idx ) return;
	
	printf("%d %d\n",P[idx].x,P[idx].y);
}

int main(){
//	freopen("1.std.in","r",stdin);
	while( scanf("%d",&N) ){
		if ( -1 == N ) return 0;

		//����
		scanf("%d",&D);
		for(int i=0;i<N;++i)scanf("%d%d",&P[i].x,&P[i].y);

		//�������ֱ����������
		if ( D + 15 >= 500 ){
			printf("1\n");
			continue;
		}

        //��ͼ
		mkGraph();

		//��Դ���·��
		spfa(N);

		//���
		if ( INT_MAX == Dist[N+1] ){
		    printf("-1\n");
			continue;
		}

        printf("%d\n",Dist[N+1]);
        prnPath(N+1);
	}    
}
