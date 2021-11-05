/**
  1 a b����ѯ·��ab������Ӷκ�
  2 a b c��·��abȫ���ĳ�c
*/
#include <bits/stdc++.h>
using namespace std;

inline int max(int a,int b,int c){return max(max(a,b),c);}

int const SIZE = 201000;

typedef int value_t;


int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    int size;
    value_t value; //��Ȩ
    value_t sum;
    value_t left,ans,right;//�����Ӷκͣ���Ӷκ�
    value_t lazys;
    unsigned char flip;//��1λ��ʾ�����ӳ٣���0λ��ʾ��ת�ӳ�
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].sum=Node[t].left=Node[t].right=Node[t].ans=Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].ans = max(Node[t].ans,Node[son].ans,Node[son].right+Node[t].left);
        Node[t].left = max(Node[son].left,Node[son].sum+Node[t].left);
        Node[t].right = max(Node[t].right,Node[t].sum+Node[son].right);
        Node[t].sum += Node[son].sum;
    }

    if(son = Node[t].son[RIGHT]){
        Node[t].size += Node[son].size;
        Node[t].ans = max(Node[t].ans,Node[son].ans,Node[t].right+Node[son].left);
        Node[t].left = max(Node[t].left,Node[t].sum+Node[son].left);
        Node[t].right = max(Node[son].right,Node[son].sum+Node[t].right);
        Node[t].sum += Node[son].sum;
    }
}

inline void _pushDown(int t){
    if ( t && (Node[t].flip & 1) ){//���ȴ���ת
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].flip ^= 1,swap(Node[son].left,Node[son].right);

        son = Node[t].son[RIGHT];
        if(son) Node[son].flip ^= 1,swap(Node[son].left,Node[son].right);

        Node[t].flip ^= 1;
    }
    if ( t && (Node[t].flip & 2) ){//�ٴ���set
        value_t& lazy = Node[t].lazys;

        int son = Node[t].son[LEFT];
        if(son){
            Node[son].flip |= 2;//��set�ӳٱ��
            Node[son].value = Node[son].lazys = lazy;
            Node[son].sum = Node[son].size * lazy;
            Node[son].left = Node[son].right = Node[son].ans = lazy > 0 ? Node[son].sum : 0;
        }

        if(son = Node[t].son[RIGHT]){
            Node[son].flip |= 2;//��set�ӳٱ��
            Node[son].value = Node[son].lazys = lazy;
            Node[son].sum = Node[son].size * lazy;
            Node[son].left = Node[son].right = Node[son].ans = lazy > 0 ? Node[son].sum : 0;
        }

        Node[t].flip ^= 2;//���set���
        lazy = 0; //��һ������ν
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
    swap(Node[x].left,Node[x].right);
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


//·������
void modifyS(int x,int y,value_t newValue){
    _makeRoot(x);
    _access(y);
    _splay(y);

    Node[y].value = Node[y].lazys = newValue;
    Node[y].sum = Node[y].size * newValue;
    Node[y].left = Node[y].ans = Node[y].right = newValue>0?Node[y].sum:0;
    Node[y].flip |= 2;
}
//����Ӷκ�
value_t maxPath(int x,int y){
    _makeRoot(x);
    _access(y);
    _splay(y);
    return Node[y].ans;
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
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    for(int i=1;i<=n;++i)Node[i].value=Node[i].left=Node[i].ans=Node[i].right=Node[i].sum=getInt();
    for(int i=1;i<n;++i)link(getInt(),getInt());
    //������
    int tmp,cmd,a,b,q = getInt();
    while(q--){
        cmd = getInt();
        a = getInt();
        if(1==cmd){
            printf("%d\n",(tmp=maxPath(a,getInt()))>0?tmp:0);
        }else{
            b = getInt();
            modifyS(a,b,getInt());
        }
    }
    return 0;
}
