/**
 * 给定数组A，定义操作：任选一个Ai，除以2，或者除以3，在保证整除的情况下
 * 问将所有Ai变成一模一样最少需要多少次操作
 * 将每个Ai写成2^x*3^y*z的形式
 * 如果每个Ai的z不是一致的，则肯定不行，输出-1
 * 否则，找到最小的x和y，这显然就是变化的目标
 * 然后做一遍for循环即可
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
int const SIZE = 13;
#else
int const SIZE = 1E3+13;
#endif

int N;
int A[SIZE];
int P2[SIZE];
int P3[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    N = getInt();

    int z = -1;
    int k2 = 1;
    int k3 = 1;
    for(int a,i=1;i<=N;++i){
        a = A[i] = getInt();
        while(a % 2 == 0){
            a >>= 1; ++P2[i];
        }
        while(a % 3 == 0){
            a /= 3; ++P3[i];
        }
        if(-1 == z){
            z = a;
        }else if(z != a){
            return puts("-1"), 0;
        }else{
            ;;
        }
        if(P2[k2] > P2[i]) k2 = i;
        if(P3[k3] > P3[i]) k3 = i;
    }
    int ans = 0;
    k2 = P2[k2], k3 = P3[k3];
    for(int i=1;i<=N;++i){
        ans += P2[i] - k2 + P3[i] - k3;
    }
    printf("%d\n", ans);
    return 0;
}