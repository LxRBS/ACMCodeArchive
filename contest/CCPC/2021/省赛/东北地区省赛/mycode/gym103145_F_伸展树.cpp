/**
 * 一个数组，其初始内容是1~n的排列，一共5种操作
 * 1 s e: 将数组[s, e]翻转
 * 2 s e: 将数组中取值在[s, e]范围内的元素做一个补操作。所谓补操作就是令ai=e=s-ai
 *        例如数组: 1 3 2 5 4,如果有指令: 2 1 4，则数组变为 4 2 3 5 1 
 * 3 i v: 将数组中所有大于等于v的元素的值加1，然后在位置i插入一个元素值为v，原i位置及其以后的元素依次后移一格
 *        很明显，这个操作以后，数组长度加一，数组内容仍然是一个排列
 * 4 i: 问数组第i个位置的元素的值是多少
 * 5 v: 问元素值为v的元素在数组的什么位置，从1开始索引
 * 
 * 首先操作1显然是数组区间操作，用伸展树很容易实现
 * 但是操作2在区间伸展树上没法实现，
 * 操作3将所有元素加1在区间伸展树上也没法实现
 * 虽然可以打lazy标记，但是这个题目不是求和或者最大值，
 * 因此有可能需要把每个节点都依次加1，这个操作显然是O(N)的。
 * 不过这个操作与区间伸展树的构成原理非常吻合，因此可以考虑用一个权值伸展树来解决这个问题
 * 
 * 所谓区间伸展树，实际上就是不保存索引，而是用伸展树的结构内禀的性质来指示数组索引，
 * 于是可以轻松完成插入操作。注意打插入操作其实就是后续的索引均加1
 * 因此再造一个权值伸展树，同样不用保存值，每个节点的位置本身就指示了值
 * 两棵树相应的节点进行互指。
 * 操作1: 区间伸展树翻转
 * 操作2：权值伸展树翻转
 * 操作3：区间伸展树中在i位置插入1个节点，权值伸展树在v位置插入1个节点，且两个节点互指
 * 操作4：在区间伸展树中找到位置1，再找到它对应的权值伸展树的节点，看看这个节点中序遍历的序号即可
 * 操作5：类似操作4
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 10;
#else
int const SIZE = 100100;
#endif
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    int sn;
    int size;
    int value;
    int point; // 互指
    unsigned char flip;
}Node[SIZE<<2];

int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
    }
    if(son = Node[t].son[RIGHT]){
        Node[t].size += Node[son].size;
    }
}




inline void _pushDown(int t){
    if(0==t) return;

    int son;
    if(Node[t].flip){
        swap(Node[t].son[LEFT], Node[t].son[RIGHT]);
        if(son=Node[t].son[LEFT]) Node[son].sn = LEFT, Node[son].flip ^= 1;
        if(son=Node[t].son[RIGHT]) Node[son].sn = RIGHT, Node[son].flip ^= 1;
        Node[t].flip ^= 1;
    }
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
    _pushUp(t);
    if(0==p) root = t;//改根
}

inline int _newNode(int value){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //其他域不用管，在各自函数中处理
    Node[toUsed].value = value;
    return toUsed;
}

int _kth(int t, int k){
    _pushDown(t);
    int son = Node[t].son[LEFT];
    int s = son?Node[son].size:0;
    if(k<s) return _kth(son,k);//去左子树找
    return s < k ? _kth(Node[t].son[RIGHT],k-s-1) : t;
}

//在第pos位置插入一个值value，参数一定合法，pos从1开始
void insert(int&root,int pos){
    int t = _kth(root,pos-1);
    _splay(root,0,t);//将pos-1旋到树根
    int tt = _kth(root,pos);
    _splay(root,root,tt);//将pos旋到根的右儿子
    //把新节点挂到根的右儿子的左儿子
    //更新值
    t = _newNode(0);
    Node[t].size = 1; 
    _link(tt,LEFT,t);
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

/// 建立区间伸展树
void _build(int &t, int parent, int sn, int s, int e, int const a[]){
    int mid = (s+e) >> 1;

    t = _newNode(a[mid]);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) _build(Node[t].son[LEFT],t,LEFT,s,mid-1,a);
    if ( mid < e ) _build(Node[t].son[RIGHT],t,RIGHT,mid+1,e,a);

    _pushUp(t);    
}

//返回root树的尺寸，是减去哨兵以后的节点数量
inline int size(int root){
    return Node[root].size - 2;
}

//在root树上查找排名第k的节点，k从1开始
int kth(int&root,int k){
    //如果k非法，注意size返回的是减去哨兵以后的size
    // if ( k <= 0 || k > size(root) ) return 0;
    int t = _kth(root,k);
    _splay(root,0,t);
    return t;
}

void _maintain(int t){
    if(Node[t].parent) _maintain(Node[t].parent);
    _pushDown(t);
}

/// 在root树上把t伸展成树根
inline int find(int&root, int t){
    _maintain(t);
    _splay(root, 0 ,t);
}

int Pointer[SIZE];

/// 建立权值伸展树
void _build2(int &t, int parent, int sn, int s, int e){
    int mid = (s+e) >> 1;

    t = _newNode(mid);
    Node[t].parent = parent;
    Node[t].sn = sn;
    Pointer[mid] = t;

    if ( s < mid ) _build2(Node[t].son[LEFT],t,LEFT,s,mid-1);
    if ( mid < e ) _build2(Node[t].son[RIGHT],t,RIGHT,mid+1,e);

    _pushUp(t);     
}

int N, M, A[SIZE];
int Root[2];

void build(int n, const int a[]){
    toUsed = 0;
    /// 首先建立区间伸展树
    _build(Root[0], 0, 0, 0, n+1, a);
    /// 然后建一个权值伸展树
    _build2(Root[1], 0, 0, 0, n+1);
    /// 权值线段树的最后一个值要改成无穷大
    int t = Root[1], son;
    while(son = Node[t].son[RIGHT]){
        t = son;
    }
    assert(Node[t].value == n+1);
    
    /// 两个伸展树的节点要互相指
    for(int p,i=1;i<=n+2;++i){
        p = Pointer[Node[i].value];
        Node[Node[i].point = p].point = i;

        if(Node[i].value == n + 1){
            Node[i].value = 0;
            Node[Node[i].point].value = 2000000000;
        }
    }
}

void disp(int t){
    printf("%d: value = %d, point = %d, left = %d, righ = %d, parent = %d\n", t, Node[t].value, Node[t].point, Node[t].son[LEFT], Node[t].son[RIGHT], Node[t].parent);
    
    _pushDown(t);
    int son;
    if(son=Node[t].son[LEFT]) disp(son);
    if(son=Node[t].son[RIGHT]) disp(son);
}

void disp(){
    printf("Root 0:\n");
    disp(Root[0]);
    printf("Root 1:\n");
    disp(Root[1]);
}

int main(){
    // freopen("2.txt","w",stdout);
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        M = getInt();
        A[0] = 0;
        A[N+1] = N + 1;
        for(int i=1;i<=N;++i)A[i] = getInt();

        build(N, A);

        // disp();

        for(int a,b,cmd,qi=1;qi<=M;++qi){
            switch(cmd=getInt()){
                case 1:{
                    a = getInt();
                    b = getInt();
                    reverse(Root[0], a, b);
                }break;
                case 2:{
                    a = getInt();
                    b = getInt();
                    reverse(Root[1], a, b);
                }break;
                case 3:{ // 
                    a = getInt();
                    b = getInt();
                    insert(Root[0], a);
                    insert(Root[1], b);
                    // 互指
                    int t0 = Node[Node[Root[0]].son[RIGHT]].son[LEFT];
                    int t1 = Node[Node[Root[1]].son[RIGHT]].son[LEFT];
                    Node[Node[t0].point = t1].point = t0;
                }break;
                case 4:{ // 问位置a上的数
                    a = getInt();
                    /// 首先找到区间伸展树的节点
                    int t0 = kth(Root[0], a);
                    /// 然后拿到权值伸展树上对应的节点
                    int t1 = Node[t0].point;
                    /// 要pushDown
                    find(Root[1], t1);
                    _splay(Root[1], 0, t1);
                    printf("%d\n", Node[Node[t1].son[LEFT]].size);
                }break;
                case 5:{ // 问值a所在的位置
                    a = getInt();
                    /// 首先找到权值伸展树的节点
                    int t1 = kth(Root[1], a);
                    int t0 = Node[t1].point;
                    find(Root[0], t0);
                    printf("%d\n", Node[Node[t0].son[LEFT]].size);
                }break;
                throw runtime_error("wrong CMD");
            }            
        }
    }
    return 0;
}
