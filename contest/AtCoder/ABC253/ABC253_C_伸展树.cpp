/**
 * multiset，三种操作：插入，multi删除，查询
 * 用STLmultiset就能完成
 * 这里用伸展树 
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2e5+5;
#endif  

int const LEFT = 0;
int const RIGHT = 1;

int const NEG_INF = -2E9;
int const POS_INF = +2E9;

struct _t{
    int parent;
    int son[2];
    int sn;
    int size;   // size域，本子树的节点数量
    int key;    // 排序的键
    int cnt;    // 相同键值的数量
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = Node[t].cnt;
    int son = Node[t].son[LEFT];
    if(son) Node[t].size += Node[son].size;
    son = Node[t].son[RIGHT];
    if(son) Node[t].size += Node[son].size;
}
/// 分配一个新节点
inline int _newNode(int key){
    memset(Node+(++toUsed), 0, sizeof(_t));
    /// 其他域不用管，在各自函数中处理
    Node[toUsed].key = key;
    return toUsed;
}
/// p的sn儿子设置为son
inline void _link(int p, int sn, int son){
    Node[Node[p].son[Node[son].sn = sn] = son].parent = p;    
}

/// 旋转t，t不能是树根
inline void _rotate(int t){
    int p = Node[t].parent;
    int sn = Node[t].sn;
    int osn = sn ^ 1;
    /// 重新确定三对父子关系
    _link(p, sn, Node[t].son[osn]);
    _link(Node[p].parent, Node[p].sn, t);
    _link(t, osn, p);
    /// 只维护p即可，t最后维护
    _pushUp(p);
}
/// 在root树上，将t伸展为p的儿子，p为0则将t伸展为树根
void _splay(int & root, int p, int t){
    int pp;
    while((pp = Node[t].parent) != p){
        if(Node[pp].parent != p) Node[pp].sn == Node[t].sn ? _rotate(pp) : _rotate(t);
        _rotate(t);
    }
    _pushUp(t); // 最后维护t
    if(0 == p) root = t; // 改根
}

/// 在root树上找键值为key的节点，如果找不到则返回0，且p是应插入位置的父节点
int _advance(int root, int & p, int key){
    int t = root;
    while(t && Node[t].key != key){
        p = t;
        t = Node[t].son[key < Node[t].key ? LEFT : RIGHT];
    }
    return t;
}

/// 在t子树上找第k个元素，k从1开始
int _kth(int t, int k){
    int son = Node[t].son[LEFT];
    int s = son ? Node[son].size : 0;
    if(k <= s) return _kth(Node[t].son[LEFT], k);
    if(s + Node[t].cnt < k) return _kth(Node[t].son[RIGHT], k - s - Node[t].cnt);
    return t;
}

/// 在root树上插入key，返回插入以后key值的数量
int insert(int & root, int key){
    int p;
    int t = _advance(root, p, key);
    if(0 == t){ // 说明原来没有key节点
        t = _newNode(key);
        _link(p, key < Node[p].key ? LEFT : RIGHT, t);
    }
    ++Node[t].cnt;
    _splay(root, 0, t);
    return Node[t].cnt;
}
/// 在root树上删除cnt个key，cnt比现有数量还多，则删光即可
void remove(int & root, int key, int cnt){
    int p;
    int t = _advance(root, p, key);    
    if(0 == t) return; // 本来就没有key

    /// 将t变为树根
    _splay(root, 0, t);
    if(Node[t].cnt > cnt){
        Node[t].cnt -= cnt;
        Node[t].size -= cnt;
        return;
    }

    /// 此时要确实删除该节点，首先找到左儿子，由于哨兵的存，左儿子一定存在
    int son = Node[t].son[LEFT];
    /// 找到左儿子的最大点将其变为树根的儿子
    int tt = _kth(son, Node[son].size);
    _splay(t, t, tt);
    /// 此时左儿子没有右儿子，将右儿子挂到左儿子的右儿子即可
    _link(tt, RIGHT, Node[t].son[RIGHT]);
    _pushUp(tt);
    Node[root = tt].parent = 0;
    return;
}

/// 在root树上查找排名第k的节点，k从1开始
int kth(int & root, int k){
    /// 注意有哨兵的存在，所以之类要加1
    int t = _kth(root, k+1);
    _splay(root, 0, t);
    return t;
}

/// root树上最小值
inline int min(int & root){
    return Node[kth(root, 1)].key;
}
/// root树上最大值
inline int max(int & root){
    return Node[kth(root, Node[root].size-2)].key;
}

void initTree(int & root){
    toUsed = 0;
    root = _newNode(NEG_INF);
    Node[root].cnt = Node[root].size = 1;
    insert(root, POS_INF);
}

int Q, Root = 0;
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    /// 先初始化
    initTree(Root);

    cin >> Q;
    for(int op,x,c,q=1;q<=Q;++q){
        cin>>op;
        if(1 == op){
            cin >> x;
            insert(Root, x);
        }else if(2 == op){ 
            cin >> x >> c;
            remove(Root, x, c);
        }else{
            cout<<(max(Root) - min(Root))<<endl;
        }
    }
    return 0;
}
