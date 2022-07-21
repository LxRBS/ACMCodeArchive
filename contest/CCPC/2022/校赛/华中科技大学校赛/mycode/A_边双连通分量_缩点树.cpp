/**
 * ������ͨͼ�����ɸ�ѯ�ʡ�ÿ���ʣ�����uvxy4���㣬����ѡux��vy����uy��vx��·���Ĺ����������Ƕ���
 * ���Ǳ�˫�����4������ͬһ����˫�У����Ȼ������Ϊ0����Ϊû��һ�����Ǳ���ͬʱ����������·��֮�е�
 * ��˫������Ȼ�γ�һ������������Ŀ��Ϊ�����ϸ���4���㣬��·���Ĺ����������� 
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100001];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 133;
#else
int const SIZE = 2E5+7;
#endif

//just as its names
int const SIZE_OF_VERTICES = SIZE;
int const SIZE_OF_EDGES = SIZE * 3;

struct edge_t{
	int from,to;
	//weight_t weight;
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

//˫���
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int Stack[SIZE_OF_VERTICES],StackTop;//����ջ
int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
//bool IsBridge[SIZE_OF_EDGES];//��i�Ƿ�Ϊ��
bool IsVisited[SIZE_OF_EDGES];//�ߵı�����飬���ر�ʱ���ô���������ж�
int Belong2BiCC[SIZE_OF_VERTICES];//��i���ڵ�Bi��˫��ͨ��������1��ʼ
int Represent[SIZE_OF_VERTICES];//Ri��ʾ��i����˫�Ĵ���Ҳ���Ǳ����С���Ǹ���
int BiCCCnt;//˫��ͨ����������

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    //��ջ
    Stack[StackTop++] = u;

    //��u��ÿһ����
    int v,son=0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            /*//��
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    if ( Low[u] == Dfn[u] ){//u�����ϵĵ���ͬһ��������
        Represent[Belong2BiCC[u] = ++BiCCCnt] = u;
        do{
            Belong2BiCC[v=Stack[--StackTop]] = BiCCCnt;
            if ( v < Represent[BiCCCnt] ) Represent[BiCCCnt] = v;
        }while( v != u );
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(Belong2BiCC,Belong2BiCC+vn+1,0);
    fill(IsVisited,IsVisited+ECnt,false);
    //fill(IsBridge,IsBridge+ECnt,false);
    BiCCCnt = StackTop = 0;

    TimeStamp = 0;

    for(int i=1;i<=vn;++i)if ( 0 == Dfn[i] )dfs(i,i);
}

struct ufs_t{
    enum{UF_SIZE=SIZE};
    int father[UF_SIZE+1];
    
    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

using vi = vector<int>;
int N, M, Q;
vi G[SIZE];

struct problem_t{
	int u,v,x,y;
}Problem[SIZE];

using map_t = unordered_map<int, int>;
map_t LCAData[SIZE];
bool Flag[SIZE];
int Depth[SIZE];

void LCA(){
	UF.init(BiCCCnt);    
	
	function<void (int, int)> _dfs = [&](int u, int p)->void{
		Depth[u] = Depth[p] + 1;
        Flag[UF.father[u] = u] = true;
		for(auto son: G[u]){
            if(son == p) continue;
			_dfs(son, u);
			UF.father[son] = u;
		}

		for(auto & p: LCAData[u]){
			if(!Flag[p.first]) continue;
			
			p.second = UF.find(p.first);
			LCAData[p.first][u] = p.second;
		}
	};

	_dfs(1, 0);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    initGraph(N = getInt()); M = getInt();
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		mkEdge(a, b);
	}

	Tarjan(N); // ��˫
	/// �����������еı�
	UF.init(BiCCCnt);
    for(int a,b,i=2;i<ECnt;i+=2){
        a = Edge[i].from; b = Edge[i].to;
		if((a=Belong2BiCC[a]) == (b=Belong2BiCC[b])) continue;
		/// ��a�鵽b���Ѿ�������
		if(UF.find(a) == UF.find(b)) continue;
	    /// ��a��b����
		G[a].push_back(b); G[b].push_back(a);
		UF.unite(a, b);
	}
	/// ��������
	Q = getInt();
	for(int u,v,x,y,q=1;q<=Q;++q){
        Problem[q].u = u = Belong2BiCC[getInt()];
		Problem[q].v = v = Belong2BiCC[getInt()];
		Problem[q].x = x = Belong2BiCC[getInt()];
		Problem[q].y = y = Belong2BiCC[getInt()];
		/// ��Ҫ��ȡ���LCA
        if(u != x){
			LCAData[u].insert({x, 0});
			LCAData[x].insert({u, 0});
		}
		if(u != y){
			LCAData[u].insert({y, 0});
			LCAData[y].insert({u, 0});
		}
        if(v != x){
			LCAData[v].insert({x, 0});
			LCAData[x].insert({v, 0});
		}
		if(v != y){
			LCAData[v].insert({y, 0});
			LCAData[y].insert({v, 0});
		}	
		if(u != v){
			LCAData[u].insert({v, 0});
			LCAData[v].insert({u, 0});
		}	
		if(x != y){
			LCAData[x].insert({y, 0});
			LCAData[y].insert({x, 0});
		}
	}

	/// ��һ��LCA
	LCA();

	auto dist = [](int a, int b)->int{
		if(a == b) return 0;
        auto it = LCAData[a].find(b);
		assert(it != LCAData[a].end());
		return Depth[a] - Depth[it->second] + Depth[b] - Depth[it->second];
	};

	/// ������
	for(int u,v,x,y,q=1;q<=Q;++q){
        u = Problem[q].u;  v = Problem[q].v; 
		x = Problem[q].x;  y = Problem[q].y;
        /// uv��lca
		int uv = dist(u, v), xy = dist(x, y);
		int ux = dist(u, x), vy = dist(v, y);
		int uy = dist(u, y), vx = dist(v, x);
		int ans = min(ux + vy, uy + vx);
		ans -= uv + xy;
		if(ans < 0) ans = 0;
		printf("%d\n", ans>>1);
	}
    return 0;
}