/**
 * 给定一个N数组A，再给定一个K，每次操作可以将一个最小元素加1，也可以将一个最大元素减1
 * 问最少要几次操作，使得数组中至少有K个相等的元素
 * 首先确定最后相等的元素的取值一定是已经数组中原来就有的
 * 将数组Aunique一下，并且记录ai的数量cnti
 * Bi表示从左往右计算到位置i时，需要的操作数量
 * BCnti表示到i时，值等于ai的数一共有多少个
 * Ci和CCnti表示从右向左计算
 * Di表示以ai为目标的满足条件的最小操作数，则Di存在几种情况：
 * 从左部分即可，从左的全部加上部分从右
 * 从右部分即可，从右的全部加上部分从左
 * minDi就是答案
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
int const SIZE = 21;
#else 
int const SIZE = 200100;
#endif

typedef long long llt;

int N, K;
llt A[SIZE];
unordered_map<llt, int> Cnt;

llt B[SIZE], C[SIZE];
int BCnt[SIZE], CCnt[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    K = getInt();
    bool flag = false;
    for(int i=1;i<=N;++i) if(++Cnt[A[i] = getInt()]>=K) flag=true;
    if(flag){
        puts("0"); return 0;
    }

    sort(A+1, A+N+1);
    N = unique(A+1, A+N+1) - A - 1;

    B[1] = 0; BCnt[1] = Cnt[A[1]];
    for(int i=2;i<=N;++i){
        B[i] = B[i-1] + BCnt[i-1] * (A[i] - A[i-1]);
        BCnt[i] = BCnt[i-1] + Cnt[A[i]];
    }
    C[N] = 0; CCnt[N] = Cnt[A[N]];
    for(int i=N-1;i>=1;--i){
        C[i] = C[i+1] + CCnt[i+1] * (A[i+1] - A[i]);
        CCnt[i] = CCnt[i+1] + Cnt[A[i]];
    }
    llt ans = 0x3F3F3F3F3F3F3F3F;
    for(int tmp, i=1;i<=N;++i){
        tmp = BCnt[i] - K;
        if(tmp >= 0){ // 从左部分即可
            ans = min(ans, B[i]-tmp);
        }else{ // 从左全部加上从右的部分
            tmp = CCnt[i] - Cnt[A[i]] + tmp;
            ans = min(ans, B[i] + C[i] - tmp);
        }
        tmp = CCnt[i] - K;
        if(tmp >= 0){ // 从右部分即可，另外从右的全部不用算了 
            ans = min(ans, C[i] - tmp);
        }
    }
    cout<<ans<<endl;
    return 0;
}