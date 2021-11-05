/**
    1~N�����У����ֲ���
    CUT s e pos����[s,e]�ƶ�����pos֮ǰ��ʼ��ע����ģ�������
    FLIP s e: ���䷭ת
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

int const SIZE = 300100;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;//���ڵ�
    int son[2];//�ӽڵ�
    int sn;    //���ڵ������
    int size;  //size��
    value_t value; //ֵ
    unsigned char flip;//��0λ��ʾ��ת���ӳٱ��
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
    }
    son = Node[t].son[RIGHT];
    if(son){
        Node[t].size += Node[son].size;
    }
}
inline void _pushDown(int t){
    if ( t && (Node[t].flip & 1) ){//���ȴ���ת
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].sn = LEFT, Node[son].flip ^= 1;

        son = Node[t].son[RIGHT];
        if(son) Node[son].sn = RIGHT, Node[son].flip ^= 1;

        Node[t].flip ^= 1;
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
    _pushDown(t);
    int son = Node[t].son[LEFT];
    int s = son?Node[son].size:0;
    if(k<s) return _kth(son,k);//ȥ��������
    return s < k ? _kth(Node[t].son[RIGHT],k-s-1) : t;
}
//[s,e]������з�ת
void reverse(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int ttt = Node[tt].son[LEFT];
    Node[ttt].flip ^= 1;
}
//��[s,e]�����ƶ�����posλ�ÿ�ʼ
void move(int&root ,int s,int e,int pos){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    Node[tt].son[LEFT] = 0;
    _pushUp(tt);_pushUp(root);

    t = _kth(root,pos-1);
    _splay(root,0,t);

    tt = _kth(root,pos);
    _splay(root,root,tt);

    _link(tt,LEFT,son);
    _pushUp(tt);_pushUp(root);
}

//����ȫ�����齨��
void build(int&t,int parent,int sn,int s,int e){
    int mid = ( s + e ) >> 1;

    t = _newNode(mid);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) build(Node[t].son[LEFT],t,LEFT,s,mid-1);
    if ( mid < e ) build(Node[t].son[RIGHT],t,RIGHT,mid+1,e);

    _pushUp(t);
}

int Root;

void dispTree(int&);
int main(){
    char cmd[12];
    int n,m,a,b,c;
    while(n=getInt(),m=getInt(),n<0&&m<0?0:1){
        toUsed = 0;//��ʼ��
        build(Root,0,0,0,n+1);
        while(m--){
            scanf("%s",cmd);
            a = getInt();
            b = getInt();
            if('C'==*cmd) move(Root,a,b,getInt()+1);
            else reverse(Root,a,b);
        }
        dispTree(Root);
    }
    return 0;
}

void _dispTree(int root){
    _pushDown(root);
    if(Node[root].son[LEFT]) _dispTree(Node[root].son[LEFT]);
    printf(" %d",Node[root].value);
    if(Node[root].son[RIGHT]) _dispTree(Node[root].son[RIGHT]);
}
//Ҫ��֤���һ����û������ո�
void dispTree(int& root){
    int t = _kth(root,0);
    _splay(root,0,t);
    int tt = _kth(root,Node[root].size-1);
    _splay(root,root,tt);
    t = _kth(Node[tt].son[LEFT],0);
    _splay(root,tt,t);
    printf("%d",Node[t].value);
    _dispTree(Node[t].son[RIGHT]);
    printf("\n");
}
