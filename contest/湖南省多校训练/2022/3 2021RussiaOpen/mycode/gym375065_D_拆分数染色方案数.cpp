/**
 * 给定N和K种颜色，问N的拆分数染色一共有多少种方案，N在15
 * 由于N非常小，做一个暴力求出N的拆分数的具体方案
 * 假设拆分数为c1a1+c2a2+c3a3+...
 * 不同数值之间的染色显然是不相干的，因此符合乘法原理
 * 最终只需求c个a染K种颜色的方案即可
 * 相当于c个相同的球放入K个相同的盒子中的方案总数
 * 用插板法易得为 C(c+K-1, K-1)
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
int const SIZE = 10;
#else
int const SIZE = 2E5+5;
#endif
typedef long long llt;

int Cnt[16];
int N, K;
llt Ans = 0;
llt C[31][31];
llt f(){
    vector<int> v;
	for(int i=1;i<=N;++i)if(Cnt[i])v.push_back(Cnt[i]);
	llt ans = 1;
	for(auto i: v){
        ans *= C[K+i-1][K-1];
	}
	return ans;
}

void dfs(int last, int left){
	if(0 == left){
		Ans += f();
		return;
	}
	for(int i=last;i<=left;++i){
		++Cnt[i];
		dfs(i, left-i);
		--Cnt[i];
	}
}

llt proc(){
    for(int i=1;i<=N;++i){
		++Cnt[i];
		dfs(i, N-i);
		--Cnt[i];
	}
	return Ans;
}
void initC(int n){
    C[0][0] = 1;
	for(int i=1;i<=n;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j) C[i][j] = ( C[i-1][j] + C[i-1][j-1] );
	}
}
int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    initC(30);
    N = getInt(); K = getInt();
	cout<<proc()<<endl;
    return 0;
}
