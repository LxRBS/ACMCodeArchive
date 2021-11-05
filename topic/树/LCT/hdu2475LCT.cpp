/**
  ���ɸ������׺���
  MOVE x y����x�����ƶ���y�������棬���yΪ0����x���ӷŵ�����
  QUERY x����x���ӵĸ�
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
    unsigned char flip;//��1λ��ʾ�����ӳ٣���0λ��ʾ��ת�ӳ�
}Node[SIZE];
int toUsed = 0;

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
}

void _splay(int t){
    while(!_isRoot(t)){
        int p = Node[t].parent;
        if(!_isRoot(p)) _getSN(t)==_getSN(p)?_rotate(p):_rotate(t);
        _rotate(t);
    }
}

//�Ӹ���x�γ�һ����������
int _access(int x){
    int t = 0;
    for(;x;x=Node[t=x].parent){
        _splay(x);
        Node[x].son[RIGHT] = t;//��������
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
//��root������������£�x��y�������������
inline int lca(int root,int x,int y){
    _makeRoot(root);
    _access(x);
    return _access(y);
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
}

inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
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
    int n,m,x,y,root;char cmd[14];
    bool flag = false;
    while(EOF!=scanf("%d",&n)){
        flag?putchar('\n'):flag=true;

        root = n+1;//����һ������ĸ��ڵ㣬���ֲ���
        memset(Node,0,(n+2)*sizeof(node_t));
        for(int i=1;i<=n;++i)x=getUnsigned(),link(x?x:root,i);
        //������
        m = getUnsigned();
        while(m--){
            scanf("%s",cmd);
            if('M'==*cmd){
                x = getUnsigned();
                y = getUnsigned();
                //��x�ӵ�y���棬����Ƿ��򲻲���
                if(lca(root,x,y)==x)continue;
                cut(root,x);link(y?y:root,x);
            }else{//�Ҹ���������root
                int tmp = _getRoot(getUnsigned());
                _splay(tmp);
                //��������������С��
                tmp = Node[tmp].son[RIGHT];
                while(Node[tmp].son[LEFT]) tmp = Node[tmp].son[LEFT];
                printf("%d\n",tmp);
            }
        }
    }
    return 0;
}
