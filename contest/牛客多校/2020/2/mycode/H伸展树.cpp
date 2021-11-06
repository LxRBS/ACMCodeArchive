/**
    ���ֲ���
    1 x: ����һ����
    2 x: ɾ��x
    3 x: �ڼ���������2��������x�γ�������
    ����ƽ�����������A����x������B����(������֮��,����)
    1����: A����ж��x�������x��
           A���ֻ��1��x�������x��B����(0,x)
           A���û��x�������x��B����(x-ǰ,x)��(��-x,��)
    2����: Aɾ��x,A�������û��x����ɾ��(x-ǰ,x)��(��-x,��)
           A����ֻʣһ��x��ɾ��(0,x)
    3������A�����ҵ�xǰ������������������a+b>x����yes
           B������(u,v)������u<x,v>b
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

int const SIZE = 500100;
int const LEFT = 0;
int const RIGHT = 1;
int const NEG_INF = -2100000000;
int const POS_INF = 2100000000;

struct node_t{
    int parent;
    int son[2];
    int sn;
    int size;
    int cha;    //��ֵ����һ�ؼ��֣�С��
    int hou;    //��һ�������ڶ��ؼ��֣�С��
    int maxhou; //���ĺ�һ����
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
    Node[t].size = 1;
    Node[t].maxhou = Node[t].hou;
    int son = Node[t].son[LEFT];
    if(son) Node[t].size += Node[son].size, Node[t].maxhou = max(Node[t].maxhou,Node[son].maxhou);
    son = Node[t].son[RIGHT];
    if(son) Node[t].size += Node[son].size, Node[t].maxhou = max(Node[t].maxhou,Node[son].maxhou);
}

inline void _link(int parent,int sn,int son){
    Node[son].parent = parent;
    Node[son].sn = sn;
    Node[parent].son[sn] = son;
}

void _rotate(int t){
    int p = Node[t].parent;
    int sn = Node[t].sn;
    int osn = sn ^ 1;
    _link(p,sn,Node[t].son[osn]);
    _link(Node[p].parent,Node[p].sn,t);
    _link(t,osn,p);
    _pushUp(p);
}

void _splay(int&root,int p,int t){
    int pp;
    while( (pp=Node[t].parent) != p ){
        if(Node[pp].parent!=p) Node[pp].sn==Node[t].sn?_rotate(pp):_rotate(t);
        _rotate(t);
    }
    _pushUp(t);
    if(0==p) root = t;
}

bool _cmp(int cha,int hou,int t){
    return cha<Node[t].cha || (cha==Node[t].cha&&hou<Node[t].hou);
}
//���Ҳ�ֵ
int _advance(int root,int&p,int cha,int hou){
    int t = root;
    while( t && (Node[t].cha != cha || Node[t].hou != hou) ){
        p = t;
        t = Node[t].son[_cmp(cha,hou,t)?LEFT:RIGHT];
    }
    return t;
}

//��֤���ظ�
int insert(int&root,int cha,int hou){
    int p=0;
    int t = _advance(root,p,cha,hou);

    if(0==t){
        t = ++toUsed;
        Node[t].size = 1;
        Node[t].cha = cha;
        Node[t].hou = Node[t].maxhou = hou;
        _link(p,_cmp(cha,hou,p)?LEFT:RIGHT,t);
        _pushUp(p);
    }else{
        throw runtime_error("insert repeated element");
    }
    _splay(root,0,t);
    return t;
}

//��֤����
void remove(int&root,int cha,int hou){
    int p;
    int t = _advance(root,p,cha,hou);
    _splay(root,0,t);

    if(Node[root].son[LEFT]==0){//ֱ�Ӿ����Ҷ���
        root = Node[t].son[RIGHT];
        Node[root].parent = 0;
        return;
    }
    //����Ӵ���
    int tt = Node[t].son[LEFT];
    while(Node[tt].son[RIGHT]) tt = Node[tt].son[RIGHT];
    _splay(root,root,tt);

    _link(tt,RIGHT,Node[t].son[RIGHT]);
    Node[tt].parent = 0;
    _pushUp(tt);
    root = tt;
    return;
}

multiset<int> TreeA;
typedef multiset<int>::iterator it_t;
it_t Ita,Itb;
int Root = 0;

void do1(int x){
    int cnt = TreeA.count(x);
    if(cnt>1){
        TreeA.insert(x);
    }else if(1==cnt){
        TreeA.insert(x);
        //��B����(0,x)
        insert(Root,0,x);
    }else{
        Ita = Itb = TreeA.insert(x);
        if(Ita!=TreeA.begin()){//B����(x-ǰ��x)
            --Itb;
            //(x-*Itb,x)
            insert(Root,x-*Itb,x);
        }
        Itb = Ita;
        if(++Itb!=TreeA.end()){//B����(��-x����)
            //(*Itb-x,*Itb)
            insert(Root,*Itb-x,*Itb);
        }

        //B�л�Ҫɾ��һ��Ԫ��(��-ǰ,��)
        if(Ita!=TreeA.begin()&&Itb!=TreeA.end()){
            remove(Root,*Itb-*(--Ita),*Itb);
        }
    }
}

void do2(int x){
    int cnt = TreeA.count(x);
    Ita = Itb = TreeA.find(x);
    if(1==cnt){
        if(Itb!=TreeA.begin()){//ɾ��(x-ǰ,x)
            --Itb;
            //(x-*Itb,x)
            remove(Root,x-*Itb,x);
        }
        Itb = Ita;
        if(++Itb!=TreeA.end()){//ɾ��(��-x,��)
            //(*Itb-x,*Itb)
            remove(Root,*Itb-x,*Itb);
        }
        //��Ҫ����һ����(��-ǰ,��)
        if(Ita!=TreeA.begin()&&Itb!=TreeA.end()){
            insert(Root,*Itb-*(--Ita),*Itb);
            ++Ita;//��ԭ�����滹Ҫɾ��
        }
    }else if(2==cnt){//ɾ��(0,x)
        //(0,x)
        remove(Root,0,x);
    }else{//cnt>2 do nothing

    }
    TreeA.erase(Ita);
}

//�Ƿ��ҵ�ab����xС����a+b>x
bool do31(int x){
    if(Ita==Itb){//x����TreeA����Ita��xҪ��
        if(Ita==TreeA.begin()) return false;
        if(--Ita==TreeA.begin()) return false;
        --Ita;--Itb;
        return *Ita+*Itb > x;
    }
    int cnt = TreeA.count(x);
    if(cnt>=2) return true;
    //����countΪ1�����
    return Ita != TreeA.begin();//ֻҪx������С�ľ���
}

//��root������key��ǰ�������ص��ǽڵ㣬key�϶���������
int pred(int&root,int cha,int hou){
    int p,son;
    int t = _advance(root,p,cha,hou);
    //�������p��Ѱ��
    _splay(root,0,p);
    if(!_cmp(cha,hou,p)) return p;
    son = Node[p].son[LEFT];
    if(0==son) return 0;
    //�����������
    t = son;
    while(Node[t].son[RIGHT]) t = Node[t].son[RIGHT];
    return t;
}

//������һ����ֵ��xС�ģ���hou��x���
bool do32(int x){
    //��x��ǰ��
    int t = pred(Root,x,-1);
    if(0==t) return false;
    _splay(Root,0,t);
    //���ڵ��Լ�����Ӷ��ǲ�ֵ��xС��
    if(Node[Root].hou>x) return true;
    t = Node[Root].son[LEFT];
    return t && Node[t].maxhou > x;
}
void do3(int x){
    if (TreeA.size()<2){
        puts("No");
        return;
    }
    pair<it_t,it_t> pp = TreeA.equal_range(x);
    Ita = pp.first;
    Itb = pp.second;
    if(do31(x)) {
        puts("Yes");
        return;
    }
    puts(do32(x)?"Yes":"No");
}

void dispTreeA(){
    cout<<"TreeA:"<<endl;
    for(Ita=TreeA.begin();Ita!=TreeA.end();++Ita){
        cout<<*Ita<<" ";
    }
    cout<<endl;
}
void dispNode(int t){
    printf("%d:(%d %d %d)\n",t,Node[t].cha,Node[t].hou,Node[t].maxhou);
    printf("(parent = %d, LEFT = %d, RIGHT = %d)\n",Node[t].parent,Node[t].son[LEFT],Node[t].son[RIGHT]);
}
void _dispTreeBIter(int t){
    if(Node[t].son[LEFT]) _dispTreeBIter(Node[t].son[LEFT]);
    dispNode(t);
    if(Node[t].son[RIGHT]) _dispTreeBIter(Node[t].son[RIGHT]);
}
void dispTreeB(){
    cout<<"TreeB:"<<endl;
    if(Root) _dispTreeBIter(Root);
}
int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int q = getUnsigned(),cmd,x;
    for(int iq=1;iq<=q;++iq){
        //cout<<iq<<"-------------------"<<endl;
        if(iq==8){
            int x = 5;
        }
        switch(getUnsigned()){
        case 1:do1(getUnsigned());break;
        case 2:do2(getUnsigned());break;
        case 3:do3(getUnsigned());break;
        }
        //dispTreeA();dispTreeB();
    }

    return 0;
}
