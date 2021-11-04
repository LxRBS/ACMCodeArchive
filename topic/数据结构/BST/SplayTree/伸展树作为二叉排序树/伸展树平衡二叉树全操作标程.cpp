/**
   平衡二叉排序树，用伸展树，允许重复的键值
   支持插入、删除、rank、kth、max、min、前驱、后继
   以及成段插入与成段删除
   每个树均会塞两个哨兵：负无穷大和正无穷大
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef int key_t;
int const SIZE = 1001000;
int const LEFT = 0;
int const RIGHT = 1;
int const NEG_INF = -2100000000;
int const POS_INF = 2100000000;

struct node_t{
    int parent;//父节点
    int son[2];//子节点
    int sn;    //本节点的排行
    int size;  //size域，本节点子树的节点数量，用于排名
    int cnt;   //本节点键值的数量
    key_t key; //键值
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = Node[t].cnt;
    int son = Node[t].son[LEFT];
    if(son) Node[t].size += Node[son].size;
    son = Node[t].son[RIGHT];
    if(son) Node[t].size += Node[son].size;
}
//分配一个新节点
inline int _newNode(key_t key=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //其他域不用管，在各自函数中处理
    Node[toUsed].key = key;
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
//在root树上查找key，如果找不到则返回0同时p保存应插入位置的父节点
//root不为空
int _advance(int root,int&p,key_t const&key){
    int t = root;
    while( t && Node[t].key != key ){
        p = t;
        t = Node[t].son[key<Node[t].key?LEFT:RIGHT];
    }
    return t;
}
//在t子树上查找第k个元素，从1开始，重复的键值也要计算排名，参数一定合法
int _kth(int t,int k){
    int son = Node[t].son[LEFT];
    int s = son?Node[son].size:0;
    //去左子树找
    if(k<=s) return _kth(Node[t].son[LEFT],k);
    //去右子树找
    if(s+Node[t].cnt<k) return _kth(Node[t].son[RIGHT],k-s-Node[t].cnt);
    return t;//就在本节点上
}
//判断root树是否为空
inline bool isEmpty(int root){
    return Node[root].size > 2;
}
//返回root树的尺寸
inline int size(int root){
    return Node[root].size - 2;
}
//在root树上插入key
int insert(int&root,key_t const&key){
    int p;
    int t = _advance(root,p,key);

    if(0==t){//找不到
        t = _newNode(key);
        _link(p,key<Node[p].key?LEFT:RIGHT,t);
    }
    ++Node[t].cnt;
    _splay(root,0,t);//splay中包含了pushUp操作
    return Node[t].cnt;
}
//在root树上删除key
int remove(int&root,key_t const&key){
    int p;
    int t = _advance(root,p,key);
    if(0==t) return -7;//root中不含key

    _splay(root,0,t);
    //如果删除以后还有剩下的，直接返回即可
    if( --Node[t].cnt > 0 ){
        --Node[t].size;//无需pushUp操作
        return Node[t].cnt;
    }

    //否则表示当前节点应该从树中剔除
    int son = Node[t].son[LEFT];//左儿子一定存在
    //找到左儿子中最大的节点，将其变为树根的左儿子
    int tt = _kth(son,Node[son].size);
    _splay(t,t,tt);
    //此时左儿子没有右儿子，将根的右儿子挂上去即可
    _link(tt,RIGHT,Node[t].son[RIGHT]);
    _pushUp(tt);
    return Node[root=tt].parent = 0;//一定要设置为0，这是根的标记
}

//在root树上找key的前驱，返回的是节点，key不一定存在于树上
//因为哨兵的存在，所以一定有前驱
int pred(int&root,key_t const&key){
    int p,son;
    int t = _advance(root,p,key);
    if(t){//如果存在，在左子树中找到最大的节点即可
        _splay(root,0,t);
        son = Node[t].son[LEFT];//左儿子一定存在
        t = _kth(son,Node[son].size);//左儿子中最大的
        return t;
    }
    //否则根据p来寻找
    _splay(root,0,p);
    if(Node[p].key<key) return p;
    son = Node[p].son[LEFT];
    t = _kth(son,Node[son].size);//左儿子中最大的
    return t;
}
//在root树上找key的后继，返回的是节点，key不一定存在于树上
//因为哨兵的存在，所以一定有后继
int succ(int&root,key_t const&key){
    int p, son;
    int t = _advance(root,p,key);
    if(t){//如果存在，在右子树中找到最小的节点即可
        _splay(root,0,t);
        son = Node[t].son[RIGHT];//右儿子一定存在
        t = _kth(son,1);//右儿子中最小的
        return t;
    }
    //否则根据p来寻找
    _splay(root,0,p);
    if(key<Node[p].key) return p;
    son = Node[p].son[RIGHT];
    t = _kth(son,1);//右儿子中最小的
    return t;
}
//在root树上找最小值，返回的是节点
inline int min(int&root){
    return succ(root, NEG_INF);//返回负无穷大的后继
}
//在root树上找最大值，返回的是节点
inline int max(int&root){
    return pred(root, POS_INF);//返回正无穷大的前驱
}
//在root树上查询key的排名，key不一定存在于树上
int rank(int&root,key_t const&key){
    int p,son;
    int t = _advance(root,p,key);
    if(t){//如果key存在，直接返回左儿子的size，不要加1，因为有哨兵
        _splay(root,0,t);
        son = Node[t].son[LEFT];//左儿子一定存在
        return Node[son].size;
    }

    _splay(root,0,p);
    if ( key < Node[p].key ){
        son = Node[p].son[LEFT];//左儿子一定存在
        return Node[son].size;
    }
    //找右儿子的最小，能到此处则右儿子一定存在
    t = _kth(Node[p].son[RIGHT],1);
    _splay(root,0,t);
    return Node[Node[t].son[LEFT]].size;//左儿子一定存在
}
//在root树上查找排名第k的节点，k从1开始
int kth(int&root,int k){
    //如果k非法，注意size返回的是减去哨兵以后的size
    if ( k <= 0 || k > size(root) ) return 0;
    int t = _kth(root,k+1);
    _splay(root,0,t);
    return t;
}
//交换root1树上与root2树上[start,end]之间的数
int swap(int&root1,int&root2,int start,int end){
    if(root1==root2) return 0;

    int s1 = pred(root1,start);//start的前驱
    int e1 = succ(root1,end);//end的后继
    _splay(root1,0,s1);//必须先找在伸展
    _splay(root1,root1,e1);

    int s2 = pred(root2,start);//start的前驱
    int e2 = succ(root2,end);//end的后继
    _splay(root2,0,s2);
    _splay(root2,root2,e2);

    int son1 = Node[e1].son[LEFT], son2 = Node[e2].son[LEFT];
    _link(e1,LEFT,son2);_pushUp(e1);_pushUp(root1);
    _link(e2,LEFT,son1);_pushUp(e2);_pushUp(root2);//必须pushUp
    //son中肯定不包含哨兵
    return ( son1 ? Node[son1].size : 0 ) + ( son2 ? Node[son2].size : 0 );
}
//用于判断返回的节点编号是否合法
inline bool isValid(int t){
    return t && NEG_INF != Node[t].key && POS_INF != Node[t].key;
}

int Root[21];//一共20个树
//初始森林
void initTrees(int n){
    toUsed = 0;
    for(int i=1;i<=n;++i){
        Root[i] = _newNode(NEG_INF);
        Node[Root[i]].cnt = Node[Root[i]].size = 1;
        insert(Root[i], POS_INF);
    }
}

void dispTree(FILE*,int);
int main(){
    //freopen("H:\\PProject\\acmt\\1.std.in","r",stdin);
    //freopen("1.txt","w",stdout);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        initTrees(20);//初始化

        int cmd,idx,idx2,val,val2,tmp,ans1=0,ans2=0,n = getUnsigned();//指令数量
        for(int cmdi=1;cmdi<=n;++cmdi){
            cmd = getUnsigned();
            idx = getUnsigned();
            if(cmd < 7){
                val = getUnsigned();
            }else if(7 == cmd){
                idx2 = getUnsigned();
                val = getUnsigned();
                val2 = getUnsigned();
                if(val>val2)swap(val,val2);
            }

            switch(cmd){
                case 1:tmp=insert(Root[idx],val);break;
                case 2:tmp=remove(Root[idx],val);break;
                case 3:tmp=rank(Root[idx],val);break;
                case 4:isValid(tmp=kth(Root[idx],val))?(tmp=Node[tmp].key):(tmp=-13);break;
                case 5:isValid(tmp=pred(Root[idx],val))?(tmp=Node[tmp].key):(tmp=-17);break;
                case 6:isValid(tmp=succ(Root[idx],val))?(tmp=Node[tmp].key):(tmp=-19);break;
                case 7:tmp=swap(Root[idx],Root[idx2],val,val2);break;
                case 8:isValid(tmp=min(Root[idx]))?(tmp=Node[tmp].key):(tmp=-29);break;
                case 9:isValid(tmp=max(Root[idx]))?(tmp=Node[tmp].key):(tmp=-31);break;
                default:throw runtime_error("错误的cmd");
            }
            //printf("%d %d\n",cmdi,tmp);
            tmp < 0 ? ans1 += tmp : ans2 ^= tmp;
        }
        printf("Case %d:\n%d\n%d\n",kase,ans1,ans2);
    }
    return 0;
}

void dispNode(FILE*fp,int t){
    fprintf(fp,"%d: Parent: %d, SN: %d, LSON: %d, RSON: %d\n",t,Node[t].parent,Node[t].sn,Node[t].son[LEFT],Node[t].son[RIGHT]);
    fprintf(fp,"    Key: %d, Cnt: %d, Size, %d\n",Node[t].key,Node[t].cnt,Node[t].size);
}
void _dispTree(FILE*fp,int t){
    dispNode(fp,t);
    if ( Node[t].son[LEFT] ) _dispTree(fp,Node[t].son[LEFT]);
    if ( Node[t].son[RIGHT] ) _dispTree(fp,Node[t].son[RIGHT]);
}
void dispTree(FILE*fp,int root){
    printf("Tree:\n");
    _dispTree(fp,root);
}
