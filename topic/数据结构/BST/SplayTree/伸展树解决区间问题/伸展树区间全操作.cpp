/**
1����������
2�����䱶��
3����������
4�������ѯ��
5�������ѯƽ����
6�������ѯ������
7�������ѯ���ֵ����ȡģȫ����������ȷ����������Ҫ����
8�������ѯ��Сֵ
9�����䷭ת
10������ѭ������
11�������ƶ�
12������ɾ��
13���������

ע��ȡģ�����µ���ֵ�ǲ���ȷ�ģ���Ϊ�޷���ȷ�����ӳٲ���
����Ҫע�ⲻȡģ�����£���ֵ�ļ������������й�
�˴�ȫ������
���������Ϸ��Լ�⣬��������Ҫ��֤�����Ϸ�

void build(int n, valuet const a[]): ����n���������飬��ʼ����չ������ʼ��������������á�a[0],a[n+1]��ó�ʼ��Ϊ�������Է�����ԣ�������Ҳ��Ӱ����
void insert(int &root, int pos, const valuet&value): ��root���ϵĵ�pos��λ�ò���һ���ڵ㣬ȨֵΪvalue�������Ժ�ԭposλ���ϵ��������������������ƶ�һ��
value_t max(int &root, int s, int e): ��root���ϲ�ѯ[s, e]�����ֵ
value_t max(int &root, int s, int e): ��root���ϲ�ѯ[s, e]����Сֵ
void modifyD(int &root, int s, int e, const value_t &delta): ��root����[s, e]ȫ������delta
void modifyM(int &root, int s, int e, const value_t &m): ��root����[s, e]ȫ������m
void modifyS(int &root, int s, int e, const value_t &newValue): ��root����[s, e]ȫ������newValue
void move(int &root, int s, int e, int pos): ��root���ϣ���[s, e]�ƶ���posλ�ã�Ҳ����˵�ƶ�֮��ԭsλ�õ������ӵ�posλ�ÿ�ʼ�������������
void remove(int &root, int s, int e): ��root����ɾ��[s, e]������ȫ��ɾ��
void reverse(int &root, int s, int e): ��root�ϣ���ת[s, e]
void rotate4(int &root, int s, int e, int k): ��root���ϣ�ѭ������[s, e]kλ�����kС���㣬����ѭ������
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

typedef long long int llt;
typedef llt value_t;

llt const MOD = 1000000007LL;

inline llt add(llt x,llt y){return (x+y)%MOD;}
inline llt add(llt x,llt y,llt z){return add(x, add(y, z));}
inline llt add(llt x,llt y,llt z,llt w){return add(x, add(y, z, w));}

inline llt mul(llt x,llt y){return (x*y)%MOD;}
inline llt mul(llt x,llt y,llt z){return mul(x, mul(y, z));}
inline llt mul(llt x,llt y,llt z,llt w){return mul(x, mul(y, z, w));}

inline void addAss(llt&x, llt y){x=add(x, y);}
inline void mulAss(llt&x, llt y){x=mul(x, y);}

int const SIZE = 200100;
int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;//���ڵ�
    int son[2];//�ӽڵ�
    int sn;    //���ڵ������
    int size;  //size��
    value_t value; //ֵ
    value_t peak;  //���ֵ��ע�����ȡģ������ֵ���ܲ���
    value_t valley;//��Сֵ
    llt sum;       //��ֵ��ֻ�к�ֵ�п��ܳ���int32
    llt sum2;      //ƽ����
    llt sum3;      //������
    value_t k;     //ע��k����Ϊ��������ֵ���ܲ���
    value_t b;
    value_t x;     //�ӳٱ�ǣ�k�Ǳ��ˣ�b�����ӣ�x������
    unsigned char flip;//��0λ��ʾ��ת���ӳٱ�ǣ���1λ��ʾset���ӳٱ��
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].sum = Node[t].peak = Node[t].valley = Node[t].value;
    Node[t].sum2 = mul(Node[t].value, Node[t].value);
    Node[t].sum3 = mul(Node[t].sum2, Node[t].value);

    int son = Node[t].son[LEFT];
    if(son){
        Node[t].size += Node[son].size;
        addAss(Node[t].sum, Node[son].sum);
        addAss(Node[t].sum2, Node[son].sum2);
        addAss(Node[t].sum3, Node[son].sum3);
        Node[t].peak = max(Node[t].peak,Node[son].peak);
        Node[t].valley = min(Node[t].valley,Node[son].valley);
    }
    if(son = Node[t].son[RIGHT]){
        Node[t].size += Node[son].size;
        addAss(Node[t].sum, Node[son].sum);
        addAss(Node[t].sum2, Node[son].sum2);
        addAss(Node[t].sum3, Node[son].sum3);
        Node[t].peak = max(Node[t].peak,Node[son].peak);
        Node[t].valley = min(Node[t].valley,Node[son].valley);
    }
}

void _f(int t,int size,int k,int b){
    Node[t].peak = add(mul(Node[t].peak, k), b);
    Node[t].valley = add(mul(Node[t].valley, k), b);

    llt k2 = mul(k, k);
    llt k3 = mul(k2, k);
    llt b2 = mul(b, b);
    llt b3 = mul(b2, b);
    //������
    Node[t].sum3 = add(mul(k3, Node[t].sum3), mul(3, k2, b, Node[t].sum2), mul(3, k, b2, Node[t].sum), mul(size, b3));
    //ƽ����
    Node[t].sum2 = add(mul(k2, Node[t].sum2), mul(2, k, b, Node[t].sum), mul(size, b2));
    //��
    Node[t].sum = add(mul(Node[t].sum, k), mul(size, b));
}
inline void _pushDown(int t){
    if (0==t) return;

    int son;
    if(Node[t].flip & 1){//���ȴ���ת
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);
        if(son=Node[t].son[LEFT]) Node[son].sn = LEFT, Node[son].flip ^= 1;
        if(son=Node[t].son[RIGHT]) Node[son].sn = RIGHT, Node[son].flip ^= 1;
        Node[t].flip ^= 1;
    }

    value_t&k = Node[t].k;
    value_t&b = Node[t].b;
    value_t&x = Node[t].x;
    if(Node[t].flip & 2){//�ٴ���set
        llt tmp = add(mul(k, x), b);

        if(son = Node[t].son[LEFT]){
            //�ӳٱ��
            Node[son].flip |= 2;//��set�ӳٱ��
            Node[son].k = 1;
            Node[son].b = 0;
            Node[son].x = tmp;
            //����ֵ
            Node[son].value = Node[son].peak = Node[son].valley = tmp;
            Node[son].sum = mul(tmp, Node[son].size);
            Node[son].sum2 = mul(tmp, tmp, Node[son].size);
            Node[son].sum3 = mul(tmp, tmp, tmp, Node[son].size);
        }
        if(son = Node[t].son[RIGHT]){
            //�ӳٱ��
            Node[son].flip |= 2;//��set�ӳٱ��
            Node[son].k = 1;
            Node[son].b = 0;
            Node[son].x = tmp;
            //����ֵ
            Node[son].value = Node[son].peak = Node[son].valley = tmp;
            Node[son].sum = mul(tmp, Node[son].size);
            Node[son].sum2 = mul(tmp, tmp, Node[son].size);
            Node[son].sum3 = mul(tmp, tmp, tmp, Node[son].size);
        }

        Node[t].flip ^= 2;//���set���
    }else if (k!=1||b!=0){//�����
        if(son = Node[t].son[LEFT]){
            //�ӳٱ��
            mulAss(Node[son].k, k);
            Node[son].b = add(mul(k, Node[son].b), b);
            //����ֵ
            Node[son].value = add(mul(Node[son].value, k), b);
            _f(son, Node[son].size, k, b);
        }

        if(son=Node[t].son[RIGHT]){
            //�ӳٱ��
            mulAss(Node[son].k, k);
            Node[son].b = add(mul(k, Node[son].b), b);
            //����ֵ
            Node[son].value = add(mul(Node[son].value, k), b);
            _f(son, Node[son].size, k, b);
        }
    }
    k=1;b=0;x=0;
}
//����һ���½ڵ�
inline int _newNode(value_t value=0){
    memset(Node+(++toUsed),0,sizeof(node_t));
    //�������ùܣ��ڸ��Ժ����д���
    Node[toUsed].value = value;
    Node[toUsed].k = 1;//��������ʼ��Ϊ0�����һ��Ҫ��1
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
    //����ֵ
    t = _newNode(value);
    Node[t].peak = Node[t].valley = Node[t].sum = value;
    Node[t].size = 1;
    Node[t].sum3 = mul(value, Node[t].sum2=mul(value, value));
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
    //�ӳٱ��
    addAss(Node[son].b, delta);
    //����ֵ
    addAss(Node[son].value, delta);
    _f(son,Node[son].size,1, delta);
    _pushUp(tt);_pushUp(root);
}
//[s,e]����ȫ������ΪnewValue
void modifyS(int&root,int s,int e,value_t const&newValue){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    //��������ӵ��Ҷ��Ӵ���
    int son = Node[tt].son[LEFT];
    Node[son].flip |= 2;//��set�ӳٱ��
    Node[son].k = 1;
    Node[son].b = 0;
    Node[son].x = newValue;
    //����ֵ
    Node[son].value = Node[son].peak = Node[son].valley = newValue;
    Node[son].sum = mul(Node[son].size, newValue);
    Node[son].sum2 = mul(Node[son].size, newValue, newValue);
    Node[son].sum3 = mul(Node[son].size, newValue, newValue, newValue);
    _pushUp(tt);_pushUp(root);
}
//[s,e]����ȫ������m
void modifyM(int&root,int s,int e,value_t const&m){
    int t = _kth(root,s-1);
    _splay(root,0,t);
    int tt = _kth(root,e+1);
    _splay(root,root,tt);
    //��������ӵ��Ҷ��Ӵ���
    int son = Node[tt].son[LEFT];
    //�ӳٱ��
    mulAss(Node[son].k, m);
    mulAss(Node[son].b, m);
    //����ֵ
    mulAss(Node[son].value, m);
    _f(son,Node[son].size,m,0);
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
//��[s,e]�����ƶ�����posλ�ÿ�ʼ
void move(int&root ,int s,int e,int pos){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    Node[tt].son[LEFT] = 0;
    _pushUp(tt);_pushUp(root);

    //��posλ��
    //if(pos>e) pos -= e - s + 1;
    t = _kth(root,pos-1);
    _splay(root,0,t);

    tt = _kth(root,pos);
    _splay(root,root,tt);

    _link(tt,LEFT,son);
    _pushUp(tt);_pushUp(root);
}
llt sum(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].sum;
}
llt sum2(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].sum2;
}
llt sum3(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].sum3;
}
value_t max(int&root,int s,int e){
    int t = _kth(root,s-1);
    _splay(root,0,t);

    int tt = _kth(root,e+1);
    _splay(root,root,tt);

    int son = Node[tt].son[LEFT];
    return Node[son].peak;
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
void _build(int&t,int parent,int sn,int s,int e,value_t const a[]){
    int mid = ( s + e ) >> 1;

    t = _newNode(a[mid]);
    Node[t].parent = parent;
    Node[t].sn = sn;

    if ( s < mid ) _build(Node[t].son[LEFT],t,LEFT,s,mid-1,a);
    if ( mid < e ) _build(Node[t].son[RIGHT],t,RIGHT,mid+1,e,a);

    _pushUp(t);
}

inline bool empty(int root){
    return Node[root].size<=2;
}
inline int size(int root){
    return Node[root].size - 2;
}
int Root;

//����ȫ�����齨��,һ��n������ñ�֤a[0],a[n+1]==0
void build(int n, value_t const a[]){
    toUsed = 0;
    _build(Root,0,0,0,n+1,a);
}

value_t A[SIZE];

void dispTree(FILE*,int);
int main(){
    //freopen("1.std.in","r",stdin);
    //freopen("��չ������ȫ����.std.in","r",stdin);
    //freopen("2.txt","w",stdout);
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        //������
        int n = getInt();
        int m = getInt();
        for(int i=1;i<=n;++i)A[i]=getInt();
        A[0] = A[n+1] = 0;

        //����
        build(n, A);

        //������
        printf("Case #%d:\n",kase);

        int cmd,s,e;
        value_t w;
        value_t ans;
        for(int i=1;i<=m;++i){
            if(5==i){
                int t=22;
            }
            cmd = getInt();
            s = getInt();
            if(13!=cmd) e = getInt();
            else e = -1;
            switch(cmd){
            case 1:{//����
                modifyD(Root,s,e,w=getInt());
            }break;
            case 2:{//����
                modifyM(Root,s,e,w=getInt());
            }break;
            case 3:{//����
                modifyS(Root,s,e,w=getInt());
            }break;
            case 4:{//��
                ans = sum(Root,s,e);printf("%lld\n", ans);
            }break;
            case 5:{//ƽ����
                ans = sum2(Root,s,e);printf("%lld\n", ans);
            }break;
            case 6:{//������
               ans =  sum3(Root,s,e);printf("%lld\n", ans);
            }break;
            case 7:{//���ֵ
                ans = max(Root,s,e);printf("%lld\n", ans);
            }break;
            case 8:{//��Сֵ
                ans = min(Root,s,e);printf("%lld\n", ans);
            }break;
            case 9:{//���䷭ת
                reverse(Root,s,e);
            }break;
            case 10:{//����ѭ�����ƣ�������С��0ʱ������
                rotate(Root,s,e,w=getInt());
            }break;
            case 11:{//�����ƶ�
                move(Root,s,e,w=getInt());
            }break;
            case 12:{//����ɾ��
                remove(Root,s,e);
            }break;
            case 13:{//�������
                insert(Root,s,w=getInt());
            }break;
            default:throw runtime_error("wrong cmd");
            }
        }

    }
    return 0;
}

void dispNode(FILE*fp,int t){
    _pushDown(t);
    fprintf(fp,"%d: Parent: %d, SN: %d, LSON: %d, RSON: %d\n",t,Node[t].parent,Node[t].sn,Node[t].son[LEFT],Node[t].son[RIGHT]);
    fprintf(fp,"    Value: %d, Sum: %lld, Size: %d, Peak: %d\n",Node[t].value,Node[t].sum,Node[t].size,Node[t].peak);
}
void _dispTree(FILE*fp,int t){
    if ( Node[t].son[LEFT] ) _dispTree(fp,Node[t].son[LEFT]);
    dispNode(fp,t);
    if ( Node[t].son[RIGHT] ) _dispTree(fp,Node[t].son[RIGHT]);
}
void dispTree(FILE*fp,int root){
    printf("Tree:\n");
    _dispTree(fp,root);
}
