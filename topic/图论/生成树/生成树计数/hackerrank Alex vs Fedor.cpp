/*
    输出MST的数量与生成树总数的比
*/
#include <cstdio>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct ufs_t{
    enum {SIZE=110};
    int father[SIZE];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return x==father[x]?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(x)]=find(y);}
};

int const SIZE_OF_COLUMNS = 110;

typedef long long llt;

//a is the determinant to be calculated which will be changed during calculation
//n is n, the valid index is from 0 to n-1
llt determinant(llt (*a)[SIZE_OF_COLUMNS],int const n){
    llt ret = 1;

    for(int i=0;i<n;++i){
    	for(int j=i+1;j<n;++j){
    		while( a[j][i] ){
    			llt t = a[i][i] / a[j][i];
    			for(int k=i;k<n;++k){
    				a[i][k] = ( a[i][k] - t * a[j][k] );
				}
				for(int k=i;k<n;++k) swap(a[i][k],a[j][k]);
				ret = -ret;
			}
		}

		if ( 0 == a[i][i] ) return 0;

		ret = ret * a[i][i];
	}

    return ret;
}

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 2100;

struct edge_t{
	int from,to;
	weight_t weight;
}Edge[SIZE_OF_EDGES];
int ECnt;

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 1;
}

inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt++].weight = w;
}

bool operator < (edge_t const&lhs,edge_t const&rhs){
    return lhs.weight < rhs.weight || ( lhs.weight == rhs.weight && lhs.from < rhs.from )
        || ( lhs.weight == rhs.weight && lhs.from == rhs.from && lhs.to < rhs.to );
}

int Map[SIZE_OF_VERTICES];
llt G[SIZE_OF_COLUMNS][SIZE_OF_COLUMNS];

//calculate the count of MST
llt Kruskal(int vn,int en,ufs_t&uf){
    uf.init(vn);
    sort(Edge+1,Edge+en+1);

    int totalCnt = 1;

    llt ret = 1;
    int k = 1;
    while( k <= en ){
        int t = 0;
        int kk = 0;
        int cnt = 0;
        int ff = 0;
        int ft = 0;
        bool flag = false;

        fill(Map,Map+vn+1,-1);
        memset(G,0,sizeof(G));

        while(  ( kk = (t++) + k ) <= en && Edge[k].weight == Edge[kk].weight ){
            if ( ( ff = uf.find(Edge[kk].from) ) == ( ft = uf.find(Edge[kk].to) ) ) continue;

            if ( -1 == Map[ff] ) Map[ff] = cnt ++;
            if ( -1 == Map[ft] ) Map[ft] = cnt ++;

            ++G[Map[ff]][Map[ff]];
            ++G[Map[ft]][Map[ft]];
            --G[Map[ff]][Map[ft]];
            --G[Map[ft]][Map[ff]];
        }

        //if ( cnt > 1 ) ret = ret * determinant(G,cnt-1,MOD) % MOD;
        vector<int> vi;
        for(;k<kk;++k){
            if ( uf.find(Edge[k].from) == uf.find(Edge[k].to) ) continue;

            vi.push_back(Edge[k].from);
            vi.push_back(Edge[k].to);

            uf.unite(Edge[k].from,Edge[k].to);
            ++totalCnt;
            if ( vn == totalCnt ) {
                flag = true;
                break;
            }
        }

        if ( vi.empty() ) continue;

        set<int> s;
        for(vector<int>::iterator it=vi.begin();it!=vi.end();++it){
            s.insert(uf.find(*it));
        }

        int prev = Map[*s.begin()];
        for(set<int>::iterator it=++s.begin();it!=s.end();++it){
            int cur = Map[*it];
            ++G[prev][prev];
            ++G[cur][cur];
            --G[prev][cur];
            --G[cur][prev];
            prev = cur;
        }

        if ( cnt > 1 ) ret = ret * determinant(G,cnt-1);

        if ( flag ) break;
    }

    return vn == totalCnt ? ret : 0;
}

int N,M;

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N);
    memset(G,0,sizeof(G));
    for(int i=0;i<M;++i){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        mkEdge(a,b,c);
        ++G[a-1][a-1];
        ++G[b-1][b-1];
        --G[a-1][b-1];
        --G[b-1][a-1];
    }

    return true;
}

//iteration implementation
llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

ufs_t UF;
void proc(){
    //calculate the count of spanning trees
    llt total = determinant(G,N-1);

    llt mst = Kruskal(N,M,UF);

    llt g = gcd(mst,total);
    mst /= g;
    total /= g;

    printf("%lld/%lld\n",mst,total);
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) proc();
    return 0;
}

