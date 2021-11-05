/**
   一个n×m的矩阵，每一格上有Plant
   每个Plant有一个得分，得分为正表示吃掉该植物的收益，否则表示代价
   每个植物有一个攻击集合，包含若干个位置
   Zombie从右边进入地图，只能水平移动
   问如何安排Zombie，是的净收益最大
   如果b植物位于a植物的攻击位置，则必须先吃掉a再吃掉b，
   另外，如果b位于a的同一行左侧，也必须先吃掉a再吃掉b
   最大权闭合子图问题
   注意拓扑排序的边与网络流的边刚好是反向的
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 60000;
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
	ECnt = 2;//ECnt从2开始，空指针用0表示，反向边用^1计算
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

int __L[SIZE_OF_VERTICES];//层次图
int Queue[SIZE_OF_VERTICES];//队列
//建立残留网络从源s到汇t的层次图，n为顶点总数
bool bfs(int s,int t,int n){
	fill(__L+1,__L+n+1,-1);

	int u,v,head,tail = 0;
	__L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		//寻找还有残量的边
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
            //如果有残量又没有被搜索过的，则标记层次
			if ( Edge[p].weight > 0 && -1 == __L[v = Edge[p].to] ){
                __L[Queue[tail++]=v] = __L[u] + 1;
			}
		}
	}

	return -1 != __L[t];
}

//在层次图上搜索增广路径，本质上就是搜索可以增广的流量
//这个流量是各层之间流量的最小值
//u为当前节点，cf为已经搜索出的结果，t为汇点
weight_t dfs(int u,weight_t cf,int t){
	if ( u == t ) return cf;

	weight_t tf = 0;//tf记录u往下一层的总可行流量
	for(int p=Vertex[u];p;p=Edge[p].next){
		int v = Edge[p].to;
		weight_t c = Edge[p].weight;

		if ( __L[u] + 1 == __L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//正向边减去可行流量
			Edge[p^1].weight += f;//反向边加上
			tf += f;
		}
	}
	if ( 0 == tf ) __L[u] = -1;//修改层次图
	return tf;
}

//Dinic算法，s为源，t为汇，n为图顶点总数
weight_t Dinic(int s,int t,int n){
	weight_t ret = 0;
	while( bfs(s,t,n) ){//第一步建立分层图
		weight_t ans;
		//第二步在分层图上查找一条增广路径的可行流量
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}
vector<vector<int> > G;
int InDeg[660];
int W[22][32];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    int m = getInt();
    int vn = n*m;
    G.assign(vn,vector<int>());
    for(int i=0;i<n;++i)for(int j=0;j<m;++j){
        W[i][j] = getInt();
        int r,c,a = getInt();
        int k = i*m+j;
        while(a--){
            r = getInt();
            c = getInt();
            G[k].push_back(r*m+c);
            ++InDeg[r*m+c];
        }
        if(j){
            G[k].push_back(k-1);
            ++InDeg[k-1];
        }
    }
    //做一个拓扑排序
    int q[660];
    bool flag[660]={false};
    int *head=q,*tail=q;
    for(int i=0;i<vn;++i)if(0==InDeg[i])flag[*head++=i]=true;
    while(head!=tail){
        vector<int>const&v=G[*tail++];
        for(vector<int>::const_iterator it=v.begin();it!=v.end();++it){
            if(0==--InDeg[*it])flag[*head++=*it]=true;
        }
    }
    //q里面的点是可以进行最大流的
    vn += 2;
    int s = vn-1, t = vn;
    initGraph(vn);
    int sum = 0;
    for(int*p=q;p!=tail;++p){
        int index = *p + 1;
        int r = *p/m;
        int c = *p%m;
        if(W[r][c]>0) sum+=W[r][c],mkEdge(s,index,W[r][c]);
        else mkEdge(index,t,-W[r][c]);
        vector<int>const&v=G[*p];
        for(vector<int>::const_iterator it=v.begin();it!=v.end();++it){
            if(flag[*it]){
                mkEdge(*it+1,index,INF);
            }
        }
    }
    printf("%d\n",max(sum-Dinic(s,t,vn),0));
    return 0;
}
