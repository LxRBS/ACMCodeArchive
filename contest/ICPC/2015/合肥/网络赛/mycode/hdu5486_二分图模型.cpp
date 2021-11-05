/**
  给定N(100万)个实体，用两种聚类方法分别给出两种集合的划分
  问两种划分中split、merge和1:1的数量各多少个。
  例如一共有1、2、3、4的四个实体
  第一种聚类为{1,2,3,4}，第二种聚类为{1}{2}{3}{4}
  这就称为split
  如果是反过来则称为merge
  如果第一种为{1,2}{3,4},第二种也是，则称为1:1
  还有一种可能，{1,2}{3,4}和{1,3}{2,4}，这种情况不用统计
  注意实体的编号是不变的，但是两种聚类的编号是不一定一致的

  首先去重，然后将前后聚类映射成一个二分图。计算度数即可。
  计算Merge的时候要防止重复计算。
*/
#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

//just as its names
int const SIZE_OF_VERTICES = 1000100;
int const SIZE_OF_EDGES = 1000100<<1;

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

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

struct _t{
    int c1,c2;
}T[1000100];

bool operator < (_t const&lhs,_t const&rhs){
    return lhs.c1<rhs.c1||(lhs.c1==rhs.c1&&lhs.c2<rhs.c2);
}

bool operator == (_t const&lhs,_t const&rhs){
    return lhs.c1 == rhs.c1 && lhs.c2 == rhs.c2;
}

//将题目给定的聚类编号映射成出现的顺序
map<int,int> A2ID,B2ID;
typedef map<int,int>::iterator iit;

int Deg[2000100];
int Split,Merge,OneOne;
bool Flag[2000100];

//判断是否为split
bool isSplit(int u){
    if(Deg[u]<=1) return false;

    //对u的每一个邻点
    for(int p=Vertex[u];p;p=Edge[p].next){
        int v = Edge[p].to;
        if(Deg[v]!=1) return false;
    }

    return true;
}

//判断是否为合并
bool isMerge(int u){
    if(Deg[u]!=1) return false;

    //判断u的邻点的所有邻点
    int v = Edge[Vertex[u]].to;
    if(Deg[v]<=1) return false;

    for(int p=Vertex[v];p;p=Edge[p].next){
        int vv = Edge[p].to;
        if(1!=Deg[vv]) return false;
    }

    //在返回之前要把v的所有邻点都设置为真，以后不要再处理
    for(int p=Vertex[v];p;p=Edge[p].next){
        int vv = Edge[p].to;
        Flag[vv] = true;
    }
    return true;
}

//判断是否为1对1
bool isOneOne(int u){
    if(Deg[u]!=1) return false;
    int v = Edge[Vertex[u]].to;
    return 1==Deg[v];
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        int n = getInt();

        for(int i=0;i<n;++i){
            T[i].c1 = getInt();
            T[i].c2 = getInt();
        }

        //预处理
        sort(T,T+n);
        n = unique(T,T+n) - T;

        A2ID.clear();
        B2ID.clear();
        initGraph(n<<1);
        fill(Deg,Deg+n+n+1,0);
        fill(Flag,Flag+n+n+1,false);

        int c1,c2;
        iit ait,bit;

        int ak = 0, bk = 0;
        int au,bu;
        for(int i=0;i<n;++i){
            if(A2ID.end()==(ait=A2ID.find(c1=T[i].c1))){//还没有出现过
                A2ID.insert(make_pair(c1,au=++ak));
            }else{
                au = ait->second;
            }
            if(B2ID.end()==(bit=B2ID.find(c2=T[i].c2))){
                B2ID.insert(make_pair(c2,bu=++bk));
            }else{
                bu = bit->second;
            }
            //有一条边
            mkEdge(au,bu+n);
            ++Deg[au];
            ++Deg[bu+n];
        }

        //对A中的每一个点
        Split = Merge = OneOne = 0;
        for(int i=1;i<=ak;++i)if(!Flag[i]){
            if(isSplit(i)) ++Split;
            else if(isOneOne(i)) ++OneOne;
            else if(isMerge(i)) ++Merge;
        }
        /*
        //对B中的每一个点
        for(int i=n+1;i<=n+bk;++i){
            if(isSplit(i)) ++Merge;
        }//*/

        printf("Case #%d: %d %d %d\n",kase,Split,Merge,OneOne);
    }
    return 0;
}

