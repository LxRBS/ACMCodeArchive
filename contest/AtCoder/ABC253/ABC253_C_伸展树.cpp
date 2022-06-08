/**
 * multiset�����ֲ��������룬multiɾ������ѯ
 * ��STLmultiset�������
 * ��������չ�� 
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
    int size;   // size�򣬱������Ľڵ�����
    int key;    // ����ļ�
    int cnt;    // ��ͬ��ֵ������
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = Node[t].cnt;
    int son = Node[t].son[LEFT];
    if(son) Node[t].size += Node[son].size;
    son = Node[t].son[RIGHT];
    if(son) Node[t].size += Node[son].size;
}
/// ����һ���½ڵ�
inline int _newNode(int key){
    memset(Node+(++toUsed), 0, sizeof(_t));
    /// �������ùܣ��ڸ��Ժ����д���
    Node[toUsed].key = key;
    return toUsed;
}
/// p��sn��������Ϊson
inline void _link(int p, int sn, int son){
    Node[Node[p].son[Node[son].sn = sn] = son].parent = p;    
}

/// ��תt��t����������
inline void _rotate(int t){
    int p = Node[t].parent;
    int sn = Node[t].sn;
    int osn = sn ^ 1;
    /// ����ȷ�����Ը��ӹ�ϵ
    _link(p, sn, Node[t].son[osn]);
    _link(Node[p].parent, Node[p].sn, t);
    _link(t, osn, p);
    /// ֻά��p���ɣ�t���ά��
    _pushUp(p);
}
/// ��root���ϣ���t��չΪp�Ķ��ӣ�pΪ0��t��չΪ����
void _splay(int & root, int p, int t){
    int pp;
    while((pp = Node[t].parent) != p){
        if(Node[pp].parent != p) Node[pp].sn == Node[t].sn ? _rotate(pp) : _rotate(t);
        _rotate(t);
    }
    _pushUp(t); // ���ά��t
    if(0 == p) root = t; // �ĸ�
}

/// ��root�����Ҽ�ֵΪkey�Ľڵ㣬����Ҳ����򷵻�0����p��Ӧ����λ�õĸ��ڵ�
int _advance(int root, int & p, int key){
    int t = root;
    while(t && Node[t].key != key){
        p = t;
        t = Node[t].son[key < Node[t].key ? LEFT : RIGHT];
    }
    return t;
}

/// ��t�������ҵ�k��Ԫ�أ�k��1��ʼ
int _kth(int t, int k){
    int son = Node[t].son[LEFT];
    int s = son ? Node[son].size : 0;
    if(k <= s) return _kth(Node[t].son[LEFT], k);
    if(s + Node[t].cnt < k) return _kth(Node[t].son[RIGHT], k - s - Node[t].cnt);
    return t;
}

/// ��root���ϲ���key�����ز����Ժ�keyֵ������
int insert(int & root, int key){
    int p;
    int t = _advance(root, p, key);
    if(0 == t){ // ˵��ԭ��û��key�ڵ�
        t = _newNode(key);
        _link(p, key < Node[p].key ? LEFT : RIGHT, t);
    }
    ++Node[t].cnt;
    _splay(root, 0, t);
    return Node[t].cnt;
}
/// ��root����ɾ��cnt��key��cnt�������������࣬��ɾ�⼴��
void remove(int & root, int key, int cnt){
    int p;
    int t = _advance(root, p, key);    
    if(0 == t) return; // ������û��key

    /// ��t��Ϊ����
    _splay(root, 0, t);
    if(Node[t].cnt > cnt){
        Node[t].cnt -= cnt;
        Node[t].size -= cnt;
        return;
    }

    /// ��ʱҪȷʵɾ���ýڵ㣬�����ҵ�����ӣ������ڱ��Ĵ棬�����һ������
    int son = Node[t].son[LEFT];
    /// �ҵ�����ӵ����㽫���Ϊ�����Ķ���
    int tt = _kth(son, Node[son].size);
    _splay(t, t, tt);
    /// ��ʱ�����û���Ҷ��ӣ����Ҷ��ӹҵ�����ӵ��Ҷ��Ӽ���
    _link(tt, RIGHT, Node[t].son[RIGHT]);
    _pushUp(tt);
    Node[root = tt].parent = 0;
    return;
}

/// ��root���ϲ���������k�Ľڵ㣬k��1��ʼ
int kth(int & root, int k){
    /// ע�����ڱ��Ĵ��ڣ�����֮��Ҫ��1
    int t = _kth(root, k+1);
    _splay(root, 0, t);
    return t;
}

/// root������Сֵ
inline int min(int & root){
    return Node[kth(root, 1)].key;
}
/// root�������ֵ
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
    
    /// �ȳ�ʼ��
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
