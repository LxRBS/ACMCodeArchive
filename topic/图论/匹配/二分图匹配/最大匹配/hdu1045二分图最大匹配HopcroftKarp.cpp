/*
    �������̣��������������ϰ���
    ������ܷŶ��ٸ���ʹ�û��಻����
    ���û���ϰ������һ����С�㸲�ǣ��������ƥ��
    ����Ϊһ����ÿһ��Ϊ�൱�ڶ���ͼ��һ���㣬����Ϊһ��
    �������ϰ����ÿһ�п�����Ҫ�ֳɶ���ͼ�ϵļ�����
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 251000;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

int L[SIZE_OF_VERTICES];//Li���i����ƥ��ĵ㣬ע�����������ȫͼ�ı�Ŷ����Ƕ���ͼ��ţ��ر��Ƕ�B���ֵĵ�

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
	fill(L,L+n+1,0);
}

//�����
inline void mkEdge(int a,int b){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int D[SIZE_OF_VERTICES];
int Q[SIZE_OF_VERTICES];//��������
bool bfs(int na,int nb,int n){
    bool ret = false;
    fill(D,D+n+1,0);

    int head,tail = 0;
    for(int i=1;i<=na;++i) if ( !L[i] ) Q[tail++] = i;//���

    int u,v;
    for(head=0;head<tail;++head){
        //��ÿһ�����ÿһ����
        for(int p=Vertex[u=Q[head]];p;p=Edge[p].next){
            if ( !D[v=Edge[p].to] ){
                D[v] = D[u] + 1;
                if ( !L[v] ) ret = true;
                else D[L[v]] = D[v] + 1, Q[tail++] = L[v];
            }
        }
    }
    return ret;
}

bool dfs(int u){
    int v;
    for(int p=Vertex[u];p;p=Edge[p].next){
        if ( D[v=Edge[p].to] == D[u] + 1 ){
            D[v] = 0;
            if ( !L[v] || dfs(L[v]) ){
                L[ L[v] = u ] = v;
                return true;
            }
        }
    }
    return false;
}

//na��A��������nb��B��������n��������
int HopcroftKarp(int na,int nb,int n){
    int ret = 0;
    while( bfs(na,nb,n) ){
        for(int i=1;i<=na;++i){
            if ( !L[i] && dfs(i) ) ++ret;
        }
    }
    return ret;
}

int N,AN,BN,VN;
char A[10][10];

int BelongRow[10][10],BelongCol[10][10];
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;

    fgets(A[0],9,stdin);
    for(int i=0;i<N;++i) fgets(A[i],9,stdin);

    //����������еĲ���
    int k = 1;
    for(int i=0;i<N;++i){
        int col = 0;
        while( col < N ){
            while( col < N && A[i][col] != '.' ) ++col;
            if ( N == col ) break;

            while( col < N && A[i][col] == '.' ) BelongRow[i][col++] = k;
            ++k;
        }
    }
    AN = k;

    //���������еĲ���
    for(int i=0;i<N;++i){
        int row = 0;
        while( row < N ){
            while( row < N && A[row][i] != '.' ) ++row;
            if ( N == row ) break;

            while( row < N && A[row][i] == '.' ) BelongCol[row++][i] = k;
            ++k;
        }
    }
    BN = k - AN;

    //��ͼ
    initGraph(VN=k);
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if('.'==A[i][j]){
        mkEdge(BelongRow[i][j],BelongCol[i][j]);
    }

    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        printf("%d\n",HopcroftKarp(AN,BN,VN));
    }
    return 0;
}
