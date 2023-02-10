/**
 * 给定N长度的数字串，要求染成红黑两色，同时红色数字串要能整除A，黑色要能整除B
 * 且红黑数字串的长度之差最小
 * N在40，所以有2^40情况。有两种办法，
 * 第一种是分成两半搜，可以在2^20log(2^20)内完成，可能还会有些log，而且数据结构比较复杂
 * 第二种办法是考虑着2^40种情况中肯定有一些状态对于结果是重复的，因此实际上没有那么多
 * 考虑(depth, rmod, bmod, rcnt)分别表示第depth位，红余数，黑余数，红数量
 * 虽然具体染色不一样，但可以达成相同的状态。因此搜一遍即可。总数是N^4。
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

int getDigit(){
    while(1){
        char ch = __hv007();
        if('0' <= ch && ch <= '9') return (int)(ch - '0');  
    }
}

#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else 
int const SIZE = 41;
#endif

typedef long long llt;
inline int ABS(int x){return x>=0?x:-x;}

int N, A, B;
int S[SIZE];
bool Flag[SIZE][SIZE][SIZE][SIZE];
char Ans[SIZE], Tmp[SIZE];
int NowCha;

void dfs(int depth, int rmod, int bmod, int rcnt){
    if(Flag[depth][rmod][bmod][rcnt]) return;
    Flag[depth][rmod][bmod][rcnt] = true;

    if(depth == N){
        if(rmod || bmod || 0 == rcnt || N == rcnt) return;
        int tmp = ABS(N - rcnt - rcnt);
        if(tmp < NowCha) {
            copy(Tmp, Tmp+N, Ans);
            NowCha = tmp;
        }
        return;
    }

    /// 只有两种情况
    Tmp[depth] = 'R';
    dfs(depth+1, (rmod*10+S[depth])%A, bmod, rcnt+1);
    Tmp[depth] = 'B';
    dfs(depth+1, rmod, (bmod*10+S[depth])%B, rcnt);
}

char* proc(){
    memset(Flag, 0, sizeof(Flag));
    NowCha = 100000;
    Ans[0] = '-', Ans[1] = '1', Ans[2] = '\0';
    Ans[N] = '\0';
    dfs(0, 0, 0, 0);
    return Ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); A = getInt(); B = getInt();
        for(int i=0;i<N;++i) S[i] = getDigit();
        printf("%s\n", proc());
    }
    return 0;
}