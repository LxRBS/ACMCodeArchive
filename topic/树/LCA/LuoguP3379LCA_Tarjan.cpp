/**
    LCA模板题
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

//just as its names
int const SIZE_OF_VERTICES = 500005;
int const SIZE_OF_EDGES = SIZE_OF_VERTICES<<1;

struct edge_t{
	int from,to;
	//weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
	edge_t(int a=0,int b=0,int c=0):from(a),to(b),next(c){}
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
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

struct ufs_t{
    enum{UF_SIZE=SIZE_OF_VERTICES};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

bool operator == (edge_t const&lhs,edge_t const&rhs){
    return lhs.from == rhs.from && lhs.to == rhs.to;
}

struct hash_t{
    typedef edge_t key_t;
    typedef int value_t;
    enum{MOD=0x1FFFFF};

    key_t keys[MOD+1];
    value_t values[MOD+1];

    int head[MOD+1];
    int next[MOD+1];

    int toUsed;

    hash_t():toUsed(0){fill(head,head+MOD+1,-1);}

    void clear(){toUsed=0;fill(head,head+MOD+1,-1);}

    void insert(key_t const&key,value_t const&value){
        int k = _key(key) & MOD;
        keys[toUsed] = key;
        values[toUsed] = value;
        next[toUsed] = head[k];
        head[k] = toUsed++;
    }

    value_t find(key_t const&key)const{
        int k = _key(key) & MOD;
        for(int i=head[k];i!=-1;i=next[i]){
            if ( keys[i] == key ) return values[i];
        }
        return -1;
    }

    value_t& operator [] (key_t const&key){
        int k = _key(key) & MOD;
        for(int i=head[k];i!=-1;i=next[i]){
            if ( keys[i] == key ) return values[i];
        }

        keys[toUsed] = key;
        values[toUsed] = 0;//本来没有key就插入一个默认值
        next[toUsed] = head[k];
        head[k] = toUsed++;
        return values[toUsed-1];
    }

    int _key(key_t const&key)const{
        return key.from*31+key.to;
    }
}Hash;

bool Flag[SIZE_OF_VERTICES];
vector<int> Question[SIZE_OF_VERTICES];

void dfs(int u,int parent){
    Flag[UF.father[u] = u] = true;
    //对u的每一个儿子
    int v;
    for(int p=Vertex[u];p;p=Edge[p].next)if((v=Edge[p].to)!=parent){
        dfs(v,u);
        UF.father[v] = u;
    }
    //对每一个跟u有关的问题
    vector<int>const& vec = Question[u];
    for(vector<int>::const_iterator it=vec.begin();it!=vec.end();++it){
        if(Flag[v = *it]){
            int ans = UF.find(v);
            //总是把小数放在前面
            int a = min(u, v);
            int b = max(u, v);
            Hash[edge_t(a,b)] = ans;
        }
    }
}

void Tarjan(int root,int n){
    UF.init(n);//初始化并查集
    Hash.clear();//初始化散列表
    fill(Flag,Flag+n+1,false);//是否搜索过

    dfs(root,0);//答案保存在Hash中
}

int N,M,S;
edge_t RawProblem[SIZE_OF_VERTICES];
int main(){
    //freopen("1.txt","r",stdin);
    initGraph(N = getUnsigned());
    for(int i=0;i<=N;++i)Question[i].clear();

    M = getUnsigned();
    S = getUnsigned();
    //读入树的结构
    for(int i=1;i<N;++i){
        int a = getUnsigned();
        mkEdge(a, getUnsigned());
    }
    //读入题目
    for(int i=0;i<M;++i){
        int a = getUnsigned();
        int b = getUnsigned();
        if(a>b)swap(a,b);
        RawProblem[i] = edge_t(a,b);
        Question[a].push_back(b);
        Question[b].push_back(a);
    }

    Tarjan(S, N);

    //回答题目
    for(int i=0;i<M;++i){
        printf("%d\n", Hash.find(RawProblem[i]));
    }
    return 0;
}

