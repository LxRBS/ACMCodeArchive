/**
 * �ɳ־û��߶���ģ����
 * ʵ��һ��������ʷ�汾������ 
 * v 1 pos value: ���ݰ汾v�����ݸ���һ���°棬����posλ�õ�ֵ��Ϊvalue
 * v 2 pos: ���ݰ汾v�����ݸ���һ���°棬�����posλ�õ�ֵ
 * ʹ���߶��������棬���ڵ��ֵ����ν���ؼ���Ҷ�ӽڵ���Ҫ�����Ӧ����Ԫ��
 * ������ʹ��ָ��ָ����Թ�������ݣ�������Ҫʹ����ʽ�洢��ʽ�Ķ�����
 * ÿ���޸Ĵ�������ʼ������޸�logN���ڵ㣬��ÿ��Ҫ�޸ĵĽڵ�����ȸ��ƣ��ٸ�
 * ��ѯ����ֱ�Ӳ顣
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
	int son[2];   // ָ�����Ҷ��ӣ����豣�����ڵ���Ϣ
	value_t peak; // �������ֵ
}Node[SIZE*30];
int toUsed = 0;

/// �����½ڵ�
inline int _newNode(){
	if(toUsed+1>=SIZE*30) while(1);
	memset(Node+(++toUsed), 0, sizeof(_t));
	return toUsed;
}

/// ����һ���½ڵ㣬�����Ǹ���old�ڵ�
inline int _newNode(int old){
	if(toUsed+1>=SIZE*30) while(1);
    memcpy(Node+(++toUsed), Node+old, sizeof(_t));
	return toUsed;
}

inline void _pushUp(int t){
	Node[t].peak = max(Node[Node[t].son[LEFT]].peak, Node[Node[t].son[RIGHT]].peak);
}

/// ��������Ҫ��̬����ڵ�
void build(int &t, int s, int e){
    t = _newNode();
	if(s == e){
		Node[t].peak = getInt();
		return;
	}

	int mid = (s + e) >> 1;
	build(Node[t].son[LEFT], s, mid);
	build(Node[t].son[RIGHT], mid+1, e);
	// _pushUp(t); // ��������pushUp
}

/// ��posλ���޸ĳ�newValue���ϰ汾ά�ֲ��䣬�޸Ļ��������°汾��
void modify(int &t, int old, int s, int e, int pos, int newValue){
    t = _newNode(old);
	if(s == e){ // ��ͷ�ˣ�����Ҫ������ڵ�
        Node[t].peak = newValue;
		return;     
	}        

	int mid = (s + e) >> 1;
	if(pos <= mid) modify(Node[t].son[LEFT], Node[old].son[LEFT], s, mid, pos, newValue);
	else modify(Node[t].son[RIGHT], Node[old].son[RIGHT], mid+1, e, pos, newValue);
	// _pushUp(t); // ��������pushUp
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
/// һ������ô����汾��ÿ���汾һ����
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
		if(1 == op){ // �޸İ汾v
            value = getInt();
            modify(Root[q], Root[v], 1, N, loc, value);
		}else{
            printf("%d\n", query(Root[v], 1, N, loc));
			Root[q] = Root[v]; // ��ѯ����ҲҪ��ֵһ���汾
		}

	}
    return 0;
}