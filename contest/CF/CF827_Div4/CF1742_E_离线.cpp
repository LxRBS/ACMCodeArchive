/**
 * 给定长度为N的数组A，Ai表示第i级台阶相较于前一即的高度差
 * 再给定Q个询问，对每个询问问ki能够达到的最高高度
 * ki只能够跨上高度差小于等于ki的台阶
 * 离线，对所有询问排个序，依次回答即可
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
int const SIZE = 14;
#else
int const SIZE = 2E5+12;
#endif

using llt = long long;

int N, Q;
int A[SIZE];

struct T{
    int k;
    int pos;
}K[SIZE];

llt Ans[SIZE];

void proc(){
    sort(K, K+Q, [](T a, T b){
        if(a.k != b.k) return a.k < b.k;
        return a.pos < b.pos;
    });

    llt sum = 0;
    int cur = 0;
    for(int i=1;i<=N;++i){
        while(cur < Q && K[cur].k < A[i]){
            Ans[K[cur].pos] = sum;
            ++cur;
        }
        sum += A[i];
    }
    while(cur < Q){
        Ans[K[cur].pos] = sum; ++cur;
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); Q = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
        for(int i=0;i<Q;++i) K[K[i].pos=i].k = getInt();     
        proc();
        for(int i=0;i<Q;++i) printf("%lld ", Ans[i]);
        printf("\n");
    }
    return 0;
}

