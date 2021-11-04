/**
   ƽ�����������������չ���������ظ��ļ�ֵ
1 ���� xx ��
2 ɾ�� xx ��(���ж����ͬ��������ֻɾ��һ��)
3 ��ѯ xx ��������(��������Ϊ�ȵ�ǰ��С�����ĸ��� +1 )
4 ��ѯ����Ϊ xx ����
5 �� xx ��ǰ��(ǰ������ΪС�� xx����������)
6 �� xx �ĺ��(��̶���Ϊ���� xx������С����)
ǿ������
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef int key_t;
int const SIZE = 1100100;
int const LEFT = 0;
int const RIGHT = 1;
int const NEG_INF = -2100000000;
int const POS_INF = 2100000000;

struct node_t{
    int parent;//���ڵ�
    int son[2];//�ӽڵ�
    int sn;    //���ڵ������
    int size;  //size�򣬱��ڵ������Ľڵ���������������
    int cnt;   //���ڵ��ֵ������
    key_t key; //��ֵ
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = Node[t].cnt;
    int son = Node[t].son[LEFT];
    if(son) Node[t].size += Node[son].size;
    son = Node[t].son[RIGHT];
    if(son) Node[t].size += Node[son].size;
}
//����һ���½ڵ�
inline int _newNode(key_t key=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //�������ùܣ��ڸ��Ժ����д���
    Node[toUsed].key = key;
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
//��root���ϲ���key������Ҳ����򷵻�0ͬʱp����Ӧ����λ�õĸ��ڵ�
//root��Ϊ��
int _advance(int root,int&p,key_t const&key){
    int t = root;
    while( t && Node[t].key != key ){
        p = t;
        t = Node[t].son[key<Node[t].key?LEFT:RIGHT];
    }
    return t;
}
//��t�����ϲ��ҵ�k��Ԫ�أ���0��ʼ���ظ��ļ�ֵҲҪ��������������һ���Ϸ�
int _kth(int t,int k){
    int son = Node[t].son[LEFT];
    int s = son?Node[son].size:0;
    //ȥ��������
    if(k<s) return _kth(son,k);
    //ȥ��������
    if(s+Node[t].cnt<=k) return _kth(Node[t].son[RIGHT],k-s-Node[t].cnt);
    return t;//���ڱ��ڵ���
}
//�ж�root���Ƿ�Ϊ��
inline bool isEmpty(int root){
    return Node[root].size <= 2;
}
//����root���ĳߴ�
inline int size(int root){
    return Node[root].size - 2;
}
//��root���ϲ���key
int insert(int&root,key_t const&key){
    int p;
    int t = _advance(root,p,key);

    if(0==t){//�Ҳ���
        t = _newNode(key);
        _link(p,key<Node[p].key?LEFT:RIGHT,t);
    }
    ++Node[t].cnt;
    _splay(root,0,t);//splay�а�����pushUp����
    return Node[t].cnt;
}
//��root����ɾ��key
int remove(int&root,key_t const&key){
    int p;
    int t = _advance(root,p,key);
    if(0==t) return -7;//root�в���key

    _splay(root,0,t);
    //���ɾ���Ժ���ʣ�µģ�ֱ�ӷ��ؼ���
    if( --Node[t].cnt > 0 ){
        --Node[t].size;//����pushUp����
        return Node[t].cnt;
    }

    //�����ʾ��ǰ�ڵ�Ӧ�ô������޳�
    int son = Node[t].son[LEFT];//�����һ������
    //�ҵ�����������Ľڵ㣬�����Ϊ�����������
    int tt = _kth(son,Node[son].size-1);
    _splay(t,t,tt);
    //��ʱ�����û���Ҷ��ӣ��������Ҷ��ӹ���ȥ����
    _link(tt,RIGHT,Node[t].son[RIGHT]);
    _pushUp(tt);
    return Node[root=tt].parent = 0;//һ��Ҫ����Ϊ0�����Ǹ��ı��
}

//��root������key��ǰ�������ص��ǽڵ㣬key��һ������������
//��Ϊ�ڱ��Ĵ��ڣ�����һ����ǰ��
int pred(int&root,key_t const&key){
    int p,son;
    int t = _advance(root,p,key);
    if(t){//������ڣ������������ҵ����Ľڵ㼴��
        _splay(root,0,t);
        son = Node[t].son[LEFT];//�����һ������
        t = _kth(son,Node[son].size-1);//�����������
        return t;
    }
    //�������p��Ѱ��
    _splay(root,0,p);
    if(Node[p].key<key) return p;
    son = Node[p].son[LEFT];
    t = _kth(son,Node[son].size-1);//�����������
    return t;
}
//��root������key�ĺ�̣����ص��ǽڵ㣬key��һ������������
//��Ϊ�ڱ��Ĵ��ڣ�����һ���к��
int succ(int&root,key_t const&key){
    int p, son;
    int t = _advance(root,p,key);
    if(t){//������ڣ������������ҵ���С�Ľڵ㼴��
        _splay(root,0,t);
        son = Node[t].son[RIGHT];//�Ҷ���һ������
        t = _kth(son,0);//�Ҷ�������С��
        return t;
    }
    //�������p��Ѱ��
    _splay(root,0,p);
    if(key<Node[p].key) return p;
    son = Node[p].son[RIGHT];
    t = _kth(son,0);//�Ҷ�������С��
    return t;
}
//��root��������Сֵ�����ص��ǽڵ�
inline int min(int&root){
    return succ(root, NEG_INF);//���ظ������ĺ��
}
//��root���������ֵ�����ص��ǽڵ�
inline int max(int&root){
    return pred(root, POS_INF);//������������ǰ��
}
//��root���ϲ�ѯkey��������key��һ������������
int rank(int&root,key_t const&key){
    int p,son;
    int t = _advance(root,p,key);
    if(t){//���key���ڣ�ֱ�ӷ�������ӵ�size����Ҫ��1����Ϊ���ڱ�
        _splay(root,0,t);
        son = Node[t].son[LEFT];//�����һ������
        return Node[son].size;
    }

    _splay(root,0,p);
    if ( key < Node[p].key ){
        son = Node[p].son[LEFT];//�����һ������
        return Node[son].size;
    }
    //���Ҷ��ӵ���С���ܵ��˴����Ҷ���һ������
    t = _kth(Node[p].son[RIGHT],0);
    _splay(root,0,t);
    return Node[Node[t].son[LEFT]].size;//�����һ������
}
//��root���ϲ���������k�Ľڵ㣬k��1��ʼ
int kth(int&root,int k){
    //���k�Ƿ���ע��size���ص��Ǽ�ȥ�ڱ��Ժ��size
    if ( k <= 0 || k > size(root) ) return 0;
    int t = _kth(root,k);//��Ϊ���ڱ���ֱ�Ӿ���k
    _splay(root,0,t);
    return t;
}

//�����жϷ��صĽڵ����Ƿ�Ϸ�
inline bool isValid(int t){
    return t && NEG_INF != Node[t].key && POS_INF != Node[t].key;
}

int Root;
//��ʼ��
void initTrees(int n){
    toUsed = 0;
    Root = _newNode(NEG_INF);
    Node[Root].cnt = Node[Root].size = 1;
    insert(Root, POS_INF);
}

void dispTree(FILE*,int);
int main(){
    //freopen("1.txt","r",stdin);
    //freopen("1.txt","w",stdout);
    initTrees(1);
    int n = getUnsigned();
    int m = getUnsigned();
    for(int i=0;i<n;++i)insert(Root,getUnsigned());
    int last = 0, ans = 0;
    while(m--){//����ָ�֤�н�
        switch(getUnsigned()){
            case 1:insert(Root,getUnsigned()^last);break;
            case 2:remove(Root,getUnsigned()^last);break;
            case 3:ans^=last=rank(Root,getUnsigned()^last);break;
            case 4:ans^=last=Node[kth(Root,getUnsigned()^last)].key;break;
            case 5:ans^=last=Node[pred(Root,getUnsigned()^last)].key;break;
            case 6:ans^=last=Node[succ(Root,getUnsigned()^last)].key;break;
            default:throw runtime_error("����ȷ��cmd");
        }

    }
    printf("%d\n",ans);
    return 0;
}

void dispNode(FILE*fp,int t){
    fprintf(fp,"%d: Parent: %d, SN: %d, LSON: %d, RSON: %d\n",t,Node[t].parent,Node[t].sn,Node[t].son[LEFT],Node[t].son[RIGHT]);
    fprintf(fp,"    Key: %d, Cnt: %d, Size, %d\n",Node[t].key,Node[t].cnt,Node[t].size);
}
void _dispTree(FILE*fp,int t){
    dispNode(fp,t);
    if ( Node[t].son[LEFT] ) _dispTree(fp,Node[t].son[LEFT]);
    if ( Node[t].son[RIGHT] ) _dispTree(fp,Node[t].son[RIGHT]);
}
void dispTree(FILE*fp,int root){
    printf("Tree:\n");
    _dispTree(fp,root);
}
