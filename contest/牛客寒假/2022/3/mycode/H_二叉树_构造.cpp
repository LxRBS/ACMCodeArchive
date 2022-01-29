/**
 * ����������A��B��B�������ɴ���ת���Եõ�A����һ�����е���ת����
 * ����A�����ӣ����ϵ��£���B�еĶ�Ӧ�ڵ�����λ���ɣ����N^2/2����ת
*/
#include<bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 1010;
#endif

int const LEFT = 0;
int const RGHT = 1;

int N;
int A[SIZE][2], B[SIZE][2];
vector<int> Ans;

struct _t{
    int parent;
    int son[2];
    int sn;
    int name; // useless in fact
}NodeA[SIZE], NodeB[SIZE];

inline void _link(int parent,int sn,int son){
    NodeB[son].parent = parent;
    NodeB[son].sn = sn;
    NodeB[parent].son[sn] = son;
}

void _rotate(int t){
    Ans.push_back(t);

    int p = NodeB[t].parent;
    int sn = NodeB[t].sn;
    int osn = sn ^ 1;
    //����ȷ�����Ը��ӹ�ϵ
    _link(p,sn,NodeB[t].son[osn]);
    _link(NodeB[p].parent,NodeB[p].sn,t);
    _link(t,osn,p);
}

void _splay(int&root,int p,int t){
    int pp;
    while( (pp=NodeB[t].parent) != p ){
        if(NodeB[pp].parent!=p) NodeB[pp].sn==NodeB[t].sn?_rotate(pp):_rotate(t);
        _rotate(t);
    }

    if(0==p) root = t;//�ĸ�
}

int RootA, RootB;

void build(int const a[][2], _t t[], int&root){
    int flag[SIZE] = {0};
    for(int i=1;i<=N;++i){
        t[t[t[i].name = i].son[LEFT] = a[i][LEFT]].parent
        = t[t[i].son[RGHT] = a[i][RGHT]].parent
        = i;   
        t[a[i][LEFT]].sn = LEFT;
        t[a[i][RGHT]].sn = RGHT;     
    }

    for(int i=1;i<=N;++i)if(t[i].parent == 0){
        root = i; break;
    }

    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getUnsigned();
    for(int i=1;i<=N;++i) A[i][LEFT] = getUnsigned(), A[i][RGHT] = getUnsigned();
    for(int i=1;i<=N;++i) B[i][LEFT] = getUnsigned(), B[i][RGHT] = getUnsigned();
    build(A, NodeA, RootA);
    build(B, NodeB, RootB);
    
    queue<int> qa, qb;
    qa.push(RootA);
    qb.push(RootB);
    while(!qa.empty()){
        int sz = qa.size();
        while(sz--){
            auto ha = qa.front(); qa.pop();
            auto hb = qb.front(); qb.pop();
            if(ha != hb){
                /// ��B���е�ha��ת����Ӧλ��
                int parent = NodeA[ha].parent;
                _splay(RootB, parent, ha);
            }
            
            int son = NodeA[ha].son[LEFT];
            if(son) qa.push(son);
            son = NodeA[ha].son[RGHT];
            if(son) qa.push(son);

            son = NodeB[ha].son[LEFT];
            if(son) qb.push(son);
            son = NodeB[ha].son[RGHT];
            if(son) qb.push(son);
        }
    }
    printf("%d\n", Ans.size());
    for(auto i: Ans)printf("%d\n", i);
    return 0;
}