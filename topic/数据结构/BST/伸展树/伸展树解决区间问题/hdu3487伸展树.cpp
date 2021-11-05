/**
    1~N的序列，两种操作
    CUT s e pos：将[s,e]移动到从pos之前开始，注意与模板的区别
    FLIP s e: 区间翻转
*/
#include <bits/stdc++.h>
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

typedef int value_t;

int const SIZE = 300100;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;//父节点
    int son[2];//子节点
    int sn;    //本节点的排行
    int size;  //size域
    value_t value; //值
    unsigned char flip;//第0位表示翻转的延迟标记
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
    }
    son = Node[t].son[RIGHT];
    if(son){
        Node[t].size += Node[son].size;
    }
}
inline void _pushDown(int t){
    if ( t && (Node[t].flip & 1) ){//首先处理翻转
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].sn = LEFT, Node[son].flip ^= 1;

        son = Node[t].son[RIGHT];
        if(son) Node[son].sn = RIGHT, Node[son].flip ^= 1;

        Node[t].flip ^= 1;
    }
}
//分配一个新节点
inline int _newNode(value_t value=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //其他域不用管，在各自函数中处理
    Node[toUsed].value = value;
    return toUsed;
}
//将parent的sn儿子设置为son
inline void _link(int parent,int sn,int son){
    Node[son].parent = parent;
    Node[son].sn = sn;
    Node[parent].son[sn] = son;
}
//旋转操作,t不能是树根
void _rotate(int t){
    int p = Node[t].parent;
    int sn = Node[t].sn;
    int osn = sn ^ 1;
    //如果保证splay紧跟kth调用，则不需要pushDown
    //重新确定三对父子关系
    _link(p,sn,Node[t].son[osn]);
    _link(Node[p].parent,Node[p].sn,t);
    _link(t,osn,p);
    //只维护p即可，t暂时不维护
    _pushUp(p);
}
//在root树中，将t伸展为p的儿子,p为0则伸展为树根
void _splay(int&root,int p,int t){
    int pp;
    while( (pp=Node[t].parent) != p ){
        if(Node[pp].parent!=p) Node[pp].sn==Node[t].sn?_rotate(pp):_rotate(t);
        _rotate(t);
    }
    _pushUp(t);//最后维护t
    if(0==p) root = t;//改根
}

//在t子树上查找第k个元素，从0开始，参数一定合法
int _kth(int t,int k){
    _pushDown(t);
    int son = Node[t].son[LEFT];
    int s = son?Node[son].size:0;
    if(k<s) return _kth(son,k);//去左子树找
    return s < k ? _kth(Node[t].son[RIGHT],k-s-1) : t;
}
//[s,e]区间进行翻转
void reverse(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int ttt = Node[tt].son[LEFT];
    Node[ttt].flip ^= 1;
}
//将[s,e]区间移动到从pos位置开始
void move(int&root ,int s,int e,int pos){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    Node[tt].son[LEFT] = 0;
    _pushUp(tt);_pushUp(root);

    t = _kth(root,pos-1);
    _splay(root,0,t);

    tt = _kth(root,pos);
    _splay(root,root,tt);

    _link(tt,LEFT,son);
    _pushUp(tt);_pushUp(root);
}

//利用全局数组建树
void build(int&t,int parent,int sn,int s,int e){
    int mid = ( s + e ) >> 1;

    t = _newNode(mid);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) build(Node[t].son[LEFT],t,LEFT,s,mid-1);
    if ( mid < e ) build(Node[t].son[RIGHT],t,RIGHT,mid+1,e);

    _pushUp(t);
}

int Root;

void dispTree(int&);
int main(){
    char cmd[12];
    int n,m,a,b,c;
    while(n=getInt(),m=getInt(),n<0&&m<0?0:1){
        toUsed = 0;//初始化
        build(Root,0,0,0,n+1);
        while(m--){
            scanf("%s",cmd);
            a = getInt();
            b = getInt();
            if('C'==*cmd) move(Root,a,b,getInt()+1);
            else reverse(Root,a,b);
        }
        dispTree(Root);
    }
    return 0;
}

void _dispTree(int root){
    _pushDown(root);
    if(Node[root].son[LEFT]) _dispTree(Node[root].son[LEFT]);
    printf(" %d",Node[root].value);
    if(Node[root].son[RIGHT]) _dispTree(Node[root].son[RIGHT]);
}
//要保证最后一个数没有输出空格
void dispTree(int& root){
    int t = _kth(root,0);
    _splay(root,0,t);
    int tt = _kth(root,Node[root].size-1);
    _splay(root,root,tt);
    t = _kth(Node[tt].son[LEFT],0);
    _splay(root,tt,t);
    printf("%d",Node[t].value);
    _dispTree(Node[t].son[RIGHT]);
    printf("\n");
}
