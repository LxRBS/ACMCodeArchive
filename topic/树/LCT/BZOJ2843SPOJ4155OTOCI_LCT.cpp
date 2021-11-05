/**
  bridge A B:A、B之间连一条边，当A、B不连通时
  penguis A X：将A设置为X
  excursion A B：求A、B路径和，如果不连通输出impossible
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 201000;

typedef int value_t;
typedef int llt;

int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    value_t value; //点权
    llt sum;       //splay树的和，即路径和
    unsigned char flip;//第1位表示设置延迟，第0位表示翻转延迟
}Node[SIZE];
int toUsed = 0;

inline int _newNode(value_t value=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    Node[toUsed].value = value;
    return toUsed;
}

inline void _pushUp(int t){
    Node[t].sum = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].sum += Node[son].sum;
    }

    if(son = Node[t].son[RIGHT]){
        Node[t].sum += Node[son].sum;
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
//在root做树根的情况下，x和y的最近公共祖先
inline int lca(int root,int x,int y){
    _makeRoot(root);
    _access(x);
    return _access(y);
}
inline bool isConnect(int x,int y){
    return _getRoot(x) == _getRoot(y);
}
//路径设置
void modifyS(int y,value_t newValue){
    _access(y);
    _splay(y);

    Node[y].sum += newValue - Node[y].value;
    Node[y].value = newValue;
}

//路径查询和
value_t sumPath(int x,int y){
    _makeRoot(x);
    _access(y);
    _splay(y);
    return Node[y].sum;
}

int getUnsigned(){
	char ch = getchar();
	while( ch > '9' || ch < '0' ) ch = getchar();

	int ret = 0;
	do ret = ret * 10 + (int)(ch-'0');while( '0' <= (ch=getchar()) && ch <= '9' );
	return ret;
}
void dispLCT(FILE*fp, int n);
int main(){
    //freopen("1.txt","r",stdin);
    int n,q,a,b;char cmd[22];
    while(EOF!=scanf("%d",&n)){
        memset(Node,0,(n+1)*sizeof(node_t));

        for(int i=1;i<=n;++i){
            Node[i].value = Node[i].sum = getUnsigned();
        }

        q = getUnsigned();
        while(q--){
            scanf("%s",cmd);
            if('e'==*cmd){
                if(isConnect(a=getUnsigned(),b=getUnsigned()))printf("%d\n",sumPath(a,b));
                else printf("impossible\n");
            }else if('b'==*cmd){
                if(isConnect(a=getUnsigned(),b=getUnsigned()))printf("no\n");
                else printf("yes\n"),link(a,b);
            }else{
                a = getUnsigned();
                modifyS(a,getUnsigned());
            }
        }
    }
    return 0;
}
