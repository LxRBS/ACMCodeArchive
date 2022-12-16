/**
 * 给定一个WLD的字符串，其中W表示加1，L表示减1，D表示不变
 * 特别的假设当前分数是3的倍数，则经过L也保持不变
 * 现在有若干个询问[s, e, c]，问初试分数c，经过[s, e]后的分数是多少
 * 同一字母在不同分数下表现可能不同，但是显然一共只有3种情况
 * 再考虑倍增算法，令Dijk表示分数为k，从i开始，经过长度2^j的分数变化，k只需取012即可
 * 一遍可以求取D
 * 回答的时候从s开始往前跳即可
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

int N, Q;
char S[SIZE];
/// Dijk表示分数为k，从i开始，经过长度2^j的分数变化
int D[SIZE][18][3];

void init(){
    for(int i=0;i<N;++i){
		auto d = D[i][0]; 
		switch(S[i]){
			case 'W': d[0] = d[1] = d[2] = 1; break;
			case 'D': d[0] = d[1] = d[2] = 0; break;
			case 'L': d[0] = 0; d[1] = d[2] = -1; break;
			default: assert(0);
		}
	}

	for(int j=1,tmp;(tmp=1<<j)<=N;++j){
		for(int i=0;i+tmp<=N;++i){
			auto d = D[i][j];
			auto a = D[i][j-1];
			auto b = D[i+(tmp>>1)][j-1];

			d[0] = a[0] + b[(a[0]%3+3)%3];
			d[1] = a[1] + b[((a[1]+1)%3+3)%3];
			d[2] = a[2] + b[((a[2]+2)%3+3)%3];
		}
	}

	return;
}

int log(int s, int e){
	int n = e - s + 1;
	int ans = 0;
    while((1 << ans) < n) ++ans;
	if((1 << ans) > n) --ans;
	return ans;
}

int proc(int s, int e, int c){
    int ans = c;
	int cur = s;
	while(1){
		int k = log(cur, e);
		int left = (ans % 3 + 3) % 3;
        ans += D[cur][k][left];
		cur += (1 << k);
		if(cur > e) break;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%s", &N, &Q, S);
	init();
	for(int s,e,c,q=1;q<=Q;++q){
        scanf("%d%d%d", &s, &e, &c);
		printf("%d\n", proc(s-1, e-1, c));
	}
    return 0;
}