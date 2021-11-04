/**
 * 给一圈数字染色，要求相邻的不同数字不能染一样的颜色
 * 问最少需要几种颜色，给出一种方案
 * 观察一下，猜测最多只需要3种颜色，一般2种就够了
 * 进一步观察，其实是一个判二分图问题，但这个二分图比较容易判
 * 如果全相等，答案就是1
 * 如果偶数长度，答案是2
 * 如果每对相邻的数都不相等，答案是3
 * 最后剩下的情况答案是2，但是方案比较麻烦，
 * 不相等的相邻对要分别弄成1和2，其他随意。用dfs处理
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

#define fi first
#define se second
typedef pair<int, int> pii;
typedef vector<pii> vi;

int N;
int A[SIZE];
int B[SIZE];

bool is1(){
    for(int i=2;i<=N;++i){
        if(A[1] != A[i]){
            return false;
        }
    }
    return true;
}

bool isDiff(){
    A[0] = A[N];
    for(int i=1;i<=N;++i){
        if(A[i-1] == A[i]){
            return false;
        }
    }
    return true;
}

void dfs(int index, int color){
    B[index] = color;

    int prev = index - 1;
    if(prev == 0) prev = N;
    if(B[prev] == 0 && A[prev] != A[index]) dfs(prev, color^3);

    int next = index + 1;
    if(next == N + 1) next = 1;
    if(B[next] == 0 && A[next] != A[index]) dfs(next, color^3);
}

void proc(){
    if(is1()){
        puts("1");
        for(int i=1;i<=N;++i)printf("1 ");
        puts("");
        return;
    }

    if(0 == N % 2){
        puts("2");
        for(int i=1;i<=N;i+=2)printf("1 2 ");
        puts("");
        return;
    }

    if(isDiff()){
        printf("3\n3");
        for(int i=2;i<=N;i+=2)printf(" 1 2");
        puts("");
        return;
    }

    fill(B, B+N+1, 0);
    for(int i=1;i<=N;++i)if(0==B[i]){
        dfs(i, 1);
    }

    puts("2");
    for(int i=1;i<=N;++i)printf("%d ", B[i]);
    puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
        proc();
	}
	return 0;
}