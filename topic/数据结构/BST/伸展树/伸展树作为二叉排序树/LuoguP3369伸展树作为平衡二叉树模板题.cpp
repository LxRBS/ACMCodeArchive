#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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

using llt = long long;
using vll = vector<llt>;
using vvll = vector<vll>;
using v3ll = vector<vvll>;
using si = set<int>;

struct SplayBBT{ // 伸展树作为平衡二叉树

using key_t = int; 

enum{LEFT=0, RIGHT=1};
enum{INF=INT32_MAX};  // 注意要与key_t匹配

struct node_t{
    int parent;//父节点
    int son[2];//子节点
    int sn;    //本节点的排行
    int size;  //size域，本节点子树的节点数量，用于排名
    int cnt;   //本节点键值的数量，允许有重复的键
    key_t key; //键值
    node_t(){memset(this, 0, sizeof(node_t));}
};

int root;
vector<node_t> data;

/// 初始化，传入可能的最大的节点数量
/// 会插入2个哨兵
void init(int possible_capacity){
    this->root = 0;
    this->data.clear();
    this->data.reserve(possible_capacity);
    this->data.push_back(node_t());
    /// 插入哨兵
    auto & d = this->data[this->root = this->_new(-INF)];
    d.size = d.cnt = 1;
    this->insert(INF);
}

void _pushUp(int t){
    auto & s = data[t].size;
    s = data[t].cnt;
    int son = data[t].son[LEFT];
    if(son) s += data[son].size;
    son = data[t].son[RIGHT];
    if(son) s += data[son].size;
}

/// 用k做一个新节点
int _new(const key_t & k){
    this->data.push_back(node_t());
    this->data.back().key = k; // 其他域均不管
    return this->data.size() - 1;
}

/// 将parent的sn儿子设置为son
void _link(int parent, int sn, int son){
    data[son].parent = parent;
    data[son].sn = sn;
    data[parent].son[sn] = son;
}

/// 旋转节点t，t不能是树根
void _rotate(int t){
    int p = data[t].parent;
    int sn = data[t].sn;
    int osn = sn ^ 1;
    //重新确定三对父子关系
    this->_link(p,sn,data[t].son[osn]);
    this->_link(data[p].parent,data[p].sn,t);
    this->_link(t,osn,p);
    //只维护p即可，t暂时不维护
    this->_pushUp(p);
}

/// 将t伸展为p的儿子,p为0则伸展为树根
void _splay(int p, int t){
    int pp;
    while( (pp=data[t].parent) != p ){
        if(data[pp].parent!=p) data[pp].sn==data[t].sn?this->_rotate(pp):this->_rotate(t);
        this->_rotate(t);
    }
    this->_pushUp(t);//最后维护t
    if(0==p) this->root = t;//改根
}

/// 查找key，返回找到的节点
/// 如果找不到返回0，且p保存节点，该节点表示如果要插入key，则应该作为p的儿子
int _advance(int&p,key_t const&key){
    int t = this->root;
    while(t && data[t].key != key){
        p = t;
        t = data[t].son[key<data[t].key?LEFT:RIGHT];
    }
    return t;
}

/// 在t子树上查找第k个元素，从0开始，重复的键值也要计算排名，参数一定合法
int _kth(int t, int k){
    // int son = data[t].son[LEFT];
    // int s = son ? data[son].size : 0;
    // //去左子树找
    // if(k < s) return this->_kth(son, k);
    // //去右子树找
    // if(s + data[t].cnt <= k) return this->_kth(data[t].son[RIGHT], k - s - data[t].cnt);
    // return t;//就在本节点上
	/// 原来用的递归，但是在LuoguP6136的某两个点会T
    /// 改成循环仍然会T，直到加了splay才通过。
	while(1){
		auto son = data[t].son[LEFT];
		auto s = son ? data[son].size : 0;
		if(k < s) t = son;
		else if(s + data[t].cnt <= k) k -= s + data[t].cnt, t = data[t].son[RIGHT];
		else {_splay(0, t); return t;}
	}
	assert(0);
	return -1000000;
}

/// 树的节点数量，注意要减去哨兵，注意不要用data.size()
int size()const{return this->data[this->root].size - 2;}

/// 插入key，返回插入后key的数量
int insert(const key_t & key){
    int p;
    int t = this->_advance(p, key);

    if(0 == t){//找不到
        t = this->_new(key);
        this->_link(p,key<data[p].key?LEFT:RIGHT,t);
    }
    ++data[t].cnt;
    this->_splay(0, t);//splay中包含了pushUp操作
    return data[t].cnt;    
}

/// 删除key，只删除1个
/// 返回删除后key的数量
/// 如果本来就没有key，直接返回0
int erase(const key_t & key){
    int p;
    int t = this->_advance(p, key);
    if( 0 == t) return 0; // 树中不含key

    this->_splay(0, t);
    //如果删除以后还有剩下的，直接返回即可
    if( --data[t].cnt > 0 ){
        --data[t].size;//无需pushUp操作
        return data[t].cnt;
    }    

    //否则表示当前节点应该从树中剔除
    int son = data[t].son[LEFT];//因为有哨兵左儿子一定存在
    //找到左儿子中最大的节点，将其变为树根的左儿子
    int tt = this->_kth(son, data[son].size - 1);
    this->_splay(t, tt);
    //此时左儿子没有右儿子，将根的右儿子挂上去即可
    this->_link(tt,RIGHT,data[t].son[RIGHT]);
    this->_pushUp(tt);
    return data[this->root=tt].parent = 0;//一定要设置为0，这是根的标记    
}

/// 找key的前驱，即比key小的最大的数，因为有哨兵，前驱一定存在
/// key本身不一定存在于树中
const node_t & pred(key_t const & key){
    int p,son;
    int t = this->_advance(p, key);
    if(t){//如果存在，在左子树中找到最大的节点即可
        this->_splay(0, t);
        son = data[t].son[LEFT];//左儿子一定存在
        t = this->_kth(son, data[son].size - 1);//左儿子中最大的
        return data[t];
    }
    //否则根据p来寻找
	this->_splay(0, p); // 要splay，不能直接return
    if(data[p].key < key) return data[p];
       
    son = data[p].son[LEFT];
    t = this->_kth(son, data[son].size - 1);//左儿子中最大的
    return data[t];
}

/// 找key的后继，即比key大的最小的数，因为有哨兵，一定存在
/// key本身不一定在树中
const node_t & succ(key_t const & key){
    int p, son;
    int t = this->_advance(p, key);
    if(t){//如果存在，在右子树中找到最小的节点即可
        this->_splay(0, t);
        son = data[t].son[RIGHT];//右儿子一定存在
        t = this->_kth(son, 0);//右儿子中最小的
        return data[t];
    }
    //否则根据p来寻找
	this->_splay(0, p); // 要splay，不能直接return
    if(key < data[p].key) return data[p];    
       
    son = data[p].son[RIGHT];
    t = this->_kth(son, 0);//右儿子中最小的
    return data[t];
}

/// 返回最小key所在的节点
const node_t & min(){return this->succ(-INF);}

/// 返回最大key所在的节点
const node_t & max(){return this->pred(INF);}

/// 查询key在树中的排名，最小值排名为1
/// key本身不一定存在于树中
int rank(const key_t & key){
    int p, son;
    int t = this->_advance(p, key);
    if(t){ // 如果key存在，直接返回左儿子的size，不要加1，因为有哨兵
        this->_splay(0, t);
        son = data[t].son[LEFT];//左儿子一定存在
        return data[son].size;
    }

    this->_splay(0, p);
    if (key < data[p].key){
        son = data[p].son[LEFT];//左儿子一定存在
        return data[son].size;
    }

    /// 找右儿子的最小，能到此处则右儿子一定存在
    t = this->_kth(data[p].son[RIGHT], 0);
    this->_splay(0, t);
    return data[data[t].son[LEFT]].size;//左儿子一定存在    
}

/// 返回排名第sn的key
const node_t & select(int sn){
    assert(1 <= sn && sn <= this->size());
    /// 因为有哨兵，直接用sn即可
    int t = this->_kth(this->root, sn);
    this->_splay(0, t);
    return data[t];
}

}Tree;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int q = getInt();
    Tree.init(q);
    while(q--){
        int cmd = getInt();
        switch(cmd){
            case 1:Tree.insert(getInt());break;
            case 2:Tree.erase(getInt());break;
            case 3:printf("%d\n", Tree.rank(getInt()));break;
            case 4:printf("%d\n", Tree.select(getInt()).key);break;
            case 5:printf("%d\n", Tree.pred(getInt()).key);break;
            case 6:printf("%d\n", Tree.succ(getInt()).key);break;
            default:assert(0);
        }
    }
    return 0;
}
