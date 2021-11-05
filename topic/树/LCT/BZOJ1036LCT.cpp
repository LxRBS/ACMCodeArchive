/**
  CHANGE u t���ѽڵ�uȨֵ�ĳ�t
  QMAX u v����ѯuv·�����ֵ
  QSUM u v����ѯuv·����
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 201000;

typedef int value_t;

int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    value_t value; //��Ȩ
    value_t peak;  //splay���������ֵ����¼·�����ֵ
    value_t sum;       //splay���ĺͣ���·����
    unsigned char flip;//��1λ��ʾ�����ӳ٣���0λ��ʾ��ת�ӳ�
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].sum = Node[t].value;
    Node[t].peak = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].sum += Node[son].sum;
        Node[t].peak = max(Node[t].peak,Node[son].peak);
    }

    if(son = Node[t].son[RIGHT]){
        Node[t].sum += Node[son].sum;
        Node[t].peak = max(Node[t].peak,Node[son].peak);
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

inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
}
//��������
void modifyS(int x,value_t newValue){
    _access(x);
    _splay(x);
    Node[x].value = newValue;
    _pushUp(x);
}
//·����ѯ����ֵ
value_t maxPath(int x,int y){
    _makeRoot(x);
    _access(y);
    _splay(y);
    return Node[y].peak;
}
//·����ѯ��
value_t sumPath(int x,int y){
    _makeRoot(x);
    _access(y);
    _splay(y);
    return Node[y].sum;
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}
void dispLCT(FILE*fp, int n);
int A[SIZE],B[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    for(int i=1;i<n;++i)A[i]=getInt(),B[i]=getInt();
    for(int i=1;i<=n;++i)Node[i].value = Node[i].peak = Node[i].sum = getInt();
    for(int i=1;i<n;++i)link(A[i],B[i]);
    //������
    int a, m = getInt();
    char cmd[16];
    while(m--){
        scanf("%s",cmd);
        a = getInt();
        if('Q'==*cmd){
            printf("%d\n",'M'==*(cmd+1)?maxPath(a,getInt()):sumPath(a,getInt()));
        }else{
            modifyS(a,getInt());
        }
    }
    return 0;
}
