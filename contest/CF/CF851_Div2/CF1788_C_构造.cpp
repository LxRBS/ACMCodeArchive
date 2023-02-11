/**
 * 给定N，用1到2N这2N个数恰好构造出N对数，使得这N对数之和构成一个连续的序列
 * 令x为序列的第一个数，则 x + (x + 1) + ... + (x + N - 1) = 1 + ... + 2N
 * 所以 x = (3N + 3) / 2，所以N必须为奇数，偶数无解
 * 观察一下可按如下构造：令 a = 2N, b = 1
 * b按照1、3、5、7增长，a每次减－，直到达到最大值(5N+1)/2
 * 再然后b按照2/4/6/8增长，a每次减一。
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

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;

int N;

void proc(){
    if(!(N & 1)) return (void)printf("No\n");
    printf("Yes\n");
    int c = N;
    auto limit = 5 * N + 1 >> 1;
    int a = N << 1, b = 1;
    while(1){
        --c;
        printf("%d %d\n", a, b);
        if(a + b == limit) break;
        b += 2;
        a -= 1;
    }
    if(0 == c) return;
    b = 2;
    a -= 1;
    while(1){
        printf("%d %d\n", a, b);
        if(!--c) break;
        b += 2;
        a -= 1;
    }
    return;
} 

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        proc();
    }
    return 0;
}