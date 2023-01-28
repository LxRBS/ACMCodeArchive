/**
 * 给定字符串S和T，S比较长。令T的长度记作N。
 * 字符串由小写字母和问号构成，问号可以匹配任意字母
 * 对x=0,1,2,...,N，由S的前x个字母和后N-x个字母构成的字符串，是否能够与T匹配，回答N+1次
 * 字符串长度在3E5。
 * 首先求出S的后N个字母与T的不匹配的数量，记作Suf
 * 再令Pre为S的前x个字母与T的不匹配数量
 * 然后for x=1,2,...,N，对每一个x，处理一下前面新加的一个位置后面减去的一个位置
 * 因此可以O(1)维护Pre与Suf，对每个位置，当二者全为0时是可以匹配的。
 * O(N)即可
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
int const SIZE = 3E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

int N, M;
char S[SIZE], T[SIZE];
int Cnt;
int Pre;

bool proc(int pos){
    int old = pos + M - N;
	if(S[old] == '?' || T[pos] == '?' || S[old] == T[pos]) ;
	else --Cnt;
	if(S[pos] == '?' || T[pos] == '?' || S[pos] == T[pos]) ;
	else ++Pre;
	if(0 == Cnt && 0 == Pre) return true;
	return false;
}

void proc(){
	for(int i=0,j=M-N;i<N;++i,++j){
		if(S[j] == '?' || T[i] == '?' || S[j] == T[i]) ;
		else ++Cnt;
	}	
	puts(Cnt ? "No" : "Yes");
	for(int i=0;i<N;++i){
		puts(proc(i) ? "Yes" : "No");
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    scanf("%s%s", S, T);
	N = strlen(T);
	M = strlen(S);
    proc();
    return 0;
}