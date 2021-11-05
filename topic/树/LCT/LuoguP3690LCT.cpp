/**
0 x y 代表询问从 xx 到 yy 的路径上的点的权值的xor 和。保证 xx 到 yy 是联通的。
1 x y 代表连接 xx 到 yy，若 xx 到 yy 已经联通则无需连接。
2 x y 代表删除边 (x,y)，不保证边 (x,y) 存在。
3 x y 代表将点 xx 上的权值变成 yy。
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
    int size;      //splay子树的节点数量，即路径信息
    value_t value; //点权
    value_t sum;   //splay树的和，即路径和
    unsigned char flip;//第1位表示设置延迟，第0位表示翻转延迟
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].sum = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].sum ^= Node[son].sum;
    }
    if(son=Node[t].son[RIGHT]){
        Node[t].size += Node[son].size;
        Node[t].sum ^= Node[son].sum;
    }
}

inline void _pushDown(int t){
    if ( t && (Node[t].flip & 1) ){//首先处理翻转
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].flip ^= 1;
        if(son = Node[t].son[RIGHT]) Node[son].flip ^= 1;

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
    _splay(x);//以前没有splay，于是TLE
    return x;
}
//令child是parent的子节点
inline void link(int parent,int child){
    _makeRoot(child);
    Node[child].parent = parent;
}

inline bool isConnect(int x,int y){
    return _getRoot(x) == _getRoot(y);
}
//单点设置
void modifyS(int x,value_t newValue){
    _access(x);
    _splay(x);

    Node[x].sum ^= newValue ^ Node[x].value;
    Node[x].value = newValue;
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
    toUsed = 0;
    for(int i=1;i<=n;++i){
        Node[i].value = Node[i].sum = getUnsigned();
        Node[i].size = 1;
    }
    int tmp;
    while(m--){
        int cmd = getUnsigned();
        int x = getUnsigned();
        int y = getUnsigned();
        switch(cmd){
            case 0:printf("%d\n",sumPath(x,y));break;
            case 1:if(!isConnect(x,y))link(x,y);break;
            case 2:if(isConnect(x,y)){
                _makeRoot(x);
                _access(y);
                _splay(y);
                //如果路径长度为2说明x和y直接相连
                if(Node[y].size==2)Node[y].son[LEFT] = Node[x].parent = 0,_pushUp(y);
            }break;
            case 3:modifyS(x,y);break;
            default:throw runtime_error("wrong cmd");
        }
        //dispLCT(stdout,n);
    }
    return 0;
}
bool TmpFlag[SIZE];
void _dispNodeIter(FILE*fp,int t){
    _pushDown(t);//输出之前还是要pushDown
    if(Node[t].son[LEFT]) _dispNodeIter(fp,Node[t].son[LEFT]);
    TmpFlag[t] = true;
    fprintf(fp,"%d value:%d, sum:%d\n",t,Node[t].value,Node[t].sum);
    //fprintf(fp,"           total_siz:%d, i_siz:%d\n",Node[t].total_size,Node[t].i_size);
    if(Node[t].son[RIGHT]) _dispNodeIter(fp,Node[t].son[RIGHT]);
}
void dispNode(FILE*fp,int t){
    _maintain(t);
    //首先找到t的splay根节点
    int root = t;
    while(!_isRoot(root)) root = Node[root].parent;
    //对root做一个中序输出
    fprintf(fp,"splay: %d, path_parent: %d\n",root,Node[root].parent);
    _dispNodeIter(fp,root);
}
//一共n个节点
void dispLCT(FILE*fp, int n){
    fill(TmpFlag,TmpFlag+n+1,false);
    fprintf(fp,"LCT:\n");
    for(int i=1;i<=n;++i)if(!TmpFlag[i]){
        dispNode(fp, i);
    }
}
