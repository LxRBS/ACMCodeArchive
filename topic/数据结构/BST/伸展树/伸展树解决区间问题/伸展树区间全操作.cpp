/**
1：区间增加
2：区间倍乘
3：区间设置
4：区间查询和
5：区间查询平方和
6：区间查询立方和
7：区间查询最大值，不取模全正数可以正确处理，否则需要修正
8：区间查询最小值
9：区间翻转
10：区间循环右移
11：区间移动
12：区间删除
13：单点插入

注意取模意义下的最值是不正确的，因为无法正确处理延迟操作
另外要注意不取模意义下，最值的计算与正负号有关
此处全是正数
参数不做合法性检测，调用者需要保证参数合法

void build(int n, valuet const a[]): 给定n个数的数组，初始化伸展树。初始化操作，必须调用。a[0],a[n+1]最好初始化为特殊数以方便调试，其他数也不影响结果
void insert(int &root, int pos, const valuet&value): 在root树上的第pos个位置插入一个节点，权值为value。插入以后，原pos位置上的数及其后面的数均往后移动一格
value_t max(int &root, int s, int e): 在root树上查询[s, e]的最大值
value_t max(int &root, int s, int e): 在root树上查询[s, e]的最小值
void modifyD(int &root, int s, int e, const value_t &delta): 在root树上[s, e]全部增加delta
void modifyM(int &root, int s, int e, const value_t &m): 在root树上[s, e]全部倍乘m
void modifyS(int &root, int s, int e, const value_t &newValue): 在root树上[s, e]全部增加newValue
void move(int &root, int s, int e, int pos): 在root树上，将[s, e]移动到pos位置，也就是说移动之后，原s位置的数将从第pos位置开始，其后依次类推
void remove(int &root, int s, int e): 在root树上删除[s, e]，可以全部删光
void reverse(int &root, int s, int e): 在root上，翻转[s, e]
void rotate4(int &root, int s, int e, int k): 在root树上，循环右移[s, e]k位，如果k小于零，就是循环左移
*/
#include <bits/stdc++.h>
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

typedef long long int llt;
typedef llt value_t;

llt const MOD = 1000000007LL;

inline llt add(llt x,llt y){return (x+y)%MOD;}
inline llt add(llt x,llt y,llt z){return add(x, add(y, z));}
inline llt add(llt x,llt y,llt z,llt w){return add(x, add(y, z, w));}

inline llt mul(llt x,llt y){return (x*y)%MOD;}
inline llt mul(llt x,llt y,llt z){return mul(x, mul(y, z));}
inline llt mul(llt x,llt y,llt z,llt w){return mul(x, mul(y, z, w));}

inline void addAss(llt&x, llt y){x=add(x, y);}
inline void mulAss(llt&x, llt y){x=mul(x, y);}

int const SIZE = 200100;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;//父节点
    int son[2];//子节点
    int sn;    //本节点的排行
    int size;  //size域
    value_t value; //值
    value_t peak;  //最大值，注意如果取模，则最值可能不对
    value_t valley;//最小值
    llt sum;       //和值，只有和值有可能超过int32
    llt sum2;      //平方和
    llt sum3;      //立方和
    value_t k;     //注意k必须为正，否则极值可能不对
    value_t b;
    value_t x;     //延迟标记，k是倍乘，b是增加，x是设置
    unsigned char flip;//第0位表示翻转的延迟标记，第1位表示set的延迟标记
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].sum = Node[t].peak = Node[t].valley = Node[t].value;
    Node[t].sum2 = mul(Node[t].value, Node[t].value);
    Node[t].sum3 = mul(Node[t].sum2, Node[t].value);

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        addAss(Node[t].sum, Node[son].sum);
        addAss(Node[t].sum2, Node[son].sum2);
        addAss(Node[t].sum3, Node[son].sum3);
        Node[t].peak = max(Node[t].peak,Node[son].peak);
        Node[t].valley = min(Node[t].valley,Node[son].valley);
    }
    if(son = Node[t].son[RIGHT]){
        Node[t].size += Node[son].size;
        addAss(Node[t].sum, Node[son].sum);
        addAss(Node[t].sum2, Node[son].sum2);
        addAss(Node[t].sum3, Node[son].sum3);
        Node[t].peak = max(Node[t].peak,Node[son].peak);
        Node[t].valley = min(Node[t].valley,Node[son].valley);
    }
}

