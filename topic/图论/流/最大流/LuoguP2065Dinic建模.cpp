/**
   ��������1
   A������m������B������n����
   ÿ�δ�AB��ȡ1���Ҳ�����
   �������ȡ���ٶԣ�
   �����Ͽ����ö���ƥ�䣬
   ����ȷ���ߵĹ��̾���Ҫn^2log(value)����ʱ
   ���������������Ϊpi
   ai��pi��һ���ߣ�pi��bi��һ����
   ���趨һ������ST���������
   1000w���ڵ�������66w+
   ����O2�Ż��ɹ������߰�ͼ�ĵ���Ū��һ��
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 720000;
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

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;//����ߵ�����Ϊ0
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
int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//����ɸ��
int const SIZE = 1E7 + 2;
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[700000];//P[i]Ϊ��i��������i��0��ʼ��1000w���ڵ�������66w+
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
int Index[SIZE];
void sieve(){
    for(long long int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[Index[i]=PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    //����ɸ����
    sieve();
    int vn,s,t;
    int nofkase = getUnsigned();
    while(nofkase--){
        int m = getUnsigned();
        int n = getUnsigned();
        int a,tmp = n + m;
        int tmp2 = tmp + tmp + 1;
        //��ͼ
        initGraph(vn=n+n+m+m+PCnt+2);
        s = (t=vn) - 1;
        //���벢������
        for(int i=1;i<=m;++i){
            a = getUnsigned();
            for(int j=0;j<PCnt&&P[j]*P[j]<=a;++j){
                if(0==a%P[j]){
                    do a/=P[j];while(0==a%P[j]);
                    //i��Pj��һ����
                    mkEdge(i+tmp,j+tmp2,1);
                }
            }
            if(a!=1){//aҲ��һ��������
                mkEdge(i+tmp,Index[a]+tmp2,1);
            }
            //���
            mkEdge(i,i+tmp,1);
            //S��i��һ����
            mkEdge(s,i,1);
        }
        for(int i=m+1,nn=n+m;i<=nn;++i){
            a = getUnsigned();
            for(int j=0;j<PCnt&&P[j]*P[j]<=a;++j){
                if(0==a%P[j]){
                    do a/=P[j];while(0==a%P[j]);
                    //Pj��i��һ����
                    mkEdge(j+tmp2,i,1);
                }
            }
            if(a!=1)mkEdge(Index[a]+tmp2,i,1);
            //���
            mkEdge(i,i+tmp,1);
            //i��t��һ����
            mkEdge(i+tmp,t,1);
        }

        printf("%d\n",Dinic(s,t,vn));
    }
    return 0;
}
