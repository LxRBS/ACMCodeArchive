//Splay例程，用加入的顺序来区分键值
//实现插入、查找极值 
#include <cstdio>
#include <cstring>

#define SIZE 60005
#define LEFT  0
#define RIGHT 1

struct key_t{
	int priority;
	int order;
};

struct value_t{
	char name[100];
	int para;
};

bool operator < (key_t const&l,key_t const&r){
	return l.priority < r.priority || ( l.priority == r.priority && l.order < r.order );
}

bool operator == (key_t const&l,key_t const&r){
	return l.priority == r.priority && l.order == r.order;
}

bool operator != (key_t const&l,key_t const&r){
	return ! ( l == r );
}

struct _t{
	int parent;
	int child[2];
	int sn;
	key_t key;
	value_t data;
}Node[SIZE];
int toUsed = 0;

inline void init(){
	toUsed = 0;
	memset(Node,0,sizeof(_t));
}

//to get an index of a vailable node from the array
inline int _newNode(){
	++toUsed;
	memset(Node+toUsed,0,sizeof(_t));
	return toUsed;
}

//to set the p's chils[sn] with t
inline void _link(int p,int sn,int t){
	Node[p].child[sn] = t;
	Node[t].parent = p;
	Node[t].sn = sn;
}

//to find the key int the tree with the root
int _advance(key_t key,int root,int&parent){
	if ( 0 == root ) return parent = 0;
	int t = root;
	parent = Node[t].parent;
	while( t && key != Node[t].key ){
		parent = t;
		t = key < Node[t].key ? Node[t].child[LEFT] : Node[t].child[RIGHT];
	}
	return t;
}

//rotation, there must exist t and its father
void _rotate(int t){
	int p = Node[t].parent;
	int sn = Node[t].sn;
	int osn = sn ^ 1;
	
	int x = Node[t].child[osn];
	_link(p,sn,x);
	
	int grand = Node[p].parent;
	_link(grand,Node[p].sn,t);
	
	_link(t,osn,p);
}

//to splay t just under p in the tree of root
//if p is equal to 0, t will be the root of tree
void _splay(int t,int p,int&root){
	while( Node[t].parent != p ){
		int pp = Node[t].parent;
		if ( Node[pp].parent != p )
		    Node[pp].sn == Node[t].sn ? _rotate(pp) : _rotate(t);
		_rotate(t);
	}
	if ( 0 == p ) root = t;
	return;
}

void insert(key_t key,value_t data,int &root){
    //to new a node
	int t = _newNode();
	Node[t].key = key;
	Node[t].data = data;
	
	if ( 0 == root ){
		root = t;
		return;
	}	
	
	int p;
	int tt = _advance(key,root,p);
	
	int sn = key < Node[p].key ? LEFT : RIGHT;
	_link(p,sn,t);
	_splay(t,0,root);
}

int getMin(int &root){
	if ( 0 == root ) return 0;
	int t = root;
	while( Node[t].child[LEFT] ) t = Node[t].child[LEFT];
	_splay(t,0,root);
	return t;
}

int main(){
	int root = 0;
	char cmd[10];
	int order = 0;
	init();
	while( EOF != scanf("%s",cmd) ){
		if ( 'G' == *cmd ){
			if ( 0 == root ){
				printf("EMPTY QUEUE!\n");
				continue;
			}
			int t = getMin(root);
			printf("%s %d\n",Node[t].data.name,Node[t].data.para);
			//here do not encapsulate the remove operation into a function 
			root = Node[root].child[RIGHT];
			Node[root].parent = 0;
		}else{
			key_t key;
			value_t data;
			scanf("%s%d%d",data.name,&data.para,&key.priority);
			key.order = ++order;
			insert(key,data,root);
		}
	}
}