void _f(int t,int size,int k,int b){
    Node[t].peak = add(mul(Node[t].peak, k), b);
    Node[t].valley = add(mul(Node[t].valley, k), b);

    llt k2 = mul(k, k);
    llt k3 = mul(k2, k);
    llt b2 = mul(b, b);
    llt b3 = mul(b2, b);
    //立方和
    Node[t].sum3 = add(mul(k3, Node[t].sum3), mul(3, k2, b, Node[t].sum2), mul(3, k, b2, Node[t].sum), mul(size, b3));
    //平方和
    Node[t].sum2 = add(mul(k2, Node[t].sum2), mul(2, k, b, Node[t].sum), mul(size, b2));
    //和
    Node[t].sum = add(mul(Node[t].sum, k), mul(size, b));
}
inline void _pushDown(int t){
    if (0==t) return;

    int son;
    if(Node[t].flip & 1){//首先处理翻转
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);
        if(son=Node[t].son[LEFT]) Node[son].sn = LEFT, Node[son].flip ^= 1;
        if(son=Node[t].son[RIGHT]) Node[son].sn = RIGHT, Node[son].flip ^= 1;
        Node[t].flip ^= 1;
    }

    value_t&k = Node[t].k;
    value_t&b = Node[t].b;
    value_t&x = Node[t].x;
    if(Node[t].flip & 2){//再处理set
        llt tmp = add(mul(k, x), b);

        if(son = Node[t].son[LEFT]){
            //延迟标记
            Node[son].flip |= 2;//打set延迟标记
            Node[son].k = 1;
            Node[son].b = 0;
            Node[son].x = tmp;
            //更新值
            Node[son].value = Node[son].peak = Node[son].valley = tmp;
            Node[son].sum = mul(tmp, Node[son].size);
            Node[son].sum2 = mul(tmp, tmp, Node[son].size);
            Node[son].sum3 = mul(tmp, tmp, tmp, Node[son].size);
        }
        if(son = Node[t].son[RIGHT]){
            //延迟标记
            Node[son].flip |= 2;//打set延迟标记
            Node[son].k = 1;
            Node[son].b = 0;
            Node[son].x = tmp;
            //更新值
            Node[son].value = Node[son].peak = Node[son].valley = tmp;
            Node[son].sum = mul(tmp, Node[son].size);
            Node[son].sum2 = mul(tmp, tmp, Node[son].size);
            Node[son].sum3 = mul(tmp, tmp, tmp, Node[son].size);
        }

        Node[t].flip ^= 2;//清除set标记
    }else if (k!=1||b!=0){//最后处理
        if(son = Node[t].son[LEFT]){
            //延迟标记
            mulAss(Node[son].k, k);
            Node[son].b = add(mul(k, Node[son].b), b);
            //更新值
            Node[son].value = add(mul(Node[son].value, k), b);
            _f(son, Node[son].size, k, b);
        }

        if(son=Node[t].son[RIGHT]){
            //延迟标记
            mulAss(Node[son].k, k);
            Node[son].b = add(mul(k, Node[son].b), b);
            //更新值
            Node[son].value = add(mul(Node[son].value, k), b);
            _f(son, Node[son].size, k, b);
        }
    }
    k=1;b=0;x=0;
}
//分配一个新节点
inline int _newNode(value_t value=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //其他域不用管，在各自函数中处理
    Node[toUsed].value = value;
    Node[toUsed].k = 1;//其他都初始化为0，这个一定要是1
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
    //更新值
    t = _newNode(value);
    Node[t].peak = Node[t].valley = Node[t].sum = value;
    Node[t].size = 1;
    Node[t].sum3 = mul(value, Node[t].sum2=mul(value, value));
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
    //延迟标记
    addAss(Node[son].b, delta);
    //更新值
    addAss(Node[son].value, delta);
    _f(son,Node[son].size,1, delta);
    _pushUp(tt);_pushUp(root);
}
//[s,e]区间全部设置为newValue
void modifyS(int&root,int s,int e,value_t const&newValue){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    //根的左儿子的右儿子打标记
    int son = Node[tt].son[LEFT];
    Node[son].flip |= 2;//打set延迟标记
    Node[son].k = 1;
    Node[son].b = 0;
    Node[son].x = newValue;
    //更新值
    Node[son].value = Node[son].peak = Node[son].valley = newValue;
    Node[son].sum = mul(Node[son].size, newValue);
    Node[son].sum2 = mul(Node[son].size, newValue, newValue);
    Node[son].sum3 = mul(Node[son].size, newValue, newValue, newValue);
    _pushUp(tt);_pushUp(root);
}
//[s,e]区间全部乘以m
void modifyM(int&root,int s,int e,value_t const&m){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    //根的左儿子的右儿子打标记
    int son = Node[tt].son[LEFT];
    //延迟标记
    mulAss(Node[son].k, m);
    mulAss(Node[son].b, m);
    //更新值
    mulAss(Node[son].value, m);
    _f(son,Node[son].size,m,0);
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
//将[s,e]区间移动到从pos位置开始
void move(int&root ,int s,int e,int pos){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    Node[tt].son[LEFT] = 0;
    _pushUp(tt);_pushUp(root);

    //找pos位置
    //if(pos>e) pos -= e - s + 1;
    t = _kth(root,pos-1);
    _splay(root,0,t);

    tt = _kth(root,pos);
    _splay(root,root,tt);

    _link(tt,LEFT,son);
    _pushUp(tt);_pushUp(root);
}
llt sum(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].sum;
}
llt sum2(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].sum2;
}
llt sum3(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].sum3;
}
value_t max(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].peak;
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
void _build(int&t,int parent,int sn,int s,int e,value_t const a[]){
    int mid = ( s + e ) >> 1;

    t = _newNode(a[mid]);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) _build(Node[t].son[LEFT],t,LEFT,s,mid-1,a);
    if ( mid < e ) _build(Node[t].son[RIGHT],t,RIGHT,mid+1,e,a);

    _pushUp(t);
}

