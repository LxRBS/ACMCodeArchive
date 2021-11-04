//Splay例程，加入了size域，可以求出第kth个数 
#include <cstdio>
#include <cstring>

#define SIZE 1111111
#define LEFT  0
#define RIGHT 1

struct key_t{
	int key;   //有相同的键值
	int order; //用插入顺序来区分
	key_t(int a=0,int b=0):key(a),order(b){}
};
typedef int value_t;

struct _t{//树的节点
	int parent;  //父节点，树根为0，意为空
	int child[2];//子节点，0为左，1为右
	int sn;      //指示本节点是其父亲的左儿子还是右儿子，树根无效
	key_t key;   //关键字
	value_t data;//数据域
	int size;    //size域, 指示当前树的节点总数
}Node[SIZE];     //Node[0]不使用，当做NULL指针
int toUsed = 0;

bool operator < (key_t const&l,key_t const&r){
	return l.key < r.key || ( l.key == r.key && l.order < r.order );
}

bool operator == (key_t const&l,key_t const&r){
	return l.key == r.key && l.order == r.order;
}

bool operator != (key_t const&l,key_t const&r){
	return !( l == r );
}

inline void _pushUp(int t){
    Node[t].size = 1;
    int son = Node[t].child[LEFT];
    if ( son ) Node[t].size += Node[son].size;
    son = Node[t].child[RIGHT];
    if ( son ) Node[t].size += Node[son].size;
}

inline void init(){
    toUsed = 0;
	memset(Node,0,sizeof(_t));
}

//得到一个可以用的新节点，返回的是数组的索引
inline int _newNode(){
	++toUsed;
	memset(Node+toUsed,0,sizeof(_t));
	Node[toUsed].size = 1;//这一步很重要
	return toUsed;
}

//将p的sn儿子设置为t
inline void _link(int p,int sn,int t){
	Node[p].child[sn] = t;
	Node[t].parent = p;
	Node[t].sn = sn;
}

//在root树上找key节点，返回所找到的节点，同时parent为该节点的父亲
//返回为0说明没找到，而parent是待插入地方的父节点，parent也为0说明是空树
int _advance(key_t key,int root,int& parent){
	if ( 0 == root ) return parent = 0;

	int t = root;
	parent = Node[t].parent;
	while( t && key != Node[t].key ){
		parent = t;
		t = key < Node[t].key ? Node[t].child[LEFT] : Node[t].child[RIGHT];
	}
	return t;
}

//旋转操作，t是右儿子则做左旋，否则做右旋
//左旋,p(A,t(x,B))变为t(p(A,x),B)
//右旋,p(t(A,x),B)变为t(A,p(x,B))
//t及其父节点必须有意义
void _rotate(int t){
	int p = Node[t].parent;
	int sn = Node[t].sn;//t的排行，左或者右
	int osn = sn ^ 1;

	//p的sn儿子改为x
	int x = Node[t].child[osn];
	_link(p,sn,x);

	//grandfather的相应的儿子变为t
	int grandfather = Node[p].parent;
	_link(grandfather,Node[p].sn,t);

	//t的osn儿子改为p
	_link(t,osn,p);

	//只需维持p即可, 因为t必然要往上持续旋转
	_pushUp(p);
}

//伸展操作,root为根节点代表一棵树
//将t节点伸展成p的子节点，p为0表示伸展至树根
//调用时必须保证t、p和root有意义
void _splay(int t,int p,int& root){
	while ( Node[t].parent != p ){
	    int pp = Node[t].parent;
		if ( Node[pp].parent != p )
			Node[pp].sn == Node[t].sn ?
			_rotate(pp) : _rotate(t);
		_rotate(t);
	}

	//此处维持一次即可
	_pushUp(t);
	if ( 0 == p ) root = t;
	return;
}

//在root树上插入一个节点
void insert(key_t key,value_t data,int&root){
	//新建一个节点
	int t = _newNode();
	Node[t].key = key;
	Node[t].data = data;

	//如果是空树
	if ( 0 == root ){
		root = t;
		return;
	}

	//查找，保证没有相同的键值,因此tt肯定为0
	int p;
	_advance(key,root,p);

	//确定p、t的父子关系，并将t伸展至树根
	int sn = key < Node[p].key ? LEFT : RIGHT;
	_link(p,sn,t);
	_splay(t,0,root);
}

//在t树上挑出第rank个键值, 从1开始编号, 保证有答案
//返回节点编号
int select(int rank,int t){
    if ( 0 == t ) return 0;
    int son = Node[t].child[LEFT];
    int size = son ? Node[son].size : 0;
    //在左子树上递归搜索
    if ( rank <= size ) return select(rank,son);
    //右子树上递归搜索
    if ( rank > size + 1 ) return select(rank-1-size,Node[t].child[RIGHT]);
    return t;
}

//显示一个子树
void _dispNode(int node){
	if ( 0 == node ) return;
	printf("%d,key is %d,size is %d\n  left is %d,right is %d,parent is %d\n"
		,node,Node[node].key.key,Node[node].size
		,Node[node].child[LEFT],Node[node].child[RIGHT],Node[node].parent);
	_dispNode(Node[node].child[LEFT]);
	_dispNode(Node[node].child[RIGHT]);
}
//显示root树
void disp(int root){
	printf("The tree is:\n");
	if ( root ) _dispNode(root);
	else printf("Null Tree.\n");
}

int main(){
	int n,root = 0;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		int v;
		scanf("%d",&v);
		insert(key_t(v,i),0,root);
	}

	char tmp[20];
	scanf("%s%d",tmp,&n);
	for(int i=0;i<n;++i){
		int r;
		scanf("%d",&r);
		int t = select(r,root);
		printf("%d\n",Node[t].key.key);
	}
	return 0;
}

