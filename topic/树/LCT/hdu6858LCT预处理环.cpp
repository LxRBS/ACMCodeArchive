/**
    给一个无向图，Q个询问
    问第a条边到第b条边之间的所有边能否选出一些构成一个环
    预处理每条边，对于第i条边，记录比它大的且离的最近的能构成环的边
    如果没有的话，记录为M+1即可
    预处理的时候使用尺取法，一遍循环即可解决，每次循环使用LCT
    然后对于每个询问O(1)可解决
    总时间复杂度是O(MlogN+Q)
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}


int const SIZE = 301000;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    int size;      //splay子树的节点数量，即路径信息
    unsigned char flip;//第1位表示设置延迟，第0位表示翻转延迟
}Node[SIZE];
int toUsed = 0;

inline int _newNode(){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //Node[toUsed].value = value;
    return toUsed;
}

inline void _pushUp(int t){
    Node[t].size = 1;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
    }

    if(son = Node[t].son[RIGHT]){
        Node[t].size += Node[son].size;
    }
}

inline void _pushDown(int t){
    if ( t && (Node[t].flip & 1) ){//首先处理翻转
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].flip ^= 1;

        son = Node[t].son[RIGHT];
        if(son) Node[son].flip ^= 1;

        Node[t].flip ^= 1;
    }
}
//判断t是否为本splay的根
inline bool _isRoot(int t){
    int p = Node[t].parent;
    return 0==p || (Node[p].son[LEFT]!=t&&Node[p].son[RIGHT]!=t);
}
//获取排行，不能用于树根
inline int _getSN(int t){
    return Node[Node[t].parent].son[RIGHT] == t;
}
inline void _link(int p,int sn,int t){
    Node[Node[t].parent=p].son[sn] = t;
}
inline void _rotate(int t){
    int p = Node[t].parent;//父节点
    int g = Node[p].parent;//祖父节点
    int sn = _getSN(t);
    int osn = sn^1;
    //不需要pushDown，在splay中pushDown

    _link(p,sn,Node[t].son[osn]);
    Node[t].parent = g;
    if(!_isRoot(p))Node[g].son[_getSN(p)]=t;
    _link(t,osn,p);

    _pushUp(p);
}
//从根开始逐级下放延迟标记
void _maintain(int t){
    if(!_isRoot(t)) _maintain(Node[t].parent);
    _pushDown(t);
}
void _splay(int t){
    _maintain(t);
    while(!_isRoot(t)){
        int p = Node[t].parent;
        if(!_isRoot(p)) _getSN(t)==_getSN(p)?_rotate(p):_rotate(t);
        _rotate(t);
    }
    _pushUp(t);
}

//从根到x形成一条链，返回
int _access(int x){
    int t = 0;
    for(;x;x=Node[t=x].parent){
        _splay(x);
        Node[x].son[RIGHT] = t;//将链接上
        _pushUp(x);
    }
    return t;
}
//令x成为原树的根
inline void _makeRoot(int x){
    _access(x);
    _splay(x);
    Node[x].flip ^= 1; //打翻转标记
}
//获取x所在树的根节点
int _getRoot(int x){
    _access(x);
    _splay(x);
    while( Node[x].son[LEFT] ) x = Node[x].son[LEFT];
    _splay(x);
    return x;
}
//令child是parent的子节点
inline void link(int parent,int child){
    _makeRoot(child);
    Node[child].parent = parent;
}
//将child从parent树上切下
inline void cut(int parent,int child){
    _makeRoot(parent);
    _access(child);
    _splay(child);
    Node[child].son[LEFT] = Node[Node[child].son[LEFT]].parent = 0;
    _pushUp(child);
}

inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
}

struct edge_t{
    int from,to;
}Edge[SIZE];

int N,M,Q;
//Right[i]表示比i大且与i处于同一个圈的最近边
int Right[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        Q = getUnsigned();
        for(int a,b,i=1;i<=M;++i){
            a = getUnsigned();
            b = getUnsigned();
            if(a>b)swap(a,b);
            Edge[i].from = a;
            Edge[i].to = b;
        }

        //预处理Right
        int k = 1, t = 1;
        while(t<=M){
            if(k<=M && !isConnect(Edge[k].from,Edge[k].to)){
                link(Edge[k].from,Edge[k].to);
                ++k;
            }else{//第k条边与前面的t边形成圈
                cut(Edge[t].from,Edge[t].to);
                Right[t++] = k;
            }
        }

        int lastans = 0;
        for(int a,b,i=1;i<=Q;++i){
            a = (getUnsigned()^lastans)%M+1;
            b = (getUnsigned()^lastans)%M+1;
            if(a>b) swap(a,b);
            puts((lastans=(b>=Right[a]))?"Yes":"No");
        }
    }
    return 0;
}