inline bool empty(int root){
    return Node[root].size<=2;
}
inline int size(int root){
    return Node[root].size - 2;
}
int Root;

//利用全局数组建树,一共n个，最好保证a[0],a[n+1]==0
void build(int n, value_t const a[]){
    toUsed = 0;
    _build(Root,0,0,0,n+1,a);
}

value_t A[SIZE];

void dispTree(FILE*,int);
int main(){
    //freopen("1.std.in","r",stdin);
    //freopen("伸展树区间全操作.std.in","r",stdin);
    //freopen("2.txt","w",stdout);
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        //读数据
        int n = getInt();
        int m = getInt();
        for(int i=1;i<=n;++i)A[i]=getInt();
        A[0] = A[n+1] = 0;

        //建树
        build(n, A);

        //答问题
        printf("Case #%d:\n",kase);

        int cmd,s,e;
        value_t w;
        value_t ans;
        for(int i=1;i<=m;++i){
            if(5==i){
                int t=22;
            }
            cmd = getInt();
            s = getInt();
            if(13!=cmd) e = getInt();
            else e = -1;
            switch(cmd){
            case 1:{//增加
                modifyD(Root,s,e,w=getInt());
            }break;
            case 2:{//倍乘
                modifyM(Root,s,e,w=getInt());
            }break;
            case 3:{//设置
                modifyS(Root,s,e,w=getInt());
            }break;
            case 4:{//和
                ans = sum(Root,s,e);printf("%lld\n", ans);
            }break;
            case 5:{//平方和
                ans = sum2(Root,s,e);printf("%lld\n", ans);
            }break;
            case 6:{//立方和
               ans =  sum3(Root,s,e);printf("%lld\n", ans);
            }break;
            case 7:{//最大值
                ans = max(Root,s,e);printf("%lld\n", ans);
            }break;
            case 8:{//最小值
                ans = min(Root,s,e);printf("%lld\n", ans);
            }break;
            case 9:{//区间翻转
                reverse(Root,s,e);
            }break;
            case 10:{//区间循环右移，当参数小于0时，左移
                rotate(Root,s,e,w=getInt());
            }break;
            case 11:{//区间移动
                move(Root,s,e,w=getInt());
            }break;
            case 12:{//区间删除
                remove(Root,s,e);
            }break;
            case 13:{//单点插入
                insert(Root,s,w=getInt());
            }break;
            default:throw runtime_error("wrong cmd");
            }
        }

    }
    return 0;
}

void dispNode(FILE*fp,int t){
    _pushDown(t);
    fprintf(fp,"%d: Parent: %d, SN: %d, LSON: %d, RSON: %d\n",t,Node[t].parent,Node[t].sn,Node[t].son[LEFT],Node[t].son[RIGHT]);
    fprintf(fp,"    Value: %d, Sum: %lld, Size: %d, Peak: %d\n",Node[t].value,Node[t].sum,Node[t].size,Node[t].peak);
}
void _dispTree(FILE*fp,int t){
    if ( Node[t].son[LEFT] ) _dispTree(fp,Node[t].son[LEFT]);
    dispNode(fp,t);
    if ( Node[t].son[RIGHT] ) _dispTree(fp,Node[t].son[RIGHT]);
}
void dispTree(FILE*fp,int root){
    printf("Tree:\n");
    _dispTree(fp,root);
}
