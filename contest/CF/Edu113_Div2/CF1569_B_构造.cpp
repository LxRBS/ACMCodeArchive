/**
 N个选手，两两比赛。选手分两类，一类是一场都不想输，另一类是想至少赢一场
 比赛结果有胜平负三种。
 问如何操纵比赛，使得每个选手都能达成目标
 不想输的人，跟其他所有人都打平即可。
 至少赢一场的人构成一个环即可。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef long long llt;

llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE =66;
#else 
int const SIZE = 66;
#endif

#define pb push_back
typedef vector<int> vi;

int N;
char A[SIZE];

void proc(){
	int cnt1 = 0, cnt2 = 0;
	vi v1, v2;
	for(int i=0;i<N;++i){
		if(A[i]=='1') { ++cnt1; v1.pb(i);}
		else {++cnt2;v2.pb(i);}
	}
	if(1==cnt2 || 2==cnt2){
		puts("NO");
		return;
	}

    puts("YES");
    char b[55][55] = {0};
	for(int i=0;i<N;++i)for(int j=0;j<N;++j){
		if(i==j){
			b[i][j] = 'X';
		}else{
			b[i][j] = '=';
		}
	}

	if(cnt2) v2.pb(v2[0]);
	for(int i=0,n=v2.size()-1;i<n;++i){
		b[v2[i]][v2[i+1]] = '+';
        b[v2[i+1]][v2[i]] = '-';
	}

	for(int i=0;i<N;++i){
		puts(b[i]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%d%s", &N, A);
        proc();
	}
	return 0;
}
