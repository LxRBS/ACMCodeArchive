/**
 * 给定一个长度为N的数组A，对任意Ai可以做整除2的操作，可以操作任意次
 * 问能否将A变为1~N的一个排列
 * N在50，Ai在1E9
 * 首先把所有Ai除2到N以下，其次依次记录即可，直到完成或者出现矛盾
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
int const SIZE = 66;
#endif

typedef long long llt;

vector<int> Vec[51];

void init(){
	for(int i=1;i<=50;++i){
		Vec[i].push_back(i);
		while(Vec[i].back() != 1) Vec[i].push_back(Vec[i].back()>>1);
	}
}

int N;
int A[SIZE];

int f(int a){
	while(a > N) a >>= 1;
	return a;
}

bool proc(){
	int flag[SIZE] = {0};
    for(int i=1;i<=N;++i){
		++flag[A[i] = f(A[i])];
	}
	for(int i=N;i;--i){
		if(0 == flag[i]) return false;
		if(flag[i] > Vec[i].size()) return false;
		flag[i/2] += flag[i] - 1;
	}
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    init();
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
	    for(int i=1;i<=N;++i) A[i] = getInt();
		puts(proc()?"YES":"NO");	
	}
    return 0;
}
