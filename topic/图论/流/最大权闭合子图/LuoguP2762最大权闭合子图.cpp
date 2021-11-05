/**
   m��ʵ�飬n̨������ÿ��ʵ��Ҫ�õ�����һЩ����
   ÿ�������ķ�����ci��ÿ��ʵ���������pi
   �������ʵ���ܹ��þ��������
   ����һ�����Ȩ�պ���ͼ����
   ���Ϊ��Ȩ�㣬�ұ�Ϊ��Ȩ�㣬������Ȩ��
   S����Ȩ����һ���ߣ�����ΪȨ
   ��Ȩ�㵽T�����ߣ�����Ϊ����Ȩ
   ����Ȩ��֮����һ���ߣ�����Ϊ�����
   ����Ȩ��=������Ȩ֮�ͣ������
   �����������������s�����ĵ㼴��
   �����һ�ηֲ�ͼ�ϴ���0�ĵ�
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 120;
int const SIZE_OF_EDGES = 2520000;
int const INF = 0x3F3F3F3F;

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

int main(){
    //freopen("1.txt","r",stdin);
    int m,n,vn,s,t;
    int sum = 0;
    string str;
    cin>>m>>n;getline(cin,str);
    s = ( vn = t = n + m + 2 ) - 1;
    initGraph(vn);
    for(int i=1;i<=m;++i){//m��ʵ��
        getline(cin,str);
        stringstream ss(str);
        int a;
        ss>>a;
        sum+=a;
        mkEdge(s,i,a);
        while(ss>>a){//ÿ��ʵ��Ҫ�õ����������
            mkEdge(i,a+m,INF);
        }
    }
    for(int i=m+1,nn=n+m;i<=nn;++i){
        int a;
        cin>>a;
        mkEdge(i,t,a);
    }
    int ret = Dinic(s,t,vn);
    //���ʵ��
    for(int i=1;i<=m;++i)if(__L[i]>0){
        cout<<i<<" ";
    }
    cout<<endl;
    //�������
    for(int i=1+m,nn=m+n;i<=nn;++i)if(__L[i]>0){
        cout<<i-m<<" ";
    }
    cout<<endl;
    cout<<sum-ret<<endl;
    return 0;
}
