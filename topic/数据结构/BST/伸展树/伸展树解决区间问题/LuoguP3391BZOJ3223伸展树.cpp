/**
    伸展树解决区间问题
    只有翻转操作
    最后输出序列
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef int value_t;

int const SIZE = 200100;
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
//利用全局建树
void build(int&t,int parent,int sn,int s,int e){
    int mid = ( s + e ) >> 1;

    t = _newNode(mid);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) build(Node[t].son[LEFT],t,LEFT,s,mid-1);
    if ( mid < e ) build(Node[t].son[RIGHT],t,RIGHT,mid+1,e);

    _pushUp(t);
}
inline bool empty(int root){
    return 0 == root || Node[root].size<=2;
}
inline int size(int root){
    return root ? Node[root].size - 2 : -1;
}
int Root;

void dispTree(FILE*,int&);
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    build(Root,0,0,0,n+1);
    while(m--){
        int s = getUnsigned();
        reverse(Root,s,getUnsigned());
    }
    //最后做一个中序遍历，需要pushDown
    dispTree(stdout,Root);
    printf("\n");
    return 0;
}
void _dispTree(FILE* fp,int root){
    _pushDown(root);
    if(Node[root].son[LEFT]) _dispTree(fp,Node[root].son[LEFT]);
    fprintf(stdout,"%d ",Node[root].value);
    if(Node[root].son[RIGHT]) _dispTree(fp,Node[root].son[RIGHT]);
}
void dispTree(FILE*fp,int& root){
    int t = _kth(root,0);
    _splay(root,0,t);
    int tt = _kth(root,Node[root].size-1);
    _splay(root,root,tt);
    _dispTree(fp,Node[tt].son[LEFT]);
}

