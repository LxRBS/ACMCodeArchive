/**
  若干个盒子套盒子
  MOVE x y：将x盒子移动到y盒子里面，如果y为0，则将x盒子放到地上
  QUERY x：问x盒子的根
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 201000;

typedef int value_t;


int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    unsigned char flip;//第1位表示设置延迟，第0位表示翻转延迟
}Node[SIZE];
int toUsed = 0;

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

void _splay(int t){
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
//在root做树根的情况下，x和y的最近公共祖先
inline int lca(int root,int x,int y){
    _makeRoot(root);
    _access(x);
    return _access(y);
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

inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
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
    int n,m,x,y,root;char cmd[14];
    bool flag = false;
    while(EOF!=scanf("%d",&n)){
        flag?putchar('\n'):flag=true;

        root = n+1;//设置一个虚拟的根节点，保持不变
        memset(Node,0,(n+2)*sizeof(node_t));
        for(int i=1;i<=n;++i)x=getUnsigned(),link(x?x:root,i);
        //答问题
        m = getUnsigned();
        while(m--){
            scanf("%s",cmd);
            if('M'==*cmd){
                x = getUnsigned();
                y = getUnsigned();
                //把x接到y上面，如果非法则不操作
                if(lca(root,x,y)==x)continue;
                cut(root,x);link(y?y:root,x);
            }else{//找根，但不是root
                int tmp = _getRoot(getUnsigned());
                _splay(tmp);
                //在右子树里找最小的
                tmp = Node[tmp].son[RIGHT];
                while(Node[tmp].son[LEFT]) tmp = Node[tmp].son[LEFT];
                printf("%d\n",tmp);
            }
        }
    }
    return 0;
}
