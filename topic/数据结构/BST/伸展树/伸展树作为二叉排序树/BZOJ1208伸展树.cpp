/*
    有一堆宠物每一个都拥有一个点数（各不相同）
    有一堆领养者，每一个都有一个希望点数

    任意时刻，如果宠物比领养者多，每个领养者将领养与其期望最近最小的
    如果领养者比宠物多，宠物会被与之最近最小的领养者领养

    求所有领养关系的差和

    典型的排序二叉树，求前驱和后继，还需要插入和删除操作
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE = 500000;
int const LEFT = 0;
int const RIGHT = 1;

typedef long long int key_tt;

key_tt const MOD = 1000000LL;

struct node_t{
    int parent;//父节点
    int son[2];//子节点
    int sn;    //排行
    key_tt key; //键
}Node[SIZE];
int NCnt;

void _dispNode(int i,FILE*fp=stdout){
    fprintf(fp,"%d: Parent: %d, Sons:(%d,%d), SN: %d\n",i,Node[i].parent,Node[i].son[LEFT],Node[i].son[RIGHT],Node[i].sn);
    fprintf(fp,"    value: %d, \n",Node[i].key);
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

inline int _newNode(key_tt key=0){
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

//在root树上找最大值
int maxKey(int root){
    if ( 0 == root ) return 0;

    int t = root;
    while( Node[t].son[RIGHT] ) t = Node[t].son[RIGHT];
    return t;
}

//在root树上找key的前驱
int prec(int root,key_tt key){
    if ( 0 == root || key == Node[root].key ) return root;
    if ( key < Node[root].key ) return prec(Node[root].son[LEFT],key);

    //在右子树上找前驱
    int p = prec(Node[root].son[RIGHT],key);
    return p ? p : root;
}

//在root树上找后继
int succ(int root,key_tt key){
    if ( 0 == root || key == Node[root].key ) return root;
    if ( Node[root].key < key ) return succ(Node[root].son[RIGHT],key);

    int p = succ(Node[root].son[LEFT],key);
    return p ? p : root;
}

//在root树上找key的前驱和后继
key_tt proc(int&root,key_tt key){
    int t1 = prec(root,key);
    int t2 = succ(root,key);

    key_tt cha1 = t1 ? key - Node[t1].key : 1000000000000000LL;
    key_tt cha2 = t2 ? Node[t2].key - key : 1000000000000000LL;

    int son;
    if ( cha1 <= cha2 ){
        _splay(root,0,t1);
        son = Node[t1].son[LEFT];
        if ( 0 == son ){
            root = Node[t1].son[RIGHT];
            Node[root].parent = 0;
        }else{
            int tt = maxKey(son);
            _splay(root,root,tt);
            _link(tt,RIGHT,Node[t1].son[RIGHT]);
            root = tt;
            Node[root].parent = 0;
        }
        return cha1;
    }else{
        _splay(root,0,t2);
        son = Node[t2].son[LEFT];
        if ( 0 == son ){
            root = Node[t2].son[RIGHT];
            Node[root].parent = 0;
        }else{
            int tt = maxKey(son);
            _splay(root,root,tt);
            _link(tt,RIGHT,Node[t2].son[RIGHT]);
            root = tt;
            Node[root].parent = 0;
        }
        return cha2;
    }
}

void insert(int&root,key_tt key){
    if ( 0 == root ) {
        root = _newNode(key);
        return;
    }

    int p = 0, t = root;
    while( t ){
        p = t;
        t = Node[t].son[ key<Node[t].key ? LEFT : RIGHT ];
    }

    t = _newNode(key);
    _link(p,key<Node[p].key?LEFT:RIGHT,t);
}

int N,Root;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initTree();Root = 0;

    int a,b, now = -1;
    key_tt ans = 0LL;

    while(N--){
        scanf("%d%d",&a,&b);

        if ( now == a || Root == 0 ){
            insert(Root,b);
            now = a;
        }else{
            ans += proc(Root,b);
            ans %= MOD;
        }
    }

    printf("%lld\n",ans);
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() );
    return 0;
}
