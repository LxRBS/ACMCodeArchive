/**
   平衡二叉排序树，用伸展树
1 插入 xx 数
2 删除 xx 数(若有多个相同的数，因只删除一个)
3 查询 xx 数的排名(排名定义为比当前数小的数的个数 +1+1 )
4 查询排名为 xx 的数
5 求 xx 的前驱(前驱定义为小于 xx，且最大的数)
6 求 xx 的后继(后继定义为大于 xx，且最小的数)
*/
#include <cstdio>

typedef int key_t;
int const SIZE = 100100;
int const LEFT = 0;
int const RIGHT = 1;
//Parallel Array
int Parent[SIZE];
int Son[SIZE][2];
int Sn[SIZE];
int Size[SIZE];
int Cnt[SIZE];
key_t Key[SIZE];
int toUsed = 0;

void dispNode(FILE*fp,int t){
    fprintf(fp,"%d: Parent: %d, SN: %d, LSON: %d, RSON: %d\n",t,Parent[t],Sn[t],Son[t][LEFT],Son[t][RIGHT]);
    fprintf(fp,"    Key: %d, Cnt: %d, Size, %d\n",Key[t],Cnt[t],Size[t]);
}
void _dispTree(FILE*fp,int root){
    dispNode(fp,root);
    if ( Son[root][LEFT] ) _dispTree(fp,Son[root][LEFT]);
    if ( Son[root][RIGHT] ) _dispTree(fp,Son[root][RIGHT]);
}
void dispTree(FILE*fp,int root){
    printf("Tree:\n");
    _dispTree(fp,root);
}

inline void _pushUp(int t){
    Size[t] = Cnt[t];
    int son = Son[t][LEFT];
    if ( son ){
        Size[t] += Size[son];
    }
    son = Son[t][RIGHT];
    if ( son ){
        Size[t] += Size[son];
    }
}

inline int _newNode(key_t key=0){
    ++toUsed;
    Parent[toUsed] = Son[toUsed][0] = Son[toUsed][1] = 0;
    Size[toUsed] = Cnt[toUsed] = 0;
    Key[toUsed] = key;
    return toUsed;
}

inline void _link(int parent,int sn,int son){
    Parent[son] = parent;
    Sn[son] = sn;
    Son[parent][sn] = son;
}

void _rotate(int t){
    int p = Parent[t];
    int sn = Sn[t];
    int osn = sn ^ 1;

    _link(p,sn,Son[t][osn]);
    _link(Parent[p],Sn[p],t);
    _link(t,osn,p);

    _pushUp(p);
}

void _splay(int&root,int p,int t){
    int pp;
    while( ( pp = Parent[t] ) != p ){
        if ( Parent[pp] != p ) Sn[pp] == Sn[t] ? _rotate(pp) : _rotate(t);
        _rotate(t);
    }

    _pushUp(t);
    if ( 0 == p ) root = t;
}

int _advance(int root,int& p,key_t key){
    int t = root;
    p = Parent[t];
    while( t && Key[t] != key ){
        p = t;
        t = key < Key[t] ? Son[t][LEFT] : Son[t][RIGHT];
    }
    return t;
}

//k from 1 to N
int _kth(int root,int k){
    int t = root;
    int s = Size[Son[t][LEFT]];

    if ( k <= s ) return _kth(Son[t][LEFT],k);
    if ( s + Cnt[root] < k ) return _kth(Son[t][RIGHT],k-s-Cnt[root]);
    return root;
}

int insert(int&root,key_t key){
    int p,t;
    t = _advance(root,p,key);

    if ( 0 == t ){
        t = _newNode(key);
        _link(p,key<Key[p]?LEFT:RIGHT,t);
    }

    ++Cnt[t];
    _splay(root,0,t);
    return Cnt[t];
}

int remove(int&root,key_t key){
    int p,t;
    t = _advance(root,p,key);

    if ( 0 == t ) return -1;

    _splay(root,0,t);
    if ( Cnt[t] > 1 ){
        --Cnt[t];
        --Size[t];
        return Cnt[t];
    }

    int lson = Son[t][LEFT];
    if ( 0 == lson ){
        root = Son[t][RIGHT];
        Parent[root] = 0;
        return 0;
    }

    int tt = _kth(lson,Size[lson]);//the max of the left son
    _splay(root,root,tt);

    _link(tt,RIGHT,Son[t][RIGHT]);
    _pushUp(tt);
    root = tt;
    Parent[root] = 0;
    return 0;
}

int pred(int&root,key_t key){
    int p;
    int t = _advance(root,p,key);
    if ( t ){
        _splay(root,0,t);
        int lson = Son[t][LEFT];
        return _kth(lson,Size[lson]);
    }

    _splay(root,0,p);
    if ( Key[p] < key ) return p;

    int lson = Son[p][LEFT];
    return _kth(lson,Size[lson]);
}

int succ(int&root,key_t key){

    int p;
    int t = _advance(root,p,key);
    if ( t ){
        _splay(root,0,t);
        int rson = Son[t][RIGHT];
        return _kth(rson,1);
    }

    _splay(root,0,p);
    if ( key < Key[p] ) return p;

    int rson = Son[p][RIGHT];
    return _kth(rson,1);
}

int rank(int&root,key_t key){
    int p;
    int t = _advance(root,p,key);
    _splay(root,0,t);
    int lson = Son[t][LEFT];
    int s = lson ? Size[lson] : 0;
    return s + 1;
}

int kth(int&root,int k){
    int t = _kth(root,k);
    _splay(root,0,t);
    return t;
}

int Root = 0;
int N;
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    while(N--){
        int op,x;
        scanf("%d%d",&op,&x);
        switch(op){
        case 1:insert(Root,x);break;
        case 2:remove(Root,x);break;
        case 3:printf("%d\n",rank(Root,x));break;
        case 4:printf("%d\n",Key[kth(Root,x)]);break;
        case 5:printf("%d\n",Key[pred(Root,x)]);break;
        case 6:printf("%d\n",Key[succ(Root,x)]);break;
        //default:while(1);//it never should be
        }
        //dispTree(stdout,Root);
    }
    return 0;
}

