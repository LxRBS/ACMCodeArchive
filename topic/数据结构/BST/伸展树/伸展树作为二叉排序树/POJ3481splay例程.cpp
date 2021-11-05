/*
    3�ֲ���
    1KP�����ͻ�K�����ȼ�P����
    2�����ȼ���ߵĳ�ȥ
    3�����ȼ���͵ĳ�ȥ
    ��չ����Ϊ���������������Ĳ���
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 1000010;
int const LEFT = 0;
int const RIGHT = 1;

typedef int key_t;
typedef int value_t;

struct node_t{
    int parent;//����pΪ0���ʾ��
    int son[2];//��
    int sn;    //���У������
    key_t key; //�������⼴���ȼ�
    value_t value;//ֵ
}Node[SIZE];   //0��ʾ��
int toUsed;

//��ʼ��
inline void initTree(){
    memset(Node,0,sizeof(node_t));
    toUsed = 1;
}

//��ȡһ�����õĽڵ㣬�൱��new
inline int _newNode(){
    memset(Node+toUsed,0,sizeof(node_t));
    return toUsed++;
}

//��p��sn��������Ϊt
inline void _link(int p,int sn,int t){
    Node[ Node[t].parent = p ].son[ Node[t].sn = sn ] = t;
}

//��תt��t���벻�Ǹ�
inline void _rotate(int t){
    int sn = Node[t].sn;
    int osn = sn ^ 1;
    int p = Node[t].parent;

    _link(Node[p].parent,Node[p].sn,t);
    _link(p,sn,Node[t].son[osn]);
    _link(t,osn,p);
}

//��չ����t��չΪp�Ķ��ӣ�pΪ0����չΪ����
void _splay(int&root,int p,int t){
    while( Node[t].parent != p ){
        int pp = Node[t].parent;
        if ( Node[pp].parent != p ) Node[pp].sn == Node[t].sn ? _rotate(pp) : _rotate(t);
        _rotate(t);
    }

    if ( 0 == p ) root = t;
}

//��root���ϲ��Ҽ�Ϊkey�Ľڵ㣬�ҵ����ؽڵ�
//���򷵻�0����pΪ������ĸ��ڵ���
int _advance(int root,int&parent,key_t key){
    int t = root;
    parent = Node[t].parent;
    while( t && key != Node[t].key ){
        parent = t;
        t = Node[t].son[ key < Node[t].key ? LEFT : RIGHT ];
    }
    return t;
}

//�����������root���ϲ����ΪkeyֵΪvalue�Ľڵ�
void insert(int&root,key_t key,value_t value){
    //�½�һ���ڵ�
    int t = _newNode();
    Node[t].key = key;
    Node[t].value = value;

    //����ǿ���
    if ( 0 == root ){
        root = t;
        return;
    }

    //����Ӧ�����λ�ã���֤û����ͬ�ļ�
    int p;
    int tt = _advance(root,p,key);

    //ȷ�����ӹ�ϵ
    int sn = key < Node[p].key ? LEFT : RIGHT;
    _link(p,sn,t);
    _splay(root,0,t);
}

//��root���ϲ������ֵ�����ؽڵ�
int max(int &root){
    if ( 0 == root ) return 0;

    int t = root;
    while( Node[t].son[RIGHT] ) t = Node[t].son[RIGHT];
    _splay(root,0,t);
    return t;
}

//��root���ϲ�����Сֵ�����ؽڵ�
int min(int &root){
    if ( 0 == root ) return 0;

    int t = root;
    while( Node[t].son[LEFT] ) t = Node[t].son[LEFT];
    _splay(root,0,t);
    return t;
}

int main(){
    //freopen("1.txt","r",stdin);

    initTree();
    int cmd,k,p,root=0;//������һ������
    while( scanf("%d",&cmd),cmd ){
        if ( 1 == cmd ){
            scanf("%d%d",&k,&p);
            insert(root,p,k);
        }else if ( 2 == cmd ){
            int t = max(root);
            printf("%d\n",Node[t].value);
            //ɾ�����ֵ�����������Դ˴��Ͳ���װ��
            if ( root ){
                root = Node[root].son[LEFT];
                Node[root].parent = 0;
            }
        }else{
            int t = min(root);
            printf("%d\n",Node[t].value);
            //ɾ����Сֵ�����������Դ˴��Ͳ���װ��
            if ( root ){
                root = Node[root].son[RIGHT];
                Node[root].parent = 0;
            }
        }
    }
    return 0;
}
