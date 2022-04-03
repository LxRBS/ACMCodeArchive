/**
 * 给定N个字符串作为字典，N在18
 * 每次选择一个字典，使用其中的字母生成一个长度为L的字符串
 * 问一共可以生成多少个不同的字符串
 * 假设一格字典中用n个不同的字母，显然用这个字典生成L的字符串数量是n^L。
 * 用容斥原理即可
 * 可以不需要维护字符串，维护位就行了
 * 不过用字符串也可以过
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
int const SIZE = 20;
#else
int const SIZE = 22+5;
#endif

typedef long long llt;
typedef pair<int, int> pii;
llt const MOD = 998244353;
llt C[30][30];
void initC(){
    C[0][0] = 1;
	for(int i=1;i<=26;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j) C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
	}
}

llt powerMod(llt a, llt n){
	a %= MOD;
	llt ans = 1LL;
	while(n){
		if(n & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		n >>= 1; 
	}
	return ans;
}

int N, L;
char A[SIZE][30];

llt f(char const a[], int n){
    llt ans = 0;
    // for(int i=1;i<=n;++i){
		(ans += powerMod(n, L)) %= MOD;
	// }
	return ans;
}

llt proc(){
	int sz[22] = {0};
	for(int i=0;i<N;++i){
        int t = strlen(A[i]);
		sort(A[i], A[i]+t);
		t = unique(A[i], A[i]+t) - A[i];
		A[i][t] = '\0';
		sz[i] = t;
	}
	llt ans = 0;
    for(int i=1,n=1<<N;i<n;++i){		
		char cur[30] = "abcdefghijklmnopqrstuvwxyz";
		int len = 26;
		char tmp[30] = {0};
        /// each bit
		int pos = 0;
		for(int j=0;j<N;++j){
			if((1<<j) & i){
				pos ^= 1;
                set_intersection(cur, cur+len, A[j], A[j]+sz[j], tmp);
				/// 拷贝
				len = strlen(tmp);
                copy(tmp, tmp+len, cur);
				cur[len] = '\0';
				memset(tmp, 0, sizeof(tmp));
				if(0 == len) break;
			}            
		}
        if(len){
			llt tmp = f(cur, len);
			if(pos & 1){
				(ans += tmp) %= MOD;
			}else{
                (ans += MOD - tmp) %= MOD;
			}			
		}
	}
	return ans;
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    initC();
    scanf("%d%d", &N, &L);
	for(int i=0;i<N;++i)scanf("%s", A[i]);
	cout<<proc()<<endl;
    return 0;
}

