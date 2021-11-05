/*
    无向图求割点的数量，模板题
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
/*
//用于检查重边
struct hash_t{
    typedef pair<int,int> key_t;
    enum{MOD=0x1FFFFF};

    key_t keys[MOD+1];
    //value_t values[MOD+1];

    int head[MOD+1];
    int next[MOD+1];

    int toUsed;

    hash_t():toUsed(0){fill(head,head+MOD+1,-1);}

    void clear(){toUsed=0;fill(head,head+MOD+1,-1);}

    void insert(key_t const&key){
        int k = (key.first*31+key.second) & MOD;
        keys[toUsed] = key;
        next[toUsed] = head[k];
        head[k] = toUsed++;
    }

    bool find(key_t const&key)const{
        int k = (key.first*31+key.second) & MOD;
        for(int i=head[k];i!=-1;i=next[i]){
            if ( keys[i] == key ){
                return true;
            }
        }
        return false;
    }
}Hash;
//*/

int const SIZE_OF_VERTICES = 10010;
int const SIZE_OF_EDGES = 120010;

struct edge_t{
    int from,to;
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

inline void initGraph(int n){
    ECnt = 2;
    fill(Vertex,Vertex+n+1,0);
}

//双向边
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int TimeStamp;
int Dfn[SIZE_OF_VERTICES],Low[SIZE_OF_VERTICES];
//int AddBlocks[SIZE_OF_VERTICES];//ABi表示删除i点之后多出来的块数
bool IsBridge[SIZE_OF_EDGES];//边i是否为桥
//bool IsCut[SIZE_OF_VERTICES];//点i是否为割点
int BridgeCnt;//桥的数量

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    int v,son = 0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( (v=Edge[next].to) != pre ){
        if ( 0 == Dfn[v] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            //*
            //桥
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
                ++BridgeCnt;
            }
            //*/

            /*
            //符合割点的条件2
            if ( u != pre && Dfn[u] <= Low[v] ){
                IsCut[u] = true;
                //++AddBlocks[u];
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //符合割点的条件1
    //if ( u == pre && son > 1 ) IsCut[u] = true;
    //if ( u == pre ) AddBlocks[u] = son - 1;
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    //fill(AddBlocks,AddBlocks+vn+1,0);
    //fill(IsCut,IsCut+vn+1,false);
    fill(IsBridge,IsBridge+ECnt,false);
    TimeStamp = BridgeCnt = 0;

    for(int i=1;i<=vn;++i)if(0==Dfn[i])dfs(i,i);
}

int N;
bool read(){
    if ( scanf("%d",&N) == EOF ) return false;

    initGraph(N);
    int a,b,m;
    for(int i=0;i<N;++i){
        scanf("%d (%d)",&a,&m);
        ++a;

        for(int j=0;j<m;++j){
            scanf("%d",&b);
            mkEdge(a,++b);
        }
    }
    return true;

}

pair<int,int> Ans[SIZE_OF_VERTICES];
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        Tarjan(N);

        int ans = 0;
        for(int i=2;i<ECnt;i+=2)if(IsBridge[i]){
            Ans[ans].first = Edge[i].from-1;
            Ans[ans].second = Edge[i].to-1;
            if ( Ans[ans].first > Ans[ans].second ) swap(Ans[ans].first,Ans[ans].second);
            ++ans;
        }
        sort(Ans,Ans+ans);

        printf("%d critical links\n",ans);
        for(int i=0;i<ans;++i) printf("%d - %d\n",Ans[i].first,Ans[i].second);
        printf("\n");
    }
    return 0;
}
