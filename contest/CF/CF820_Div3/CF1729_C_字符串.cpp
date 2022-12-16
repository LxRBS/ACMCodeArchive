/**
 * 给一个字符串，从S1跳到Sn，每一步的代价是两个字母的差的绝对值
 * 求如何跳可以使代价最小，满足代价最小的情况下要求步数最多
 * 排个序即可，但实际上不用排序
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

int N;
char S[SIZE];

void proc(){
	N = strlen(S);
	vvi pos(26, vi()); 
	for(int i=0;i<N;++i){
        pos[S[i] - 'a'].push_back(i);
	}
	int ans = 0;
	int jump = 0;
	vi juti;
    if(S[N-1] >= S[0])for(int i=S[0];i<=S[N-1];++i){
		if(pos[i-'a'].empty()) continue;
		juti.insert(juti.end(), pos[i-'a'].begin(), pos[i-'a'].end());
		jump += pos[i-'a'].size();
	}else for(int i=S[0];i>=S[N-1];--i){
		if(pos[i-'a'].empty()) continue;
		juti.insert(juti.end(), pos[i-'a'].begin(), pos[i-'a'].end());
		jump += pos[i-'a'].size();
	}
	printf("%d %d\n", abs(S[0]-S[N-1]), jump);
	for(int i : juti) printf("%d ", i+1);
	printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase; scanf("%d", &nofkase);
	while(nofkase--){
        scanf("%s", S);
		proc();
	}

    return 0;
}


