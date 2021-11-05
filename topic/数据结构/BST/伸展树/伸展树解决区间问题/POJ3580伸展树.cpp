/**
    6�ֲ�����ָ��ȫ���Ǵ�д��
    add x y d����������
    reverse x y�����䷭ת
    revolve x y k������ѭ����λ
    insert x p����x�ڵ�֮�����һ���ڵ㣬ע����ģ�������
    delete x��ɾ��һ���ڵ�
    min x y�����伫Сֵ
*/
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <algorithm>
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
    value_t valley;//��Сֵ
    value_t lazyd; //delta���ӳٱ�Ǻ���ֵ
    unsigned char flip;//��0λ��ʾ��ת���ӳٱ��
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].valley = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].valley = min(Node[t].valley,Node[son].valley);
    }
    son = Node[t].son[RIGHT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].valley = min(Node[t].valley,Node[son].valley);
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
    if ( t && Node[t].lazyd ){//�����delta��
        value_t& lazy = Node[t].lazyd;

        int son = Node[t].son[LEFT];
        if(son){
            Node[son].value += lazy;
            Node[son].lazyd += lazy;
            Node[son].valley += lazy;
        }

        son = Node[t].son[RIGHT];
        if(son){
            Node[son].value += lazy;
            Node[son].lazyd += lazy;
            Node[son].valley += lazy;
        }

        lazy = 0;
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

//�ڵ�posλ�ò���һ��ֵvalue������һ���Ϸ���pos��1��ʼ
void insert(int&root,int pos,value_t const&value){
    int t = _kth(root,pos-1);
    _splay(root,0,t);//��pos-1��������
    int tt = _kth(root,pos);
    _splay(root,root,tt);//��pos���������Ҷ���
    //���½ڵ�ҵ������Ҷ��ӵ������
    t = _newNode(value);
    Node[t].valley = value;
    Node[t].size = 1;
    _link(tt,LEFT,t);
    _pushUp(tt);_pushUp(root);
}
//ɾ������[s,e]������һ���Ϸ�
void remove(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    Node[tt].son[LEFT] = 0;
    _pushUp(tt);_pushUp(root);
}
//[s,e]����ȫ������delta
void modifyD(int&root,int s,int e,value_t const&delta){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    //��������ӵ��Ҷ��Ӵ���
    int son = Node[tt].son[LEFT];
    Node[son].value += delta;
    Node[son].valley += delta;
    Node[son].lazyd += delta;
    _pushUp(tt);_pushUp(root);
}
//[s,e]��������ѭ����λk
void rotate(int&root,int s,int e,int k){
    if(0==(k%=(e-s+1))) return;
    if(k<0) k = e-s+1+k;
    //����ɾ��[e-k+1,e]
    int t = _kth(root,e-k);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    int son = Node[tt].son[LEFT];
    Node[tt].son[LEFT] = 0;
    _pushUp(tt);_pushUp(root);
    //�ٰ�son���뵽sλ��
    t = _kth(root,s-1);
    _splay(root,0,t);
    tt = _kth(root,s);
    _splay(root,root,tt);
    _link(tt,LEFT,son);
    _pushUp(tt);_pushUp(root);
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
value_t min(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].valley;
}
//����ȫ�����齨��
void build(int&t,int parent,int sn,int s,int e,value_t const a[]){
    int mid = ( s + e ) >> 1;

    t = _newNode(a[mid]);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) build(Node[t].son[LEFT],t,LEFT,s,mid-1,a);
    if ( mid < e ) build(Node[t].son[RIGHT],t,RIGHT,mid+1,e,a);

    _pushUp(t);
}
int Root;
value_t A[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    for(int i=1;i<=n;++i)A[i]=getInt();
    build(Root,0,0,0,n+1,A);
    int m = getInt();

    char cmd[30];
    int x,y;
    while(m--){
        scanf("%s",cmd);
        x = getInt();
        switch(*cmd){
            case 'A':y=getInt();modifyD(Root,x,y,getInt());break;
            case 'D':remove(Root,x,x);break;
            case 'I':insert(Root,x+1,getInt());break;
            case 'M':printf("%d\n",min(Root,x,getInt()));break;
            case 'R':{
                if('E'==cmd[3])reverse(Root,x,getInt());
                else if('O'==cmd[3])y=getInt(),rotate(Root,x,y,getInt());
                else throw runtime_error("Wrong cmd");
            }break;
            default:throw runtime_error("Wrong cmd");
        }
    }
    return 0;
}
