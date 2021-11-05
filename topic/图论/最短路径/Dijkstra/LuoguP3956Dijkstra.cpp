/**
    m��m�����̣��������ߵ����£�ֻ���������ң�ֻ��������ɫ�ĸ���
    ���ӿ����Ǻ�ɫ����ɫ��������ɫ
    1 �ߵ���ͬ��ɫ���ӻ�1����ң���ͬ��ɫ������
    2 ���Խ���һ����ɫ���Ӹĳ�ָ����ɫ������2��
      ��������ʹ�ã������߹��Ժ���ӻ�ָ�����ɫ
    �ʻ��������Ƕ��٣���㱣֤����ɫ��ע���յ�����ɫ�����
    m��100����
    ��������ɫ���ӣ�����4�����Լ�Manhattan����Ϊ2��8����
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 22000;
int const SIZE_OF_EDGES = 220000;
weight_t const INF = 1000000000;

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

inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
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
void Dijkstra(int s,int vn,weight_t d[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,0));

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
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int D2D2[][3] = {
    {0,1,2},{4,5,6},{0,6,7},{2,3,4}
};

int const DR2[] = {-1,-2,-1,0,1,2,1,0};
int const DC2[] = {-1,0,1,2,1,0,-1,-2};

weight_t D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

int A[110][110],Index[110][110];
int Row[1100],Col[1100],Color[1100];

//����һ������ɫ�ĸ��ӣ���ȡ������ɫ4������8����
void g(int idx,int jdx,int m,int r[],int c[],int r2[],int c2[],int&k,int&k2){
    k = k2 = 0;
    vector<int> v;
    for(int i=0;i<4;++i){//����4����
        int dr = idx + DR[i];
        int dc = jdx + DC[i];
        if(1<=dr&&dr<=m&&1<=dc&&dc<=m){
            if(A[dr][dc]){//����ɫ�ĸ���
                r[k] = dr;
                c[k++] = dc;
            }else{//�ո�
                v.insert(v.end(),D2D2[i],D2D2[i]+3);
            }
        }
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(vector<int>::const_iterator it=v.begin();it!=v.end();++it){
        int dr = idx + DR2[*it];
        int dc = jdx + DC2[*it];
        if(1<=dr&&dr<=m&&1<=dc&&dc<=m&&A[dr][dc]){
            r2[k2] = dr;
            c2[k2++] = dc;
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    int m = getUnsigned();
    int n = getUnsigned();
    for(int i=1;i<=n;++i){
        Row[i]=getUnsigned(),Col[i]=getUnsigned(),Color[i]=getUnsigned();
        A[Row[i]][Col[i]] = ( Color[i] ? Color[i] : ( Color[i] = 2 ) );
        Index[Row[i]][Col[i]] = i;
    }
    //��ͼ
    initGraph(1);
    for(int i=1;i<=n;++i){
        int k,k2,r[4],c[4],r2[8],c2[8];
        g(Row[i],Col[i],m,r,c,r2,c2,k,k2);
        for(int j=0;j<k;++j){//��ÿһ������ɫ��4����
            mkEdge(i,Index[r[j]][c[j]],Color[i]!=A[r[j]][c[j]]?1:0);
        }
        for(int j=0;j<k2;++j){//��ÿһ������ɫ��8����
            mkEdge(i,Index[r2[j]][c2[j]],Color[i]!=A[r2[j]][c2[j]]?3:2);
        }
    }
    Dijkstra(1,n,D,Flag);
    weight_t ans = D[Index[m][m]];
    if(INF==ans){//����(m-1,m)��(m,m-1)
        ans = min(D[Index[m-1][m]],D[Index[m][m-1]]);
        ans += 2;
    }
    printf("%d\n",ans>=INF?-1:ans);
    return 0;
}
