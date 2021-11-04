/*
    3种操作
    1KP：将客户K以优先级P加入
    2：优先级最高的出去
    3：优先级最低的出去
    伸展树作为排序二叉树最基本的操作
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 1000010;
int const LEFT = 0;
int const RIGHT = 1;

typedef int key_t;
typedef int value_t;

struct node_t{
    int parent;//父，p为0则表示根
    int son[2];//子
    int sn;    //排行：左或右
    key_t key; //键，本题即优先级
    value_t value;//值
}Node[SIZE];   //0表示空
int toUsed;

//初始化
inline void initTree(){
    memset(Node,0,sizeof(node_t));
    toUsed = 1;
}

//获取一个可用的节点，相当于new
inline int _newNode(){
    memset(Node+toUsed,0,sizeof(node_t));
    return toUsed++;
}

//将p的sn儿子设置为t
inline void _link(int p,int sn,int t){
    Node[ Node[t].parent = p ].son[ Node[t].sn = sn ] = t;
}

//旋转t，t必须不是根
inline void _rotate(int t){
    int sn = Node[t].sn;
    int osn = sn ^ 1;
    int p = Node[t].parent;

    _link(Node[p].parent,Node[p].sn,t);
    _link(p,sn,Node[t].son[osn]);
    _link(t,osn,p);
}

//伸展，将t伸展为p的儿子，p为0则伸展为树根
void _splay(int&root,int p,int t){
    while( Node[t].parent != p ){
        int pp = Node[t].parent;
        if ( Node[pp].parent != p ) Node[pp].sn == Node[t].sn ? _rotate(pp) : _rotate(t);
        _rotate(t);
    }

    if ( 0 == p ) root = t;
}

//在root树上查找键为key的节点，找到返回节点
//否则返回0，且p为待插入的父节点编号
int _advance(int root,int&parent,key_t key){
    int t = root;
    parent = Node[t].parent;
    while( t && key != Node[t].key ){
        parent = t;
        t = Node[t].son[ key < Node[t].key ? LEFT : RIGHT ];
    }
    return t;
}

//插入操作，在root树上插入键为key值为value的节点
void insert(int&root,key_t key,value_t value){
    //新建一个节点
    int t = _newNode();
    Node[t].key = key;
    Node[t].value = value;

    //如果是空树
    if ( 0 == root ){
        root = t;
        return;
    }

    //查找应插入的位置，保证没有相同的键
    int p;
    int tt = _advance(root,p,key);

    //确定父子关系
    int sn = key < Node[p].key ? LEFT : RIGHT;
    _link(p,sn,t);
    _splay(root,0,t);
}

//在root树上查找最大值，返回节点
int max(int &root){
    if ( 0 == root ) return 0;

    int t = root;
    while( Node[t].son[RIGHT] ) t = Node[t].son[RIGHT];
    _splay(root,0,t);
    return t;
}

//在root树上查找最小值，返回节点
int min(int &root){
    if ( 0 == root ) return 0;

    int t = root;
    while( Node[t].son[LEFT] ) t = Node[t].son[LEFT];
    _splay(root,0,t);
    return t;
}

int main(){
    //freopen("1.txt","r",stdin);

    initTree();
    int cmd,k,p,root=0;//首先是一个空树
    while( scanf("%d",&cmd),cmd ){
        if ( 1 == cmd ){
            scanf("%d%d",&k,&p);
            insert(root,p,k);
        }else if ( 2 == cmd ){
            int t = max(root);
            printf("%d\n",Node[t].value);
            //删除最大值，由于特殊性此处就不封装了
            if ( root ){
                root = Node[root].son[LEFT];
                Node[root].parent = 0;
            }
        }else{
            int t = min(root);
            printf("%d\n",Node[t].value);
            //删除最小值，由于特殊性此处就不封装了
            if ( root ){
                root = Node[root].son[RIGHT];
                Node[root].parent = 0;
            }
        }
    }
    return 0;
}
