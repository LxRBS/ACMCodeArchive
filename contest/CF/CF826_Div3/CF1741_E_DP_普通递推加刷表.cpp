/**
 * 假设有一个数组X，将其分为若干段，并且将每一段的长度加在左边或者右边形成一个新的段，
 * 再拼起来，得到一个新的数组A
 * 例如: [1, 2, 3, 1, 2, 3]，可以分为三段: [1], [2, 3, 1], [2, 3]
 * 再加上长度，或左或右，有可能得到:[11, 3231, 223]或者[11,2313, 232]等
 * 现在给定数组A，问是否可能是这样拼起来的。
 * 令Di是到i为止均可以分段的，则对每一个i
 * 如果D[i-Ai-1]是OK的，则Di也是
 * 另一方面如果D[i-1]是OK的，则以Ai为长度的也可以，即D[Ai+i]是OK的
 * 由此扫描一遍即可
 */
#include <assert.h>
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;
using mii = map<int, int>;

int N;
int A[SIZE];
int D[SIZE];

bool proc(){
	D[0] = 1;
    for(int i=1;i<=N;++i){
		if(i - A[i] >= 1 && D[i-A[i]-1]) D[i] = 1;
        if(D[i-1] && A[i] + i <= N) D[A[i]+i] = 1;
	}
	return D[N];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif   

    int nofkase = getInt();
	while(nofkase--){
        fill(D, D+(N=getInt())+1, 0);
		for(int i=1;i<=N;++i) A[i] = getInt();
		puts(proc()?"YES":"NO");
	}
    return 0;
}
