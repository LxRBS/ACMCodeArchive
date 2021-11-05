/**
   0��n-1��n����
   ������򵽴�i�㣬�ͻ��ٺ���ki������˷�����ֱ���ɳ�ȥ
   1 i���ʴ�i��ʼ���λ�ɳ�ȥ
   2 i k����ki�ĳ�k
   ����һ�������Ȼ����i+ki��i�ĸ��ף�����1�����ʸ���i�ĳ���
   ����2����cut��link����
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 201000;


int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    int size;      //splay�����Ľڵ���������·����Ϣ
    unsigned char flip;//��1λ��ʾ�����ӳ٣���0λ��ʾ��ת�ӳ�
}Node[SIZE];
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
    if ( t && (Node[t].flip & 1) ){//���ȴ���ת
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].flip ^= 1;

        son = Node[t].son[RIGHT];
        if(son) Node[son].flip ^= 1;

        Node[t].flip ^= 1;
    }
}
//�ж�t�Ƿ�Ϊ��splay�ĸ�
inline bool _isRoot(int t){
    int p = Node[t].parent;
    return 0==p || (Node[p].son[LEFT]!=t&&Node[p].son[RIGHT]!=t);
}
//��ȡ���У�������������
inline int _getSN(int t){
    return Node[Node[t].parent].son[RIGHT] == t;
}
inline void _link(int p,int sn,int t){
    Node[Node[t].parent=p].son[sn] = t;
}
inline void _rotate(int t){
    int p = Node[t].parent;//���ڵ�
    int g = Node[p].parent;//�游�ڵ�
    int sn = _getSN(t);
    int osn = sn^1;
    //����ҪpushDown����splay��pushDown

    _link(p,sn,Node[t].son[osn]);
    Node[t].parent = g;
    if(!_isRoot(p))Node[g].son[_getSN(p)]=t;
    _link(t,osn,p);

    _pushUp(p);
}
//�Ӹ���ʼ���·��ӳٱ��
void _maintain(int t){
    if(!_isRoot(t)) _maintain(Node[t].parent);
    _pushDown(t);
}
void _splay(int t){
    _maintain(t);
    while(!_isRoot(t)){
        int p = Node[t].parent;
        if(!_isRoot(p)) _getSN(t)==_getSN(p)?_rotate(p):_rotate(t);
        _rotate(t);
    }
    _pushUp(t);
}

//�Ӹ���x�γ�һ����������
int _access(int x){
    int t = 0;
    for(;x;x=Node[t=x].parent){
        _splay(x);
        Node[x].son[RIGHT] = t;//��������
        _pushUp(x);
    }
    return t;
}
//��x��Ϊԭ���ĸ�
inline void _makeRoot(int x){
    _access(x);
    _splay(x);
    Node[x].flip ^= 1; //��ת���
}
//��ȡx�������ĸ��ڵ�
int _getRoot(int x){
    _access(x);
    _splay(x);
    while( Node[x].son[LEFT] ) x = Node[x].son[LEFT];
    _splay(x);
    return x;
}
//��child��parent���ӽڵ�
inline void link(int parent,int child){
    _makeRoot(child);
    Node[child].parent = parent;
}
//��child��parent��������
inline void cut(int parent,int child){
    _makeRoot(parent);
    _access(child);
    _splay(child);
    Node[child].son[LEFT] = Node[Node[child].son[LEFT]].parent = 0;
    _pushUp(child);
}
//��root������������£�x��y�������������
inline int lca(int root,int x,int y){
    _makeRoot(root);
    _access(x);
    return _access(y);
}
inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
}

int sizePath(int x){
    _access(x);
    _splay(x);
    return Node[x].size - 1;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
void dispLCT(FILE*fp, int n);
int main(){
    //freopen("1.txt","r",stdin);
    int k,n = getUnsigned();
    int root = n + 1;
    for(int i=1;i<=n;++i)link((k=i+getUnsigned())>n?root:k,i);
    //������
    int x,tmp,m = getUnsigned();
    while(m--){
        if(1==getUnsigned()){//��ѯ·������
            printf("%d\n",sizePath(getUnsigned()+1));
        }else{//�����ڵ�
            x = getUnsigned()+1;
            tmp = x + getUnsigned();
            cut(root,x);
            link(tmp>n?root:tmp,x);
        }
    }
    return 0;
}
