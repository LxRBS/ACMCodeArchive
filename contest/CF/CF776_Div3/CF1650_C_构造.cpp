/**
 * 坐标轴上有M个点，每个点有坐标和权值
 * 要求挑出N个线段，满足：
 * 1. 每个线段的端点都是M个点之一
 * 2. 线段必须形成严格包含关系
 * 3. 线段端点的权值要最小
 * 实际上就是M个点中挑出2N个点使得权值和最小，排个序即可
 * 最后要求输出方案，再按坐标排个序
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
int const SIZE = 2E5+5;
#endif

struct _t{
    int idx;
    int x;
    int w;
}A[SIZE];

bool operator < (const _t&a, const _t&b){
    if(a.w != b.w) return a.w < b.w;
    if(a.x != b.x) return a.x < b.x;
    return a.idx < b.idx;
}

int N, M;

void proc(){
    sort(A+1, A+M+1);

    long long ans = 0;
    for(int i=1;i<=N+N;++i){
        ans += A[i].w;
    }
    sort(A+1, A+N+N+1, [](const _t&a, const _t&b){
        return a.x < b.x;
    });

    printf("%lld\n", ans);
    for(int i=1;i<=N;++i){
        printf("%d %d\n", A[i].idx, A[N+N+1-i].idx);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
        for(int i=1;i<=M;++i){
            A[A[i].idx=i].x = getInt();
            A[i].w = getInt();
        }
        proc();
    }
    return 0;
}
