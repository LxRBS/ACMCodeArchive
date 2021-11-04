/**
    6种操作，指令全部是大写的
    add x y d：区间增加
    reverse x y：区间翻转
    revolve x y k：区间循环移位
    insert x p：在x节点之后插入一个节点，注意与模板的区别
    delete x：删除一个节点
    min x y：区间极小值
*/
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <algorithm>
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
    value_t valley;//最小值
    value_t lazyd; //delta的延迟标记和数值
    unsigned char flip;//第0位表示翻转的延迟标记
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].valley = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].valley = min(Node[t].valley,Node[son].valley);
    }
    son = Node[t].son[RIGHT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].valley = min(Node[t].valley,Node[son].valley);
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
    if ( t && Node[t].lazyd ){//最后处理delta的
        value_t& lazy = Node[t].lazyd;

        int son = Node[t].son[LEFT];
        if(son){
            Node[son].value += lazy;
            Node[son].lazyd += lazy;
            Node[son].valley += lazy;
        }

        son = Node[t].son[RIGHT];
        if(son){
            Node[son].value += lazy;
            Node[son].lazyd += lazy;
            Node[son].valley += lazy;
        }

        lazy = 0;
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

//在第pos位置插入一个值value，参数一定合法，pos从1开始
void insert(int&root,int pos,value_t const&value){
    int t = _kth(root,pos-1);
    _splay(root,0,t);//将pos-1旋到树根
    int tt = _kth(root,pos);
    _splay(root,root,tt);//将pos旋到根的右儿子
    //把新节点挂到根的右儿子的左儿子
    t = _newNode(value);
    Node[t].valley = value;
    Node[t].size = 1;
    _link(tt,LEFT,t);
    _pushUp(tt);_pushUp(root);
}
//删除区间[s,e]，参数一定合法
void remove(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    Node[tt].son[LEFT] = 0;
    _pushUp(tt);_pushUp(root);
}
//[s,e]区间全部增加delta
void modifyD(int&root,int s,int e,value_t const&delta){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    //根的左儿子的右儿子打标记
    int son = Node[tt].son[LEFT];
    Node[son].value += delta;
    Node[son].valley += delta;
    Node[son].lazyd += delta;
    _pushUp(tt);_pushUp(root);
}
//[s,e]区间右移循环移位k
void rotate(int&root,int s,int e,int k){
    if(0==(k%=(e-s+1))) return;
    if(k<0) k = e-s+1+k;
    //首先删除[e-k+1,e]
    int t = _kth(root,e-k);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    int son = Node[tt].son[LEFT];
    Node[tt].son[LEFT] = 0;
    _pushUp(tt);_pushUp(root);
    //再把son插入到s位置
    t = _kth(root,s-1);
    _splay(root,0,t);
    tt = _kth(root,s);
    _splay(root,root,tt);
    _link(tt,LEFT,son);
    _pushUp(tt);_pushUp(root);
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
value_t min(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].valley;
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
    int n = getInt();
    for(int i=1;i<=n;++i)A[i]=getInt();
    build(Root,0,0,0,n+1,A);
    int m = getInt();

    char cmd[30];
    int x,y;
    while(m--){
        scanf("%s",cmd);
        x = getInt();
        switch(*cmd){
            case 'A':y=getInt();modifyD(Root,x,y,getInt());break;
            case 'D':remove(Root,x,x);break;
            case 'I':insert(Root,x+1,getInt());break;
            case 'M':printf("%d\n",min(Root,x,getInt()));break;
            case 'R':{
                if('E'==cmd[3])reverse(Root,x,getInt());
                else if('O'==cmd[3])y=getInt(),rotate(Root,x,y,getInt());
                else throw runtime_error("Wrong cmd");
            }break;
            default:throw runtime_error("Wrong cmd");
        }
    }
    return 0;
}
