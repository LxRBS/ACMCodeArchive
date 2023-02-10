/**
 * 给定A、B数组，做如下Q次操作：
 * x s e: 把x数组[s..e]区间中的每个元素分别加上F1,F2,...,F[e-s+1]
 * 每次操作之后问A是否等于B
 * 首先考虑成段操作Fib数列，做一个差分
 * 原数组      差分
 * 123456    1 2-1 3-2-1 4-3-2 5-4-3 6-5-4
 * 假设1到4假设Fib数列，则
 * 原数组                     差分
 * 1+F1 2+F2 3+F3 4+F4 5 6   1+F1 2-1 3-2-1 4-3-2 5-4-3-F4-F3 6-5-4-F4
 * 对比一下，发现差分数组只有3项不一样
 * 即原数组的成段加Fib数列，转换成了差分数组上的3个单点操作
 * 再考虑判断相等，做一个令C=A-B，如果C全零，则A、B相等
 * 再对C做一个差分得到D，则C全零等价于D全零
 * 因此用一个计数器记录D的非零个数即可。
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

char getChar(){
    char ch = __hv007();
    while(!isalpha(ch)) ch = __hv007();
    return ch;
}

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 20;
#else
int const SIZE = 300010;
#endif

llt Mod;
inline llt ABS(llt x){return (x%=Mod)>=0?x:x+Mod;}

int N, Q;

llt A[SIZE];
llt B[SIZE];
llt C[SIZE];
llt D[SIZE];
llt F[SIZE];

inline int f(llt &a, llt b){
    llt tmp = ABS(a + b);
    if(0==a&&tmp) return a=tmp, 1;
    if(0==tmp&&a) return a=tmp, -1;
    return a=tmp, 0;
}

void proc1(){
    for(int a,b,q=1;q<=Q;++q){
        char cmd = getChar();
        a = getInt(); b = getInt();
        if('A' == cmd){
            puts((C[1]=ABS(C[1]+1LL))?"NO":"YES");
        }else if('B' == cmd){
            puts((C[1]=ABS(C[1]-1LL))?"NO":"YES");
        }else{
            throw runtime_error("wrong cmd");
        }
    }
}

void proc0(){
        for(int a,b,q=1;q<=Q;++q){
        char cmd = getChar();
        a = getInt(); b = getInt();
        puts("YES");
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); Q = getInt();
    Mod = getInt();
    for(int i=1;i<=N;++i)A[i] = getInt();
    for(int i=1;i<=N;++i){
        C[i] = A[i] - (B[i] = getInt());
    }
    if(1 == Mod){
        proc0(); return 0;
    }
    if(1 == N){
        proc1(); return 0;
    }
    
    int cnt = 0;
    F[1] = F[2] = 1;
    if(D[1] = ABS(C[1])) ++cnt;
    if(D[2] = ABS(C[2]-C[1])) ++cnt;
    for(int i=3;i<=N;++i){
        if(D[i]=ABS(C[i]-C[i-1]-C[i-2])) ++cnt;
        F[i] = (F[i-1]+F[i-2]) % Mod;
    }

    for(int a,b,q=1;q<=Q;++q){
        char cmd = getChar();
        a = getInt(); b = getInt();
        if('A' == cmd){
            cnt += f(D[a], 1);
            if(b+1<=N) cnt += f(D[b+1], -F[b-a+2]);
            if(b+2<=N) cnt += f(D[b+2], -F[b-a+1]);
        }else if('B' == cmd){
            cnt += f(D[a], -1);
            if(b+1<=N) cnt += f(D[b+1], F[b-a+2]);
            if(b+2<=N) cnt += f(D[b+2], F[b-a+1]);
        }else{
            throw runtime_error("wrong cmd");
        }
        puts(cnt?"NO":"YES");
    }
    return 0;
}
