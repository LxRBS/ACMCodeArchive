/**
    有向图，问从S到T的期望步数，
    n在1w以内，强连通分量的大小不超过100
    令Di为i到T的期望，则D[T]=0
    Di = 1/n * SIGMA{Dj}+1，其中j是i的后继
    可以解一个方程，但是会超范围
    将图变为KDAG，对于KDAG上的点可以使用DP直接做
    对于SCC内部的点，可以使用高斯消元法解方程
    似乎有重边
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


int const SIZE_OF_COLUMN = 110;//TODO

double const INF = 1E18;
double const EPS = 1E-7;
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

int const SIZE_OF_VERTICES = 11000;
int const SIZE_OF_EDGES = 2200000;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

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
}

int Stack[SIZE_OF_VERTICES], StackTop;//辅助栈
bool IsInStack[SIZE_OF_VERTICES];

int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];

int SCCCnt;//连通分量的总数量
int Belong[SIZE_OF_VERTICES];//第i个顶点属于第Belong[i]个强连通分量
int SCCSize[SIZE_OF_VERTICES];//第i个连通分量的大小，下标从1开始
vector<int> Vec[10010];

void dfs(int u){
    Dfn[u] = Low[u] = ++TimeStamp;

    //入栈
    IsInStack[ Stack[StackTop++] = u ] = true;

    //对u的每一条边
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];
        }else if ( IsInStack[v] && Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //找到一个SCC
    if ( Dfn[u] == Low[u] ){
        ++SCCCnt;
        do{
            IsInStack[ v = Stack[--StackTop] ] = false;
            ++SCCSize[ Belong[v] = SCCCnt ];
            Vec[SCCCnt].push_back(v);//当前连通分量的顶点编号
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
//判断是否能从s到t
bool isOK(int s,int t,int n){
    if (s==t) return true;

    bool flag[10010] = {false};
    queue<int> q;
    q.push(s);flag[s] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v,p=Vertex[u];p;p=Edge[p].next){
            if((v=Edge[p].to)==t) return true;
            if(!flag[v]){
                flag[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

int OutDeg[10010] = {0};
double D[10010] = {0.0};
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    int s = getUnsigned();
    int t = getUnsigned();
    initGraph(n);
    for(int i=0;i<m;++i){
        int a = getUnsigned();
        mkEdge(a, getUnsigned());
        ++OutDeg[a];
    }
    if(!isOK(s,t,n)){//首先判断st是否可达
        puts("INF");
        return 0;
    }
    //求一个KDAG
    Tarjan(n);
    fill(D,D+n+1,-1.0);
    D[t] = 0.0;
    //Belong的顺序恰好是KDAG拓扑的倒序，也是DP的顺序
    for(int i=1;i<=SCCCnt;++i){//对第i个连通分量
        double a[110][110] = {0.0}, b[110] = {0.0};
        int k = 0, mmap[10010] = {0};
        //首先编个号
        for(vector<int>::const_iterator it=Vec[i].begin();it!=Vec[i].end();++it){
            a[k][k] = b[k] = 1.0;
            if(t==*it) b[k] = 0.0;
            mmap[*it] = k++;
        }
        //然后求其他项系数
        k = 0;
        for(vector<int>::const_iterator it=Vec[i].begin();it!=Vec[i].end();++it){
            if(t==*it) ;
            else if(0 == OutDeg[*it]){
                b[k] = INF;
            }else{
                double tmp = 1.0 / OutDeg[*it];
                for(int v,p=Vertex[*it];p;p=Edge[p].next){
                    if(D[v=Edge[p].to] < 0){//v还有算出来其实等价于uv同属一个SCC
                        a[k][mmap[v]] -= tmp;//这里要用-=，不能直接赋值，应该是有重边
                    }else{
                        b[k] += tmp * D[v];
                    }
                }
            }
            ++k;
        }
        //解方程
        GaussColumnPivot(a,b,k,k);
        //把解拷贝到结果
        for(vector<int>::const_iterator it=Vec[i].begin();it!=Vec[i].end();++it){
            D[*it] = b[mmap[*it]];
            if(D[*it]>1E10) D[*it] = INF;
        }
        if(D[s]>=0) break;
    }
    if(D[s]>1E10) puts("INF");
    else printf("%.3f\n",D[s]);
    return 0;
}

