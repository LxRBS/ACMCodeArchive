/**
    三种操作
    1 x: 插入一个数
    2 x: 删除x
    3 x: 在集合里面找2个数，与x形成三角形
    两个平衡二叉树，树A保存x本身，树B保存(相邻数之差,后数)
    1操作: A如果有多个x，则插入x，
           A如果只有1个x，则插入x，B插入(0,x)
           A如果没有x，则插入x，B插入(x-前,x)与(后-x,后)
    2操作: A删除x,A里面如果没有x，则删除(x-前,x)与(后-x,后)
           A里面只剩一个x，删除(0,x)
    3操作：A里面找到x前面最近的两个数，如果a+b>x，则yes
           B里面找(u,v)，满足u<x,v>b
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
    int cha;    //差值，第一关键字，小于
    int hou;    //后一个数，第二关键字，小于
    int maxhou; //最大的后一个数
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
//查找差值
int _advance(int root,int&p,int cha,int hou){
    int t = root;
    while( t && (Node[t].cha != cha || Node[t].hou != hou) ){
        p = t;
        t = Node[t].son[_cmp(cha,hou,t)?LEFT:RIGHT];
    }
    return t;
}

//保证无重复
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

//保证存在
void remove(int&root,int cha,int hou){
    int p;
    int t = _advance(root,p,cha,hou);
    _splay(root,0,t);

    if(Node[root].son[LEFT]==0){//直接就是右儿子
        root = Node[t].son[RIGHT];
        Node[root].parent = 0;
        return;
    }
    //左儿子存在
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
        //树B里面(0,x)
        insert(Root,0,x);
    }else{
        Ita = Itb = TreeA.insert(x);
        if(Ita!=TreeA.begin()){//B插入(x-前，x)
            --Itb;
            //(x-*Itb,x)
            insert(Root,x-*Itb,x);
        }
        Itb = Ita;
        if(++Itb!=TreeA.end()){//B插入(后-x，后)
            //(*Itb-x,*Itb)
            insert(Root,*Itb-x,*Itb);
        }

        //B中还要删除一个元素(后-前,后)
        if(Ita!=TreeA.begin()&&Itb!=TreeA.end()){
            remove(Root,*Itb-*(--Ita),*Itb);
        }
    }
}

void do2(int x){
    int cnt = TreeA.count(x);
    Ita = Itb = TreeA.find(x);
    if(1==cnt){
        if(Itb!=TreeA.begin()){//删除(x-前,x)
            --Itb;
            //(x-*Itb,x)
            remove(Root,x-*Itb,x);
        }
        Itb = Ita;
        if(++Itb!=TreeA.end()){//删除(后-x,后)
            //(*Itb-x,*Itb)
            remove(Root,*Itb-x,*Itb);
        }
        //还要插入一个数(后-前,后)
        if(Ita!=TreeA.begin()&&Itb!=TreeA.end()){
            insert(Root,*Itb-*(--Ita),*Itb);
            ++Ita;//还原，后面还要删除
        }
    }else if(2==cnt){//删除(0,x)
        //(0,x)
        remove(Root,0,x);
    }else{//cnt>2 do nothing

    }
    TreeA.erase(Ita);
}

//是否找到ab都比x小，且a+b>x
bool do31(int x){
    if(Ita==Itb){//x不在TreeA，且Ita比x要大
        if(Ita==TreeA.begin()) return false;
        if(--Ita==TreeA.begin()) return false;
        --Ita;--Itb;
        return *Ita+*Itb > x;
    }
    int cnt = TreeA.count(x);
    if(cnt>=2) return true;
    //这是count为1的情况
    return Ita != TreeA.begin();//只要x不是最小的就行
}

//在root树上找key的前驱，返回的是节点，key肯定不在树上
int pred(int&root,int cha,int hou){
    int p,son;
    int t = _advance(root,p,cha,hou);
    //否则根据p来寻找
    _splay(root,0,p);
    if(!_cmp(cha,hou,p)) return p;
    son = Node[p].son[LEFT];
    if(0==son) return 0;
    //左儿子中最大的
    t = son;
    while(Node[t].son[RIGHT]) t = Node[t].son[RIGHT];
    return t;
}

//首先找一个差值比x小的，且hou比x大的
bool do32(int x){
    //找x的前驱
    int t = pred(Root,x,-1);
    if(0==t) return false;
    _splay(Root,0,t);
    //根节点以及左儿子都是差值比x小的
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
