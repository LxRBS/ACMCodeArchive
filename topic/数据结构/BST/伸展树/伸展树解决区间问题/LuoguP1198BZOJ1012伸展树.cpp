/**
    一个序列，初始为空，两种操作
    Q L：查询末尾L个数中最大的
    A n：将上一次的答案加n插入到末尾
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

int const SIZE = 200100;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;//父节点
    int son[2];//子节点
    int sn;    //本节点的排行
    int size;  //size域
    value_t value; //值
    value_t peak;  //最大值
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].peak = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].peak = max(Node[t].peak,Node[son].peak);
    }
    son = Node[t].son[RIGHT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].peak = max(Node[t].peak,Node[son].peak);
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
    int son = Node[t].son[LEFT];
    int s = son?Node[son].size:0;
    if(k<s) return _kth(son,k);//去左子树找
    return s < k ? _kth(Node[t].son[RIGHT],k-s-1) : t;
}

//在第pos位置插入一个值value，参数一定合法，pos从1开始
void insert(int&root,int pos,value_t const&value){
    int t = _kth(root,pos-1);
    _splay(root,0,t);//将pos-1旋到树根
    int tt = _kth(root,pos);
    _splay(root,root,tt);//将pos旋到根的右儿子
    //把新节点挂到根的右儿子的左儿子
    t = _newNode(value);
    Node[t].peak = value;
    Node[t].size = 1;
    _link(tt,LEFT,t);
    _pushUp(tt);_pushUp(root);
}

value_t max(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].peak;
}
void build(int&t,int parent,int sn,int s,int e){
    int mid = ( s + e ) >> 1;

    t = _newNode(mid);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) build(Node[t].son[LEFT],t,LEFT,s,mid-1);
    if ( mid < e ) build(Node[t].son[RIGHT],t,RIGHT,mid+1,e);

    _pushUp(t);
}
inline int size(int root){
    return Node[root].size - 2;
}

int Root;

int main(){
    //freopen("1.txt","r",stdin);
    int m = getInt();
    int mod = getInt();
    int pos, last = 0;
    char cmd[3];

    //初始化
    toUsed = 0;
    build(Root,0,0,0,1);

    while(m--){
        scanf("%s",cmd);
        pos = size(Root);
        if('A'==*cmd){
            insert(Root,pos+1,(getInt()+last)%mod);
        }else{
            printf("%d\n",last=max(Root,pos-getInt()+1,pos));
        }
    }
    return 0;
}

