#include <cstdio>
#include <cstring>
using namespace std;

int  const SIZE = 1111111;
int const LEFT = 0;
int const RIGHT = 1;
typedef int key_t;
struct node_t{
    int parent;
    int child[2];
    int sn;
    key_t key;
    int size;
    int cnt;   //ָʾ��ͬkey�ĸ���
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = Node[t].cnt;
    int son = Node[t].child[LEFT];
    if (son) Node[t].size += Node[son].size;
    son = Node[t].child[RIGHT];
    if (son) Node[t].size += Node[son].size;
}

//����p��t�ĸ��ӹ�ϵ�����ﲻ����_pushUp(int)
inline void _link(int p,int sn,int t){
    Node[p].child[sn] = t;
    Node[t].parent = p;
    Node[t].sn = sn;
}
//��ת��������ȷ�����Ը��ӹ�ϵ������ֻά�ֽڵ�p��size
inline void _rotate(int t){
    int p = Node[t].parent;
    int sn = Node[t].sn;
    int osn = sn ^ 1;

    _link(p,sn,Node[t].child[osn]);
    _link(Node[p].parent,Node[p].sn,t);
    _link(t,osn,p);

    _pushUp(p);
}
//��չ��ֻ������չ�����ά�ֽڵ�t��size
void _splay(int t,int p,int&root){
    while( Node[t].parent != p ){
        int pp = Node[t].parent;
        if ( Node[pp].parent != p ){
            Node[pp].sn == Node[t].sn ?
                _rotate(pp) : _rotate(t);
        }
        _rotate(t);
    }
    _pushUp(t);
    if ( 0 == p ) root = t;
    return;
}

//��ȡһ���µĿ��ýڵ�
inline int _newNode(){
    ++toUsed;
    memset(Node+toUsed,0,sizeof(node_t));
    return toUsed;
}
//��root���ϲ��Ҽ�Ϊkey�Ľڵ㣬parentΪ�丸�ڵ�
int _advance(int root,int&parent,key_t key){
    if ( 0 == root ) return parent = 0;

    int t = root;
    parent = Node[t].parent;
    while( t && key != Node[t].key ){
        parent = t;
        t = key < Node[t].key ? Node[t].child[LEFT] : Node[t].child[RIGHT];
    }
    return t;
}

int _kth(int root,int kth){
    int son = Node[root].child[LEFT];
    int sz = son ? Node[son].size + 1 : 1;

    if ( kth < sz ) return _kth(son,kth);
    sz += Node[root].cnt - 1;
    if ( sz < kth ) return _kth(Node[root].child[RIGHT],kth-sz);
    return root;
}

//��ʼ��
inline void init(){
    toUsed = 0;
    memset(Node,0,sizeof(node_t));
}
//��root���ϲ���һ���ڵ�
void insert(int&root,key_t key){
    int p;
    int t = _advance(root,p,key);
    if (t){
        _splay(t,0,root);
        ++Node[t].cnt;
        ++Node[t].size;
        return;
    }

    t = _newNode();
    Node[t].key = key;
    Node[t].size = Node[t].cnt = 1;

    if ( 0 == root ){
        root = t;
        return;
    }

    int sn = key < Node[p].key ? LEFT : RIGHT;
    _link(p,sn,t);
    _splay(t,0,root);
}

//��root���ϲ��ҵ�kth������Ŵ�1��ʼ
int select(int& root,int kth){
    int t = _kth(root,kth);
    _splay(t,0,root);
    return t;
}
void dispTree(int);
int main(){
    init();
    //freopen("1.txt","w",stdout);
    int root = 0;
    int offset = 0;
    int ans = 0;

    char cmd[3];
    int k,n,lowbound;
    scanf("%d%d",&n,&lowbound);

    for(int i=0;i<n;++i){
        scanf("%s%d",cmd,&k);

        switch(*cmd){

        case 'A':{
            offset -= k;
        }break;

        case 'F':{
            int s = Node[root].size;
            if ( k > s ){
                printf("-1\n");
            }else{
                printf("%d\n",Node[select(root,s-k+1)].key-offset);
            }
        }break;

        case 'I':{
            if ( k >= lowbound ){
                insert(root,k+offset);
            }
        }break;

        case 'S':{
            offset += k;
            int kk = lowbound + offset;
            insert(root,kk);
            ans += Node[Node[root].child[LEFT]].size;
            _link(root,LEFT,0);
            if (1 == Node[root].cnt) root = Node[root].child[RIGHT],_link(0,0,root);
            else --Node[root].cnt,_pushUp(root);
        }break;

        }

        //dispTree(root);
    }

    printf("%d\n",ans);
    return 0;
}

void dispNode(int t){
    printf("Node: %d, Parent: %d, Left: %d, Right %d\n",t,Node[t].parent,Node[t].child[LEFT],Node[t].child[RIGHT]);
    printf("    Key: %d, Cnt: %d, Size: %d\n",Node[t].key,Node[t].cnt,Node[t].size);
}
void dispTreeIter(int root){
    dispNode(root);
    if (Node[root].child[LEFT])dispTreeIter(Node[root].child[LEFT]);
    if (Node[root].child[RIGHT])dispTreeIter(Node[root].child[RIGHT]);
}
void dispTree(int root){
    printf("Tree %d is:\n",root);
    if (0 == root) printf("    NULL.\n");
    else dispTreeIter(root);
}
