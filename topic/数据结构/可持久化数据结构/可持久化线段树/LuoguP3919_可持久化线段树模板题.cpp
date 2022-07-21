/**
 * 可持久化线段树模板题
 * 实现一个带有历史版本的数组 
 * v 1 pos value: 根据版本v的内容复制一个新版，并将pos位置的值改为value
 * v 2 pos: 根据版本v的内容复制一个新版，并输出pos位置的值
 * 使用线段树来保存，父节点的值无所谓，关键是叶子节点需要保存对应数组元素
 * 本质上使用指针指向可以共享的内容，所以需要使用链式存储格式的二叉树
 * 每次修改从树根开始，最多修改logN个节点，对每个要修改的节点均是先复制，再改
 * 查询可以直接查。
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100001];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 106;
#else
int const SIZE = 1E6+7;
#endif

int const LEFT = 0;
int const RIGHT = 1;

struct _t{
	using value_t = int;
	int son[2];   // 指向左右儿子，无需保留父节点信息
	value_t peak; // 保存最大值
}Node[SIZE*30];
int toUsed = 0;

/// 分配新节点
inline int _newNode(){
	if(toUsed+1>=SIZE*30) while(1);
	memset(Node+(++toUsed), 0, sizeof(_t));
	return toUsed;
}

/// 分配一个新节点，内容是复制old节点
inline int _newNode(int old){
	if(toUsed+1>=SIZE*30) while(1);
    memcpy(Node+(++toUsed), Node+old, sizeof(_t));
	return toUsed;
}

inline void _pushUp(int t){
	Node[t].peak = max(Node[Node[t].son[LEFT]].peak, Node[Node[t].son[RIGHT]].peak);
}

/// 建树，需要动态分配节点
void build(int &t, int s, int e){
    t = _newNode();
	if(s == e){
		Node[t].peak = getInt();
		return;
	}

	int mid = (s + e) >> 1;
	build(Node[t].son[LEFT], s, mid);
	build(Node[t].son[RIGHT], mid+1, e);
	// _pushUp(t); // 本题无需pushUp
}

/// 把pos位置修改成newValue，老版本维持不变，修改会体现在新版本上
void modify(int &t, int old, int s, int e, int pos, int newValue){
    t = _newNode(old);
	if(s == e){ // 到头了，就是要改这个节点
        Node[t].peak = newValue;
		return;     
	}        

	int mid = (s + e) >> 1;
	if(pos <= mid) modify(Node[t].son[LEFT], Node[old].son[LEFT], s, mid, pos, newValue);
	else modify(Node[t].son[RIGHT], Node[old].son[RIGHT], mid+1, e, pos, newValue);
	// _pushUp(t); // 本题无需pushUp
	return;
}

int query(int t, int s, int e, int pos){
    if(s == e){
		return Node[t].peak;
	}

	int mid = (s + e) >> 1;
	if(pos <= mid) return query(Node[t].son[LEFT], s, mid, pos);
	return query(Node[t].son[RIGHT], mid+1, e, pos);
}

int N, M;
/// 一共有这么多个版本，每个版本一个树
int Root[SIZE]; 

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    N = getInt(); M = getInt();
	build(Root[0], 1, N);
	for(int v,op,loc,value,q=1;q<=M;++q){
		v = getInt();
		op = getInt();
		loc = getInt();
		if(1 == op){ // 修改版本v
            value = getInt();
            modify(Root[q], Root[v], 1, N, loc, value);
		}else{
            printf("%d\n", query(Root[v], 1, N, loc));
			Root[q] = Root[v]; // 查询操作也要求赋值一个版本
		}

	}
    return 0;
}