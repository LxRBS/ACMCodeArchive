/**
   给定一个无向图，两类操作：
   1: 将u的点权改为x
   2: 查询u的mex函数值
   点数和边数均为10万
   将节点按照度数分为大节点和小节点，然后分别进行操作
   大节点的1操作：for每一个大邻居，修改其树状数组
   小节点的1操作：for每一个大邻居，修改其树状数组
   大节点的2操作：树状数组统计结果
   小节点的2操作：暴力
   注意树状数组只保存不超过度数的值
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long int llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//just as its names
int const SIZE_OF_VERTICES = 100010;
int const SIZE_OF_EDGES = 100010<<1;

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

int W[SIZE_OF_VERTICES];
int Deg[SIZE_OF_VERTICES];
vector<int> C[SIZE_OF_VERTICES];
vector<int> G[SIZE_OF_VERTICES];
vector<int> T[SIZE_OF_VERTICES];
int const LIMIT = 300;

//计算x的二进制位的最低位1代表的数值
int lowbit(int x){
    return x & ( x ^ ( x - 1 ) );
}

//查询C[idx]中的前x项之和
int query(int x,int idx){
    vector<int>const&v=C[idx];
    int s = 0;
    while(x>0) s+=v[x],x-=lowbit(x);
    return s;
}
//将C[idx]上的第idx项加delta
void modify(int x,int delta,int idx){
    vector<int>&v=C[idx];
    int n = v.size()-1;
    while(x<=n)v[x]+=delta,x+=lowbit(x);
}

//查询u的mex函数值
int query(int u){
    int deg = Deg[u];
    if(deg<LIMIT){//小节点，暴力
        bool flag[deg+1] = {false};
        for(int tmp,p=Vertex[u];p;p=Edge[p].next){
            if((tmp=W[Edge[p].to])<=deg){
                flag[tmp] = true;
            }
        }
        int k = 1;
        while(k<=deg && flag[k]) ++k;
        return k;
    }

    //使用树状数组
    vector<int> const&v = C[u];
    int mid, left = 1, right = v.size()-1;
    do{//二分搜索，搜索最早的序号x，使得x-sum(x)>=1
        mid = (left+right)>>1;
        if(mid-query(mid,u)>=1) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);

    return left;
}

//将v的权值从origin修改成newValue
//保证uv右边，且u是大节点
//该操作需要修改u的树状数组
void change(int u,int v,int origin,int newValue){
    if(origin){//origin为0表示是初始化操作，不为0则是后续的修改操作
        if(origin<=Deg[u]){
            if(0==--T[u][origin]){
                modify(origin,-1,u);
            }
        }
    }
    if(newValue<=Deg[u]){
        if(1==++T[u][newValue]){
            modify(newValue,+1,u);
        }
    }
}
//将u节点的权值修改为newValue
void change(int u,int newValue){
    vector<int>const& v = G[u];
    //for每一个大邻居，修改其树状数组
    for(vector<int>::const_iterator it=v.begin();it!=v.end();++it){
        change(*it,u,W[u],newValue);
    }
    W[u] = newValue;
}
int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int a,b,n,m,nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        initGraph(n = getUnsigned());
        m = getUnsigned();

        fill(Deg,Deg+n+1,0);
        for(int i=1;i<=n;++i){
            W[i]=getUnsigned() + 1;
            C[i].clear();
            G[i].clear();
            T[i].clear();
        }
        for(int i=0;i<m;++i){
            ++Deg[a=getUnsigned()];
            ++Deg[b=getUnsigned()];
            mkEdge(a,b);
        }

        //统计大邻居
        for(int i=1;i<=n;++i){
            for(int to,p=Vertex[i];p;p=Edge[p].next){
                if(Deg[to=Edge[p].to]>=LIMIT){
                    G[i].push_back(to);
                }
            }
        }

        //对每一个大节点建树状数组
        for(int deg,i=1;i<=n;++i)if((deg=Deg[i])>=LIMIT){
            C[i].assign(deg+1,0);
            T[i].assign(deg+1,0);
            for(int p=Vertex[i];p;p=Edge[p].next){
                change(i,Edge[p].to,0,W[Edge[p].to]);
            }
        }

        int cmd,u,newValue,q = getUnsigned();
        for(int iq=1;iq<=q;++iq){
            switch(cmd=getUnsigned()){
            case 1:{
                u = getUnsigned();
                newValue = getUnsigned() + 1;
                change(u,newValue);
            }break;
            case 2:{
                u = getUnsigned();
                printf("%d\n",query(u)-1);
            }break;
            default:throw runtime_error("XXXXXX");
            }
        }
    }
    return 0;
}
