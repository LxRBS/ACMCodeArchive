/**
0 x y ����ѯ�ʴ� xx �� yy ��·���ϵĵ��Ȩֵ��xor �͡���֤ xx �� yy ����ͨ�ġ�
1 x y �������� xx �� yy���� xx �� yy �Ѿ���ͨ���������ӡ�
2 x y ����ɾ���� (x,y)������֤�� (x,y) ���ڡ�
3 x y ������ xx �ϵ�Ȩֵ��� yy��
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
    int size;      //splay�����Ľڵ���������·����Ϣ
    value_t value; //��Ȩ
    value_t sum;   //splay���ĺͣ���·����
    unsigned char flip;//��1λ��ʾ�����ӳ٣���0λ��ʾ��ת�ӳ�
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].sum = Node[t].value;

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        Node[t].sum ^= Node[son].sum;
    }
    if(son=Node[t].son[RIGHT]){
        Node[t].size += Node[son].size;
        Node[t].sum ^= Node[son].sum;
    }
}

inline void _pushDown(int t){
    if ( t && (Node[t].flip & 1) ){//���ȴ���ת
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].flip ^= 1;
        if(son = Node[t].son[RIGHT]) Node[son].flip ^= 1;

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
    _splay(x);//��ǰû��splay������TLE
    return x;
}
//��child��parent���ӽڵ�
inline void link(int parent,int child){
    _makeRoot(child);
    Node[child].parent = parent;
}

inline bool isConnect(int x,int y){
    return _getRoot(x) == _getRoot(y);
}
//��������
void modifyS(int x,value_t newValue){
    _access(x);
    _splay(x);

    Node[x].sum ^= newValue ^ Node[x].value;
    Node[x].value = newValue;
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
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
void dispLCT(FILE*fp, int n);
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    toUsed = 0;
    for(int i=1;i<=n;++i){
        Node[i].value = Node[i].sum = getUnsigned();
        Node[i].size = 1;
    }
    int tmp;
    while(m--){
        int cmd = getUnsigned();
        int x = getUnsigned();
        int y = getUnsigned();
        switch(cmd){
            case 0:printf("%d\n",sumPath(x,y));break;
            case 1:if(!isConnect(x,y))link(x,y);break;
            case 2:if(isConnect(x,y)){
                _makeRoot(x);
                _access(y);
                _splay(y);
                //���·������Ϊ2˵��x��yֱ������
                if(Node[y].size==2)Node[y].son[LEFT] = Node[x].parent = 0,_pushUp(y);
            }break;
            case 3:modifyS(x,y);break;
            default:throw runtime_error("wrong cmd");
        }
        //dispLCT(stdout,n);
    }
    return 0;
}
bool TmpFlag[SIZE];
void _dispNodeIter(FILE*fp,int t){
    _pushDown(t);//���֮ǰ����ҪpushDown
    if(Node[t].son[LEFT]) _dispNodeIter(fp,Node[t].son[LEFT]);
    TmpFlag[t] = true;
    fprintf(fp,"%d value:%d, sum:%d\n",t,Node[t].value,Node[t].sum);
    //fprintf(fp,"           total_siz:%d, i_siz:%d\n",Node[t].total_size,Node[t].i_size);
    if(Node[t].son[RIGHT]) _dispNodeIter(fp,Node[t].son[RIGHT]);
}
void dispNode(FILE*fp,int t){
    _maintain(t);
    //�����ҵ�t��splay���ڵ�
    int root = t;
    while(!_isRoot(root)) root = Node[root].parent;
    //��root��һ���������
    fprintf(fp,"splay: %d, path_parent: %d\n",root,Node[root].parent);
    _dispNodeIter(fp,root);
}
//һ��n���ڵ�
void dispLCT(FILE*fp, int n){
    fill(TmpFlag,TmpFlag+n+1,false);
    fprintf(fp,"LCT:\n");
    for(int i=1;i<=n;++i)if(!TmpFlag[i]){
        dispNode(fp, i);
    }
}
