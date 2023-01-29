/**
 * 长度为N的数组A，任意i、j，当Ai大于Aj时，可以令Ai+=1，Aj-=1
 * 问A1最大可能是多少
 * 贪心。可以发现A的原始顺序其实不重要，将A排序
 * 然后对后面的Ai，能操作的就操作。
 * O(NlogN)
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long; 
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;

vi A;
int N;

int proc(){
	sort(A.begin()+1, A.end());
	int & ans = A[0];
	for(auto it=++A.begin(),et=A.end();it!=et;++it){
		if(*it <= ans) continue;
		int tmp = *it - ans;
		ans += tmp / 2;
		if(tmp & 1) ++ans;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        A.assign(N=getInt(), 0);
		for(int & i : A) i = getInt();
		printf("%d\n", proc());        
	}
    return 0;
}


