/**
    һ�����У���ʼΪ�գ����ֲ���
    Q L����ѯĩβL����������
    A n������һ�εĴ𰸼�n���뵽ĩβ
*/
#include <bits/stdc++.h>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef int value_t;

int const SIZE = 200100;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;//���ڵ�
    int son[2];//�ӽڵ�
    int sn;    //���ڵ������
    int size;  //size��
    value_t value; //ֵ
    value_t peak;  //���ֵ
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].peak = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].peak = max(Node[t].peak,Node[son].peak);
    }
    son = Node[t].son[RIGHT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].peak = max(Node[t].peak,Node[son].peak);
    }
}
//����һ���½ڵ�
inline int _newNode(value_t value=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //�������ùܣ��ڸ��Ժ����д���
    Node[toUsed].value = value;
    return toUsed;
}
//��parent��sn��������Ϊson
inline void _link(int parent,int sn,int son){
    Node[son].parent = parent;
    Node[son].sn = sn;
    Node[parent].son[sn] = son;
}
//��ת����,t����������
void _rotate(int t){
    int p = Node[t].parent;
    int sn = Node[t].sn;
    int osn = sn ^ 1;
    //�����֤splay����kth���ã�����ҪpushDown
    //����ȷ�����Ը��ӹ�ϵ
    _link(p,sn,Node[t].son[osn]);
    _link(Node[p].parent,Node[p].sn,t);
    _link(t,osn,p);
    //ֻά��p���ɣ�t��ʱ��ά��
    _pushUp(p);
}
//��root���У���t��չΪp�Ķ���,pΪ0����չΪ����
void _splay(int&root,int p,int t){
    int pp;
    while( (pp=Node[t].parent) != p ){
        if(Node[pp].parent!=p) Node[pp].sn==Node[t].sn?_rotate(pp):_rotate(t);
        _rotate(t);
    }
    _pushUp(t);//���ά��t
    if(0==p) root = t;//�ĸ�
}

//��t�����ϲ��ҵ�k��Ԫ�أ���0��ʼ������һ���Ϸ�
int _kth(int t,int k){
    int son = Node[t].son[LEFT];
    int s = son?Node[son].size:0;
    if(k<s) return _kth(son,k);//ȥ��������
    return s < k ? _kth(Node[t].son[RIGHT],k-s-1) : t;
}

//�ڵ�posλ�ò���һ��ֵvalue������һ���Ϸ���pos��1��ʼ
void insert(int&root,int pos,value_t const&value){
    int t = _kth(root,pos-1);
    _splay(root,0,t);//��pos-1��������
    int tt = _kth(root,pos);
    _splay(root,root,tt);//��pos���������Ҷ���
    //���½ڵ�ҵ������Ҷ��ӵ������
    t = _newNode(value);
    Node[t].peak = value;
    Node[t].size = 1;
    _link(tt,LEFT,t);
    _pushUp(tt);_pushUp(root);
}

value_t max(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].peak;
}
void build(int&t,int parent,int sn,int s,int e){
    int mid = ( s + e ) >> 1;

    t = _newNode(mid);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) build(Node[t].son[LEFT],t,LEFT,s,mid-1);
    if ( mid < e ) build(Node[t].son[RIGHT],t,RIGHT,mid+1,e);

    _pushUp(t);
}
inline int size(int root){
    return Node[root].size - 2;
}

int Root;

int main(){
    //freopen("1.txt","r",stdin);
    int m = getInt();
    int mod = getInt();
    int pos, last = 0;
    char cmd[3];

    //��ʼ��
    toUsed = 0;
    build(Root,0,0,0,1);

    while(m--){
        scanf("%s",cmd);
        pos = size(Root);
        if('A'==*cmd){
            insert(Root,pos+1,(getInt()+last)%mod);
        }else{
            printf("%d\n",last=max(Root,pos-getInt()+1,pos));
        }
    }
    return 0;
}

