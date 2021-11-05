/**
    ����ͼ���ʴ�S��T������������
    n��1w���ڣ�ǿ��ͨ�����Ĵ�С������100
    ��DiΪi��T����������D[T]=0
    Di = 1/n * SIGMA{Dj}+1������j��i�ĺ��
    ���Խ�һ�����̣����ǻᳬ��Χ
    ��ͼ��ΪKDAG������KDAG�ϵĵ����ʹ��DPֱ����
    ����SCC�ڲ��ĵ㣬����ʹ�ø�˹��Ԫ���ⷽ��
    �ƺ����ر�
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

int Stack[SIZE_OF_VERTICES], StackTop;//����ջ
bool IsInStack[SIZE_OF_VERTICES];

int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];

int SCCCnt;//��ͨ������������
int Belong[SIZE_OF_VERTICES];//��i���������ڵ�Belong[i]��ǿ��ͨ����
int SCCSize[SIZE_OF_VERTICES];//��i����ͨ�����Ĵ�С���±��1��ʼ
vector<int> Vec[10010];

void dfs(int u){
    Dfn[u] = Low[u] = ++TimeStamp;

    //��ջ
    IsInStack[ Stack[StackTop++] = u ] = true;

    //��u��ÿһ����
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];
        }else if ( IsInStack[v] && Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //�ҵ�һ��SCC
    if ( Dfn[u] == Low[u] ){
        ++SCCCnt;
        do{
            IsInStack[ v = Stack[--StackTop] ] = false;
            ++SCCSize[ Belong[v] = SCCCnt ];
            Vec[SCCCnt].push_back(v);//��ǰ��ͨ�����Ķ�����
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
//�ж��Ƿ��ܴ�s��t
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
    if(!isOK(s,t,n)){//�����ж�st�Ƿ�ɴ�
        puts("INF");
        return 0;
    }
    //��һ��KDAG
    Tarjan(n);
    fill(D,D+n+1,-1.0);
    D[t] = 0.0;
    //Belong��˳��ǡ����KDAG���˵ĵ���Ҳ��DP��˳��
    for(int i=1;i<=SCCCnt;++i){//�Ե�i����ͨ����
        double a[110][110] = {0.0}, b[110] = {0.0};
        int k = 0, mmap[10010] = {0};
        //���ȱ����
        for(vector<int>::const_iterator it=Vec[i].begin();it!=Vec[i].end();++it){
            a[k][k] = b[k] = 1.0;
            if(t==*it) b[k] = 0.0;
            mmap[*it] = k++;
        }
        //Ȼ����������ϵ��
        k = 0;
        for(vector<int>::const_iterator it=Vec[i].begin();it!=Vec[i].end();++it){
            if(t==*it) ;
            else if(0 == OutDeg[*it]){
                b[k] = INF;
            }else{
                double tmp = 1.0 / OutDeg[*it];
                for(int v,p=Vertex[*it];p;p=Edge[p].next){
                    if(D[v=Edge[p].to] < 0){//v�����������ʵ�ȼ���uvͬ��һ��SCC
                        a[k][mmap[v]] -= tmp;//����Ҫ��-=������ֱ�Ӹ�ֵ��Ӧ�������ر�
                    }else{
                        b[k] += tmp * D[v];
                    }
                }
            }
            ++k;
        }
        //�ⷽ��
        GaussColumnPivot(a,b,k,k);
        //�ѽ⿽�������
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

