/**
  Q C：查询C的权值
  I C1 C2 K：路径增加K
  D C1 C2 K：路径减少K
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 201000;

typedef int value_t;
typedef long long int llt;

int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    value_t value; //点权
    value_t lazyd;
    unsigned char flip;//第1位表示设置延迟，第0位表示翻转延迟
}Node[SIZE];
int toUsed = 0;

inline int _newNode(value_t value=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    Node[toUsed].value = value;
    return toUsed;
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
    if ( t && Node[t].lazyd ){//最后处理delta的
        value_t& lazy = Node[t].lazyd;

        int son = Node[t].son[LEFT];
        if(son){
            Node[son].value += lazy;
            Node[son].lazyd += lazy;
        }

        if(son = Node[t].son[RIGHT]){
            Node[son].value += lazy;
            Node[son].lazyd += lazy;
        }

        lazy = 0;
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
}

//从根到x形成一条链，返回
int _access(int x){
    int t = 0;
    for(;x;x=Node[t=x].parent){
        _splay(x);
        Node[x].son[RIGHT] = t;//将链接上
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
}
//在root做树根的情况下，x和y的最近公共祖先
inline int lca(int root,int x,int y){
    _makeRoot(root);
    _access(x);
    return _access(y);
}
inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
}
//路径增加
void modifyD(int x,int y,value_t delta){
    _makeRoot(x);
    _access(y);
    _splay(y);

    Node[y].value += delta;
    Node[y].lazyd += delta;
}
//单点查询权值
value_t maxPath(int y){
    _access(y);
    _splay(y);
    return Node[y].value;
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
void dispLCT(FILE*fp, int n);
int main(){
    //freopen("1.txt","r",stdin);
    int n,m,p,a,b,w;char cmd[3];
    while(EOF!=scanf("%d%d%d",&n,&m,&p)){
        memset(Node,0,(n+1)*sizeof(node_t));
        for(int i=1;i<=n;++i)Node[i].value = getInt();
        for(int i=1;i<n;++i)link(getInt(),getInt());
        //答问题
        while(p--){
            scanf("%s",cmd);
            if('Q'==*cmd){
                printf("%d\n",maxPath(getInt()));
            }else{
                a = getInt();b = getInt();w = getInt();
                modifyD(a,b,'I'==*cmd?w:-w);
            }
        }
    }
    return 0;
}
