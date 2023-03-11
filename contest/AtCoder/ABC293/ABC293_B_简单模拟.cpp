/// 按题目的描述操作一遍即可
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
int const SIZE = 66;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;

int N;
vi A, Flag;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    A.assign((N = getInt()) + 1, 0);
	for(int i=1;i<=N;++i) A[i] = getInt();

    Flag.assign(N + 1, 0);
	vi ans; ans.reserve(N);
	for(int i=1;i<=N;++i){  
        if(0 == Flag[i]){
			Flag[A[i]] = 1;
		} 
	}
	for(int i=1;i<=N;++i)if(0 == Flag[i])ans.push_back(i);
	printf("%d\n", (int)ans.size());
	for(int i : ans)printf("%d ", i);printf("\n");
    return 0; 
}


