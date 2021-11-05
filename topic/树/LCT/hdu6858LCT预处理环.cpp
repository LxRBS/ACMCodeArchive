/**
    ��һ������ͼ��Q��ѯ��
    �ʵ�a���ߵ���b����֮������б��ܷ�ѡ��һЩ����һ����
    Ԥ����ÿ���ߣ����ڵ�i���ߣ���¼������������������ܹ��ɻ��ı�
    ���û�еĻ�����¼ΪM+1����
    Ԥ�����ʱ��ʹ�ó�ȡ����һ��ѭ�����ɽ����ÿ��ѭ��ʹ��LCT
    Ȼ�����ÿ��ѯ��O(1)�ɽ��
    ��ʱ�临�Ӷ���O(MlogN+Q)
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}


int const SIZE = 301000;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    int size;      //splay�����Ľڵ���������·����Ϣ
    unsigned char flip;//��1λ��ʾ�����ӳ٣���0λ��ʾ��ת�ӳ�
}Node[SIZE];
int toUsed = 0;

inline int _newNode(){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //Node[toUsed].value = value;
    return toUsed;
}

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

inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
}

struct edge_t{
    int from,to;
}Edge[SIZE];

int N,M,Q;
//Right[i]��ʾ��i������i����ͬһ��Ȧ�������
int Right[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        Q = getUnsigned();
        for(int a,b,i=1;i<=M;++i){
            a = getUnsigned();
            b = getUnsigned();
            if(a>b)swap(a,b);
            Edge[i].from = a;
            Edge[i].to = b;
        }

        //Ԥ����Right
        int k = 1, t = 1;
        while(t<=M){
            if(k<=M && !isConnect(Edge[k].from,Edge[k].to)){
                link(Edge[k].from,Edge[k].to);
                ++k;
            }else{//��k������ǰ���t���γ�Ȧ
                cut(Edge[t].from,Edge[t].to);
                Right[t++] = k;
            }
        }

        int lastans = 0;
        for(int a,b,i=1;i<=Q;++i){
            a = (getUnsigned()^lastans)%M+1;
            b = (getUnsigned()^lastans)%M+1;
            if(a>b) swap(a,b);
            puts((lastans=(b>=Right[a]))?"Yes":"No");
        }
    }
    return 0;
}
