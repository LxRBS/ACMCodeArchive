/**
    无向图从1到n，边从1到m，
    等概率随机游走。如何确定边使得期望最小，求最小
*/
#include <bits/stdc++.h>
using namespace std;
int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int const SIZE_OF_COLUMN = 510;//TODO

double const EPS = 1E-6;
inline double is0(double x){return -EPS<x&&x<EPS;}

//ax = b, and b will be the result after calling, a will be the identity matrix, 0 indexed
//cntOfEq is the amount of equations, it is count of rows in fact.
//cntOfUnkown is the amount of X, it is count of columns in fact.
//returns 1 if there is solution
int GaussColumnPivot(double (*a)[SIZE_OF_COLUMN],double b[],int cntOfEq,int cntOfUnkown){
    for(int k=0,col=0;k<cntOfEq&&col<cntOfUnkown;++k,++col){
        int maxr = k;
        for(int i=k+1;i<cntOfEq;++i){
            if ( fabs(a[i][col]) > fabs(a[maxr][col]) ){
                maxr = i;
            }
        }

        if ( is0(a[maxr][col]) ) return 0;

        if ( k != maxr ){
            for(int j=col;j<cntOfUnkown;++j) swap(a[k][j],a[maxr][j]);
            swap(b[k],b[maxr]);
        }

        b[k] /= a[k][col];
        for(int j=col+1;j<cntOfUnkown;++j) a[k][j] /= a[k][col];
        a[k][col] = 1.0;

        for(int i=0;i<cntOfEq;++i){
            if ( i == k ) continue;

            b[i] -= a[i][k] * b[k];
            for(int j=col+1;j<cntOfUnkown;++j) a[i][j] -= a[k][j] * a[i][col];
            a[i][col] = 0.0;
        }
    }
    return 1;
}

int const SIZE_OF_VERTICES = 510;
int const SIZE_OF_EDGES = 125010<<1;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];
int Degree[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}
double A[510][510],B[510];
double E[125010];

/**
    设Ee为边的期望次数，则Ee = Eu/Degree[u] + Ev/Degree[v]
    e是uv边，Eu是每个点的期望次数
    Ev = SIGMA{Eu/Degree[u]}，uv有一条边，且u!=n
    E1 = SIGMA{Eu/Degree[u]} + 1，因为1点一开始有1次
    解方程即可
*/
void f1(int n,int m){
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));
    B[0] = 1.0;
    for(int i=0;i<n-1;++i){
        A[i][i] = 1.0;
        for(int v,p=Vertex[i+1];p;p=Edge[p].next){
            v = Edge[p].to;
            if(v!=n){
                A[i][v-1] -= 1.0 / Degree[v];
            }
        }
    }
    GaussColumnPivot(A,B,n,n);
    //计算边的期望
    for(int u,v,i=0,j=2;i<m;++i,j+=2){
        u = Edge[j].from;
        v = Edge[j].to;
        E[i] = B[u-1] / Degree[u] + B[v-1] / Degree[v];
    }
    sort(E,E+m);
    double ans = 0.0;
    for(int i=0;i<m;++i){
        ans += E[i] * (m - i);
    }
    printf("%.3f\n",ans);
}

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    initGraph(n);
    for(int a,b,i=1;i<=m;++i){
        ++Degree[a=getUnsigned()];
        ++Degree[b=getUnsigned()];
        mkEdge(a, b);
    }
    f1(n,m);
    return 0;
}
