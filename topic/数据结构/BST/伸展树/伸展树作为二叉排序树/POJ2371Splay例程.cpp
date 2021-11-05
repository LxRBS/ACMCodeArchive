//Splay���̣�������size�򣬿��������kth���� 
#include <cstdio>
#include <cstring>

#define SIZE 1111111
#define LEFT  0
#define RIGHT 1

struct key_t{
	int key;   //����ͬ�ļ�ֵ
	int order; //�ò���˳��������
	key_t(int a=0,int b=0):key(a),order(b){}
};
typedef int value_t;

struct _t{//���Ľڵ�
	int parent;  //���ڵ㣬����Ϊ0����Ϊ��
	int child[2];//�ӽڵ㣬0Ϊ��1Ϊ��
	int sn;      //ָʾ���ڵ����丸�׵�����ӻ����Ҷ��ӣ�������Ч
	key_t key;   //�ؼ���
	value_t data;//������
	int size;    //size��, ָʾ��ǰ���Ľڵ�����
}Node[SIZE];     //Node[0]��ʹ�ã�����NULLָ��
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

//�õ�һ�������õ��½ڵ㣬���ص������������
inline int _newNode(){
	++toUsed;
	memset(Node+toUsed,0,sizeof(_t));
	Node[toUsed].size = 1;//��һ������Ҫ
	return toUsed;
}

//��p��sn��������Ϊt
inline void _link(int p,int sn,int t){
	Node[p].child[sn] = t;
	Node[t].parent = p;
	Node[t].sn = sn;
}

//��root������key�ڵ㣬�������ҵ��Ľڵ㣬ͬʱparentΪ�ýڵ�ĸ���
//����Ϊ0˵��û�ҵ�����parent�Ǵ�����ط��ĸ��ڵ㣬parentҲΪ0˵���ǿ���
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

//��ת������t���Ҷ�����������������������
//����,p(A,t(x,B))��Ϊt(p(A,x),B)
//����,p(t(A,x),B)��Ϊt(A,p(x,B))
//t���丸�ڵ����������
void _rotate(int t){
	int p = Node[t].parent;
	int sn = Node[t].sn;//t�����У��������
	int osn = sn ^ 1;

	//p��sn���Ӹ�Ϊx
	int x = Node[t].child[osn];
	_link(p,sn,x);

	//grandfather����Ӧ�Ķ��ӱ�Ϊt
	int grandfather = Node[p].parent;
	_link(grandfather,Node[p].sn,t);

	//t��osn���Ӹ�Ϊp
	_link(t,osn,p);

	//ֻ��ά��p����, ��Ϊt��ȻҪ���ϳ�����ת
	_pushUp(p);
}

//��չ����,rootΪ���ڵ����һ����
//��t�ڵ���չ��p���ӽڵ㣬pΪ0��ʾ��չ������
//����ʱ���뱣֤t��p��root������
void _splay(int t,int p,int& root){
	while ( Node[t].parent != p ){
	    int pp = Node[t].parent;
		if ( Node[pp].parent != p )
			Node[pp].sn == Node[t].sn ?
			_rotate(pp) : _rotate(t);
		_rotate(t);
	}

	//�˴�ά��һ�μ���
	_pushUp(t);
	if ( 0 == p ) root = t;
	return;
}

//��root���ϲ���һ���ڵ�
void insert(key_t key,value_t data,int&root){
	//�½�һ���ڵ�
	int t = _newNode();
	Node[t].key = key;
	Node[t].data = data;

	//����ǿ���
	if ( 0 == root ){
		root = t;
		return;
	}

	//���ң���֤û����ͬ�ļ�ֵ,���tt�϶�Ϊ0
	int p;
	_advance(key,root,p);

	//ȷ��p��t�ĸ��ӹ�ϵ������t��չ������
	int sn = key < Node[p].key ? LEFT : RIGHT;
	_link(p,sn,t);
	_splay(t,0,root);
}

//��t����������rank����ֵ, ��1��ʼ���, ��֤�д�
//���ؽڵ���
int select(int rank,int t){
    if ( 0 == t ) return 0;
    int son = Node[t].child[LEFT];
    int size = son ? Node[son].size : 0;
    //���������ϵݹ�����
    if ( rank <= size ) return select(rank,son);
    //�������ϵݹ�����
    if ( rank > size + 1 ) return select(rank-1-size,Node[t].child[RIGHT]);
    return t;
}

//��ʾһ������
void _dispNode(int node){
	if ( 0 == node ) return;
	printf("%d,key is %d,size is %d\n  left is %d,right is %d,parent is %d\n"
		,node,Node[node].key.key,Node[node].size
		,Node[node].child[LEFT],Node[node].child[RIGHT],Node[node].parent);
	_dispNode(Node[node].child[LEFT]);
	_dispNode(Node[node].child[RIGHT]);
}
//��ʾroot��
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

