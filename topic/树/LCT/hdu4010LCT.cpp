/**
  1 x y：连接x和y
  2 x y：把y从x树上断开
  3 w x y：xy路径增加w
  4 x y：xy路径最大值
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 301000;

typedef int value_t;

int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    value_t value; //点权
    value_t peak;  //splay子树的最大值，记录路径最大值
    value_t lazyd;
    unsigned char flip;//第0位表示翻转延迟
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].peak = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].peak = max(Node[t].peak,Node[son].peak);
    }

    if(son = Node[t].son[RIGHT]){
        Node[t].peak = max(Node[t].peak,Node[son].peak);
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
    if ( t && Node[t].lazyd ){//最后处理delta的
        value_t& lazy = Node[t].lazyd;

        int son = Node[t].son[LEFT];
        if(son){
            Node[son].value += lazy;
            Node[son].lazyd += lazy;
            Node[son].peak += lazy;
        }

        if(son = Node[t].son[RIGHT]){
            Node[son].value += lazy;
            Node[son].lazyd += lazy;
            Node[son].peak += lazy;
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
//路径增加
void modifyD(int x,int y,value_t delta){
    _makeRoot(x);
    _access(y);
    _splay(y);

    Node[y].value += delta;
    Node[y].peak += delta;
    Node[y].lazyd += delta;
}
//路径查询极大值
value_t maxPath(int x,int y){
    _makeRoot(x);
    _access(y);
    _splay(y);
    return Node[y].peak;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
void dispLCT(FILE*fp, int n);
int main(){
    //freopen("1.txt","r",stdin);
    int n,q,cmd,x,y,xx;
    while(EOF!=scanf("%d",&n)){
        memset(Node,0,(n+1)*sizeof(node_t));
        for(int i=1;i<n;++i)link(getUnsigned(),getUnsigned());
        for(int i=1;i<=n;++i)Node[i].peak = Node[i].value = getUnsigned();
        //答问题
        q = getUnsigned();
        while(q--){
            cmd = getUnsigned();
            x = getUnsigned();
            switch(cmd){
                case 1:if(isConnect(x,y=getUnsigned()))printf("-1\n");else link(x,y);break;
                case 2:if(x==(y=getUnsigned())||!isConnect(x,y))printf("-1\n");else cut(x,y);break;
                case 3:if(!isConnect(xx=getUnsigned(),y=getUnsigned()))printf("-1\n");else modifyD(xx,y,x);break;
                case 4:if(!isConnect(x,y=getUnsigned()))printf("-1\n");else printf("%d\n",maxPath(x,y));break;
                default:throw runtime_error("wrong cmd");
            }
        }
        printf("\n");
    }
    return 0;
}
