/*
    一共有N个数
    对每一个数，求之前与之最接近的数

    典型的排序二叉树，插入操作，然后求最接近的数
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE = 500000;
int const LEFT = 0;
int const RIGHT = 1;

typedef int key_t;

struct node_t{
    int parent;//父节点
    int son[2];//子节点
    int sn;    //排行
    key_t key; //键
}Node[SIZE];
int NCnt;

void _dispNode(int i,FILE*fp=stdout){
    fprintf(fp,"%d: Parent: %d, Sons:(%d,%d), SN: %d\n",i,Node[i].parent,Node[i].son[LEFT],Node[i].son[RIGHT],Node[i].sn);
    fprintf(fp,"    value: %d, SIZE: %d, flip: %d\n",Node[i].key);
}

void _dispTree(int root,FILE*fp=stdout){
    _dispNode(root,fp);
    int son = Node[root].son[LEFT];
    if (son) _dispTree(son,fp);
    son = Node[root].son[RIGHT];
    if (son) _dispTree(son,fp);
}

void dispTree(int root,FILE*fp=stdout){
    fprintf(fp,"Tree:\n");
    _dispTree(root,fp);
    fprintf(fp,"\n");
}

inline int _newNode(key_t key=0){
    Node[NCnt].parent = Node[NCnt].son[0] = Node[NCnt].son[1] = 0;
    Node[NCnt].key = key;
    return NCnt++;
}

inline void initTree(){
    NCnt = 0;
    _newNode();
}

//将p的sn儿子设置为t
inline void _link(int p,int sn,int t){
    Node[p].son[sn] = t;
    Node[t].parent = p;
    Node[t].sn = sn;
}

//对t做旋转，重新确定三对父子关系
//这个函数要求t不是树根
inline void _rotate(int t){
    int p = Node[t].parent;
    int sn = Node[t].sn;
    int osn = sn ^ 1;

    _link(p,sn,Node[t].son[osn]);
    _link(Node[p].parent,Node[p].sn,t);
    _link(t,osn,p);
}

//在root树上将t伸展为p的儿子
void _splay(int&root,int p,int t){
    while( Node[t].parent != p ) {
        int pp = Node[t].parent;
        if ( Node[pp].parent != p ) Node[pp].sn == Node[t].sn ? _rotate(pp) : _rotate(t);
        _rotate(t);
    }

    if ( 0 == p ) root = t;
}

//保证root不为空树
void insert(int&root,key_t key){
    int p = 0, t = root;
    while( t ){
        p = t;
        t = key < Node[t].key ? Node[t].son[LEFT] : Node[t].son[RIGHT];
    }

    t = _newNode(key);
    _link(p,key<Node[p].key?LEFT:RIGHT,t);
    _splay(root,0,t);
}

//在root树上找最小键
int minKey(int root){
    if ( 0 == root ) return 0;

    int t = root;
    while( Node[t].son[LEFT] ) t = Node[t].son[LEFT];
    return t;
}

//在root树上找最大键
int maxKey(int root){
    if ( 0 == root ) return 0;

    int t = root;
    while( Node[t].son[RIGHT] ) t = Node[t].son[RIGHT];
    return t;
}

int proc(int&root,key_t key){
    insert(root,key);

    int t1 = minKey(Node[root].son[RIGHT]);
    int t2 = maxKey(Node[root].son[LEFT]);

    int ret = 2000000000;
    if ( t1 ) ret = min(ret,Node[t1].key-key);
    if ( t2 ) ret = min(ret,key-Node[t2].key);

    return ret;
}

int N,Root;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initTree();Root = 0;

    int a,ans=0;;
    for(int i=0;i<N;++i){
        scanf("%d",&a);

        if ( 0 == i ) ans += a, Root = _newNode(a);
        else ans += proc(Root,a);
    }
    printf("%d\n",ans);

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() );
    return 0;
}
