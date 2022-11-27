/**
 * N个任务，第i个任务可以得到Ai个金币，一天只能做一个任务
 * 总目标是C个金币，总时限是D天。
 * 同一个任务必须间隔K天才能再次进行。
 * 注意K可以为0，即明天就能再做
 * 问为了达到目标，最大的K是多少。
 * 显然二分
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

using llt = long long;
llt getInt(){
	llt sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 17;
#else
int const SIZE = 2E5+13;
#endif

llt N, C, D;
llt A[SIZE];

bool check(int x){
    if(x == N - 1){
        llt seg = D / N;
        llt yu = D % N;
        llt sum = accumulate(A, A+N, 0LL);
        llt yy = accumulate(A, A+yu, 0LL);
        return sum * seg + yy >= C;
    }

    if(x < N - 1){
        llt jie = x + 1;
        llt seg = D / jie;
        llt yu = D % jie;
        llt sum = accumulate(A, A+jie, 0LL);
        llt yy = accumulate(A, A+yu, 0LL);
        return sum * seg + yy >= C;
    }

    llt jie = x + 1;
    llt seg = D / jie;
    llt yu = D % jie;
    llt sum = accumulate(A, A+N, 0LL);
    llt yy = accumulate(A, A+min(N, yu), 0LL);
    return sum * seg + yy >= C;
}

void proc(){
    sort(A, A+N, greater<llt>());
    llt sum = accumulate(A, A+min(N, D), 0LL);
    if(sum >= C) return (void)printf("Infinity\n");

    int left = 0, right = D, mid;
    do{
        int mid = (left + right) >> 1;
        if(check(mid)) left = mid + 1;
        else right = mid - 1;
    }while(left <= right);
    int ans = right;
    if(-1 == ans) return (void)printf("Impossible\n");
    printf("%d\n", ans);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        C = getInt();
        D = getInt();
        for(int i=0;i<N;++i) A[i] = getInt();
        proc();
    }
    return 0;
}
