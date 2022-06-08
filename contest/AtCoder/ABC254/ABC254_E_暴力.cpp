/**
 * 一个无向图，度数最大为3。Q个询问：x k。
 * 问距离x不超过k的所有节点编号之和。
 * 直接做就行了。O(40Q)。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

using llt = int;

llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2E+5;
#endif

using vi = vector<int>;

int N, M, Q;
vi G[SIZE];

int Queue[110];
unordered_set<int> Flag;

int proc(int x, int k){
	if(0 == k) return x;

    int * head = Queue;
	int * tail = Queue;
    Flag.clear();

	int ans = x;
    Flag.insert(*head++ = x);

	while(k--){
        int sz = head - tail;
		while(sz--){
			int h = *tail++;
            for(int v: G[h]){
				auto it = Flag.find(v);
				if(it == Flag.end()){
					it = Flag.insert(it, v);
					ans += v;
					*head++ = v;
				}
			}
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
	for(int a,b,i=0;i<M;++i){
		a = getInt(); b = getInt();
		G[a].push_back(b); G[b].push_back(a);
	}
	Q = getInt();
	for(int x,k,q=1;q<=Q;++q){
		x = getInt(); k = getInt();
        printf("%d\n", proc(x, k));
	}
    return 0;
}
