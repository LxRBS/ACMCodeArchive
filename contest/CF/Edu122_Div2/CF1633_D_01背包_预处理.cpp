/**
 * 有一个长度为N的全1数组A，再给定一个数组B
 * 对任意Ai，可以经过一次操作令Ai=Ai+Ai/x, 其中x为任意正数
 * 操作最多进行K次。
 * 如果能够将Ai变成Bi，则可以收获Ci，问最大收获是多少
 * K在1E6，N在1E3，B数值在1E3
 * 显然将某个1变成Bi，将付出xi次操作获得Ci，而操作总数在K
 * 因此这是一个01背包，只需求出xi即可
 * 而xi可以使用广搜得到
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
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
int const SIZE = 15;
#else
int const SIZE = 1010;
#endif



int N, K;
int B[SIZE], C[SIZE];
int Cost[SIZE] = {0, 0, 1};

void init(){
    queue<int> q;
    q.push(2);
	while(!q.empty()){
		int h = q.front(); q.pop();
		for(int t,i=1;i<=h;++i){
            t = h + h / i;
			if(t >= SIZE || Cost[t]) continue;
			Cost[t] = Cost[h] + 1;
			q.push(t);
		}
	}
}

int D[1000010];

int proc(){
	fill(D, D+K+1, 0);
	for(int i=1;i<=N;++i){
		for(int v=K;v>=Cost[B[i]];--v){
			D[v] = max(D[v], D[v-Cost[B[i]]]+C[i]);
		}
	}
	return D[K];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    init();  
    int nofkase = getInt();
	while(nofkase--){
		N = getInt(); K = getInt();
		for(int i=1;i<=N;++i) B[i] = getInt();
		for(int i=1;i<=N;++i) C[i] = getInt();
		printf("%d\n", proc());
	}
    return 0;
}
