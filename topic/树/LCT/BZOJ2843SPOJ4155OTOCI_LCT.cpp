/**
  bridge A B:A��B֮����һ���ߣ���A��B����ͨʱ
  penguis A X����A����ΪX
  excursion A B����A��B·���ͣ��������ͨ���impossible
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 201000;

typedef int value_t;
typedef int llt;

int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    value_t value; //��Ȩ
    llt sum;       //splay���ĺͣ���·����
    unsigned char flip;//��1λ��ʾ�����ӳ٣���0λ��ʾ��ת�ӳ�
}Node[SIZE];
int toUsed = 0;

inline int _newNode(value_t value=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    Node[toUsed].value = value;
    return toUsed;
}

inline void _pushUp(int t){
    Node[t].sum = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].sum += Node[son].sum;
    }

    if(son = Node[t].son[RIGHT]){
        Node[t].sum += Node[son].sum;
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
    return _getRoot(x) == _getRoot(y);
}
//·������
void modifyS(int y,value_t newValue){
    _access(y);
    _splay(y);

    Node[y].sum += newValue - Node[y].value;
    Node[y].value = newValue;
}

//·����ѯ��
value_t sumPath(int x,int y){
    _makeRoot(x);
    _access(y);
    _splay(y);
    return Node[y].sum;
}

int getUnsigned(){
	char ch = getchar();
	while( ch > '9' || ch < '0' ) ch = getchar();

	int ret = 0;
	do ret = ret * 10 + (int)(ch-'0');while( '0' <= (ch=getchar()) && ch <= '9' );
	return ret;
}
void dispLCT(FILE*fp, int n);
int main(){
    //freopen("1.txt","r",stdin);
    int n,q,a,b;char cmd[22];
    while(EOF!=scanf("%d",&n)){
        memset(Node,0,(n+1)*sizeof(node_t));

        for(int i=1;i<=n;++i){
            Node[i].value = Node[i].sum = getUnsigned();
        }

        q = getUnsigned();
        while(q--){
            scanf("%s",cmd);
            if('e'==*cmd){
                if(isConnect(a=getUnsigned(),b=getUnsigned()))printf("%d\n",sumPath(a,b));
                else printf("impossible\n");
            }else if('b'==*cmd){
                if(isConnect(a=getUnsigned(),b=getUnsigned()))printf("no\n");
                else printf("yes\n"),link(a,b);
            }else{
                a = getUnsigned();
                modifyS(a,getUnsigned());
            }
        }
    }
    return 0;
}
