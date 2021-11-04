/**
    ����������������
    ����λ�ú�ֵ��ÿ������һ��
    ����������
    λ�ô�0��ʼ
    ��򵥵����䵥����
    ��չ����G++�ύ�ᳬʱ��C++�ɹ�
    ��getUnsigned�ᳬʱ����scanf�ɹ�
*/
#include <stdio.h>
#include <string.h>

typedef int value_t;

int const SIZE = 500100;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;//���ڵ�
    int son[2];//�ӽڵ�
    int sn;    //���ڵ������
    int size;  //size��
    value_t value; //ֵ
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
    Node[t].size = 1;
    _link(tt,LEFT,t);
    _pushUp(tt);_pushUp(root);
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
int Root;
void dispTree(int&);
int main(){
    //freopen("1.txt","r",stdin);
    int n,pos,value;
    while(scanf("%d",&n)!=EOF){
        //��ʼ��
        toUsed = 0;
        build(Root,0,0,0,1);

        while(n--){
            scanf("%d%d",&pos,&value);
            insert(Root,++pos,value);
        }
        dispTree(Root);
    }
    return 0;
}

void _dispTree(int root){
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
