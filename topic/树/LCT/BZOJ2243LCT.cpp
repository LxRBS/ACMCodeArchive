/**
  1 a b c：将路径ab全部染色成c
  2 a b：路径ab连续颜色的段数
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
    value_t value; //点权
    int left,right,cnt;//左边界右边界段数
    value_t lazys;
    unsigned char flip;//第1位表示设置延迟，第0位表示翻转延迟
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].left = Node[t].right = Node[t].value;
    Node[t].cnt = 1;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].cnt += Node[son].cnt - (Node[son].right==Node[t].left?1:0);
        Node[t].left = Node[son].left;
    }

    if(son = Node[t].son[RIGHT]){
        Node[t].cnt += Node[son].cnt - (Node[son].left==Node[t].right?1:0);
        Node[t].right = Node[son].right;
    }
}

inline void _pushDown(int t){
    if ( t && (Node[t].flip & 1) ){//首先处理翻转
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].flip ^= 1,swap(Node[son].left,Node[son].right);

        son = Node[t].son[RIGHT];
        if(son) Node[son].flip ^= 1,swap(Node[son].left,Node[son].right);

        Node[t].flip ^= 1;
    }
    if ( t && (Node[t].flip & 2) ){//再处理set
        value_t& lazy = Node[t].lazys;

        int son = Node[t].son[LEFT];
        if(son){
            Node[son].left = Node[son].right = Node[son].value = Node[son].lazys = lazy;
            Node[son].cnt = 1;
            Node[son].flip |= 2;
        }

        if(son = Node[t].son[RIGHT]){
            Node[son].left = Node[son].right = Node[son].value = Node[son].lazys = lazy;
            Node[son].cnt = 1;
            Node[son].flip |= 2;
        }

        Node[t].flip ^= 2;//清除set标记
        lazy = 0; //这一步无所谓
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
    swap(Node[x].left,Node[x].right);//左右边界要交换
}

//令child是parent的子节点
inline void link(int parent,int child){
    _makeRoot(child);
    Node[child].parent = parent;
}

//路径设置
void modifyS(int x,int y,value_t newValue){
    _makeRoot(x);
    _access(y);
    _splay(y);

    Node[y].value = Node[y].lazys = Node[y].left = Node[y].right = newValue;
    Node[y].cnt = 1;
    Node[y].flip |= 2;
}
//路径查询
int sumPath(int x,int y){
    _makeRoot(x);
    _access(y);
    _splay(y);
    return Node[y].cnt;
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
    int n = getUnsigned();
    int m = getUnsigned();
    for(int i=1;i<=n;++i){
        Node[i].value = Node[i].left = Node[i].right = getUnsigned();
        Node[i].cnt = 1;
    }
    for(int i=1;i<n;++i)link(getUnsigned(),getUnsigned());
    //答问题
    int a,b;char cmd[3];
    while(m--){
        scanf("%s",cmd);
        a = getUnsigned();
        b = getUnsigned();

        if('C'==*cmd){
            modifyS(a,b,getUnsigned());
        }else{
            printf("%d\n",sumPath(a,b));
        }
    }
    return 0;
}
