/**
 * 有一条直线，上面有N个点，每个点有一个坐标
 * 从i到N的花费为i、N之间的坐标差。
 * 可以选2个点建造传送门，过传送门的花费为T
 * 传送门的最大间距不能超过K
 * 所有人都要去N，问在哪里造传送门可以使得总花费最小
 * 显然传送门在不超过K的情况下越远越好，尺取法。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef long long llt;

llt getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}


#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 100010;
#endif

int N, K, T;
llt A[SIZE];
llt B[SIZE], C[SIZE];

void proc(){
	int ansi = -1, ansj = -1;
	llt save = -1;
	int left = 1, right = 1;
	while(1){
		while(right<=N && A[right]-A[left]<=K) ++right;
		--right;

        llt n = left;
		llt c1 = (A[right] - A[left]) * n;
		llt c2 = T * n;
        if(c2 < c1){
            llt tmpsave = c1 - c2;
			if(-1 == save || tmpsave > save){
				save = tmpsave;
				ansi = left, ansj = right;
			}
		}        
		
		if(++left == N) break;
		if(right < left) right = left;
	}
	
    if(-1==save){
        puts("-1");
		return;
	}

	printf("%d %d %lld\n", ansi, ansj, C[1]-save);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    N = getUnsigned();
	K = getUnsigned();
	T = getUnsigned();
	for(int i=1;i<=N;++i)A[i] = getUnsigned();

	if(K<=T){
		puts("-1");
		return 0;
	}

	B[N] = C[N] = 0;
	for(int i=N-1;i;--i){
		B[i] = A[N] - A[i];
		C[i] = B[i] + C[i+1];
	}

	proc();
    return 0;
}
