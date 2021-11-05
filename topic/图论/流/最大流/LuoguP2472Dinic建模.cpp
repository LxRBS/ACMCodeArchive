/**
   ��ͼ�����������ӣ�ÿ���߶�Ϊhij
   ��Щ�����������棬�������������벻����d������������
   ÿ��һ����������ȥ�����Ӹ߶ȼ�һ��ֱ��0Ϊֹ
   ������ж��ٸ�����������ȥ
   ��������ȥ�ļ���
   �����Ӳ�㣬����Ϊ��߶�
   �ٽ���ST���ɡ�
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 7200;
int const SIZE_OF_EDGES = 2520000;


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
	ECnt = 2;//ECnt��2��ʼ����ָ����0��ʾ���������^1����
	fill(Vertex,Vertex+n+1,0);
}
//�����
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
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
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
}

char A[22][22],B[22][22];
int X[440],Y[440];
int Index[22][22];

int dist2(int idx,int jdx){
    int x = X[idx] - X[jdx];
    int y = Y[idx] - Y[jdx];
    return x*x+y*y;
}

int main(){
    //freopen("1.txt","r",stdin);
    int r,c,d;
    scanf("%d%d%d",&r,&c,&d);
    int n = 0;
    for(int i=0;i<r;++i){
        scanf("%s",A[i]);
        for(char*p=A[i];*p;++p)if(*p!='0')X[++n]=i,Index[i][Y[n]=p-A[i]]=n;
    }
    for(int i=0;i<r;++i)scanf("%s",B[i]);
    //��ͼ
    int vn = n + n + 2;
    int s = vn-1, t = vn;
    initGraph(vn);
    int sum = 0;
    //s��������һ�������
    for(int i=0;i<r;++i)for(int j=0;j<c;++j)if('L'==B[i][j]){
        mkEdge(s,Index[i][j],1);
        ++sum;
    }
    int d2 = d*d;
    for(int i=1;i<=n;++i){
        //���
        mkEdge(i,i+n,A[X[i]][Y[i]]-'0');
        //����֮����˫���
        for(int j=i+1;j<=n;++j)if(dist2(i,j)<=d2){
            mkEdge(i+n,j,10000000);
            mkEdge(j+n,i,10000000);
        }
        //�ܹ�����ȥ��
        if(X[i]<d||X[i]>=r-d||Y[i]<d||Y[i]>=c-d){
            mkEdge(i+n,t,10000000);
        }
    }
    printf("%d\n",sum-Dinic(s,t,vn));
    return 0;
}
