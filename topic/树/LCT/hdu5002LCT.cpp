/**
    1 xy ab��xy֮��ı�ɾ����ab֮������
    2 a b x��ab·����ֵȫ���ĳ�x
    3 a b d��ab·����ֵȫ������d
    4 a b����ѯab·��֮����ϸ�ڶ���Ȩֵ������
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 201000;

struct value_t{
    int value;
    int cnt;
    value_t(int a=0,int b=0):value(a),cnt(b){}
};

bool operator < (value_t const&lhs,value_t const&rhs){
    return lhs.value < rhs.value;
}

bool operator > (value_t const&lhs,value_t const&rhs){
    return lhs.value > rhs.value;
}

bool cmp(value_t const&lhs,value_t const&rhs){
    return lhs.value == rhs.value;
}

int const NINF = -2000000000;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    int value;
    int size;
    value_t peak;  //splay���������ֵ����¼·�����ֵ
    value_t peak2; //�δ�ֵ
    int lazyd;
    int lazys;
    unsigned char flip;//��1λ��ʾ�����ӳ٣���0λ��ʾ��ת�ӳ�
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    //����ֵ�ʹδ�ֵ
    value_t a[5] = {value_t(Node[t].value,1)};
    int k = 1;

    int son = Node[t].son[LEFT];
    if ( son ) a[k++] = Node[son].peak, a[k++] = Node[son].peak2, Node[t].size += Node[son].size;
    if ( son = Node[t].son[RIGHT] ) a[k++] = Node[son].peak, a[k++] = Node[son].peak2, Node[t].size += Node[son].size;

    //����
    sort(a,a+k,greater<value_t>());

    value_t b[5];
    copy(a,a+k,b);
    int kb = unique(b,b+k,cmp) - b;

    if ( 1 == kb ){//ֻ�м���ֵ
        Node[t].peak.value = a[0].value;
        Node[t].peak.cnt = 0;
        for(int i=0;i<k;++i) Node[t].peak.cnt += a[i].cnt;
        Node[t].peak2.value = NINF;
        Node[t].peak2.cnt = 0;
    }else{//���ڴδ�ֵ
        Node[t].peak.value = a[0].value;
        Node[t].peak.cnt = a[0].cnt;
        int i = 1;
        while( a[i].value == a[0].value ) Node[t].peak.cnt += a[i++].cnt;

        Node[t].peak2.value = a[i].value;
        Node[t].peak2.cnt = a[i++].cnt;
        while( i < k && a[i].value == Node[t].peak2.value ) Node[t].peak2.cnt += a[i++].cnt;
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
    if ( t && (Node[t].flip & 2) ){//�ٴ���set
        int& lazy = Node[t].lazys;

        int son = Node[t].son[LEFT];
        if(son){
            Node[son].value = lazy,
            Node[son].lazys = lazy,
            Node[son].lazyd = 0,
            Node[son].peak.value = lazy,
            Node[son].peak.cnt = Node[son].size;
            Node[son].peak2.value = NINF;
            Node[son].peak2.cnt = 0;
            Node[son].flip |= 2;
        }

        if(son = Node[t].son[RIGHT]){
            Node[son].value = lazy,
            Node[son].lazys = lazy,
            Node[son].lazyd = 0,
            Node[son].peak.value = lazy,
            Node[son].peak.cnt = Node[son].size;
            Node[son].peak2.value = NINF;
            Node[son].peak2.cnt = 0;
            Node[son].flip |= 2;
        }

        Node[t].flip ^= 2;//���set���
        lazy = 0; //��һ������ν
    }
    if ( t && Node[t].lazyd ){//�����delta��
        int& lazy = Node[t].lazyd;

        int son = Node[t].son[LEFT];
        if(son){
            Node[son].value += lazy,
            Node[son].lazyd += lazy;
            Node[son].peak.value += lazy;
            if ( Node[son].peak2.value != NINF ) Node[son].peak2.value += lazy;
        }

        if(son = Node[t].son[RIGHT]){
            Node[son].value += lazy,
            Node[son].lazyd += lazy;
            Node[son].peak.value += lazy;
            if ( Node[son].peak2.value != NINF ) Node[son].peak2.value += lazy;
        }

        lazy = 0;
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
void modifyS(int x,int y,int newValue){
    _makeRoot(x);
    _access(y);
    _splay(y);

    Node[y].value = newValue;
    Node[y].peak.value = newValue;
    Node[y].peak.cnt = Node[y].size;
    Node[y].peak2.value = NINF;
    Node[y].peak2.cnt = 0;
    Node[y].lazys = newValue;
    Node[y].lazyd = 0;
    Node[y].flip |= 2;
}
//·������
void modifyD(int x,int y,int delta){
    _makeRoot(x);
    _access(y);
    _splay(y);

    Node[y].value += delta;
    Node[y].peak.value += delta;
    if ( Node[y].peak2.value != NINF ) Node[y].peak2.value = delta;
    Node[y].lazyd += delta;
}
//·����ѯ�δ�ֵ
value_t maxPath(int x,int y){
    _makeRoot(x);
    _access(y);
    _splay(y);
    return Node[y].peak2;
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
    int cmd,a,b,n,q,nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        memset(Node,0,((n = getInt())+1)*sizeof(node_t));
        q = getInt();
        for(int i=1;i<=n;++i){
            Node[i].value = getInt();
        }
        for(int i=1;i<n;++i){
            a = getInt();
            link(a,getInt());
        }

        //������
        printf("Case #%d:\n",kase);
        value_t ans;
        while(q--){
            cmd = getInt();
            a = getInt();
            b = getInt();
            switch(cmd){
                case 1:cut(a,b);link(getInt(),getInt());break;
                case 2:modifyS(a,b,getInt());break;
                case 3:modifyD(a,b,getInt());break;
                case 4:ans=maxPath(a,b);ans.cnt?printf("%d %d\n",ans.value,ans.cnt):puts("ALL SAME");break;
                default:throw runtime_error("wrong cmd");
            }
        }
    }
    return 0;
}

