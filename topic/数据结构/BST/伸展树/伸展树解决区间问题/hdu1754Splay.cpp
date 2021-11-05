/**
    单点修改
    区间查询最小值
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
    value_t peak;//最大值
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

//[s,e]区间全部设置为newValue
void modifyS(int&root,int s,int e,value_t const&newValue){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    //根的左儿子的右儿子打标记
    int son = Node[tt].son[LEFT];
    Node[son].value = Node[son].peak = newValue;
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
//利用全局数组建树
void build(int&t,int parent,int sn,int s,int e,value_t const a[]){
    int mid = ( s + e ) >> 1;

    t = _newNode(a[mid]);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) build(Node[t].son[LEFT],t,LEFT,s,mid-1,a);
    if ( mid < e ) build(Node[t].son[RIGHT],t,RIGHT,mid+1,e,a);

    _pushUp(t);
}
int Root;
value_t A[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    char cmd[3];
    int n,m,a;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;++i)A[i] = getUnsigned();
        toUsed = 0;
        build(Root,0,0,0,n+1,A);
        while(m--){
            scanf("%s",cmd);
            a = getUnsigned();
            if('Q'==*cmd)printf("%d\n",max(Root,a,getUnsigned()));
            else modifyS(Root,a,a,getUnsigned());
        }
    }

    return 0;
}


