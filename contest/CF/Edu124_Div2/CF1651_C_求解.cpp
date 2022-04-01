/**
 * 有两行计算机A和B，其中A是依次连接的，B也是依次连接的
 * 现在要求在A和B之间做若干个连接满足：删除任何一个点，整个系统仍然是连接的
 * 如果连接Ai和Bj，则费用为|Ai-Bj|
 * 求满足上述条件的最小费用
 * 稍微考虑一下可知，A1B1ANBN必须与对面的某台机器相连
 * 所以一共只有若干种情况，依次判断一下即可
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

typedef long long llt;
llt INF = 0x3F3F3F3F3F3F3F3F;
inline llt ABS(llt x){return x>=0?x:-x;}

int N;
int A[SIZE], B[SIZE];

llt f12(){
    llt t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(A[N]-B[i]) < t1){
            t1 = ABS(A[N]-B[i]);
        }
    }
    llt t2 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(B[N]-A[i]) < t2){
            t2 = ABS(B[N]-A[i]);
        }
    }
    return ABS(A[1]-B[1]) + t1 + t2;
}

llt f21(){
    llt t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(A[1]-B[i]) < t1){
            t1 = ABS(A[1]-B[i]);
        }
    }
    llt t2 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(B[1]-A[i]) < t2){
            t2 = ABS(B[1]-A[i]);
        }
    }
    return ABS(A[N]-B[N]) + t1 + t2;
}

llt f22(){
    llt ans = 0;
    llt t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(A[N]-B[i]) < t1){
            t1 = ABS(A[N]-B[i]);
        }
    }
    ans += t1;
    t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(B[N]-A[i]) < t1){
            t1 = ABS(B[N]-A[i]);
        }
    }
    ans += t1;   
    t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(A[1]-B[i]) < t1){
            t1 = ABS(A[1]-B[i]);
        }
    }
    ans += t1;
    t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(B[1]-A[i]) < t1){
            t1 = ABS(B[1]-A[i]);
        }
    }
    ans += t1;  
    return ans; 
}

llt g12(){
    llt ans = ABS(A[1]-B[N]);
    llt t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(B[1]-A[i]) < t1){
            t1 = ABS(B[1]-A[i]);
        }
    }
    ans += t1;
    t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(A[N]-B[i]) < t1){
            t1 = ABS(A[N]-B[i]);
        }
    }
    ans += t1;
    return ans;
}

llt g21(){
    llt ans = ABS(A[N]-B[1]);
    llt t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(A[1]-B[i]) < t1){
            t1 = ABS(A[1]-B[i]);
        }
    }
    ans += t1;
    t1 = INF;
    for(int i=1;i<=N;++i){
        if(ABS(B[N]-A[i]) < t1){
            t1 = ABS(B[N]-A[i]);
        }
    }
    ans += t1;  
    return ans;
}


llt proc(){
    llt ans = ABS(A[1]-B[1]) + ABS(A[N]-B[N]);
    ans = min(ans, ABS(A[1]-B[N]) + ABS(A[N]-B[1]));    
    ans = min(ans, f12());
    ans = min(ans, f21());
    ans = min(ans, f22());
    ans = min(ans, g12());
    ans = min(ans, g21());
    // ans = min(ans, g22());
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
        for(int i=1;i<=N;++i) B[i] = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}