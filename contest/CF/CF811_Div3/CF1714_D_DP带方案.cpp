/**
 * 给定一个字符串S，长度100，再给定10个小字符串Ti，长度10
 * 如果Ti是S的子串，则能用Ti将S的这一部分盖住，可以重复覆盖
 * 问最少要多少次可以将S全盖住，输出方案。不能则输出-1
 * 规模较小，用暴力的方法即可
 * 首先求出Ai，Ai包含以i位置结尾的可以匹配的T的所有编号
 * 令Di是盖到i的最小次数，D初始化为-1，D[0] = 0
 * 则 Di = min{1 + Dj, Dj!=-1, 且Dj在t的覆盖范围内，t是Ai中的字符串之一}
 * 计算的时候顺便记住方案
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

int N;
string S;
vector<string> T;

vvi A;
vi D;
vpii G;

void output(){
	vpii ans;
	int k = S.length();
	while(1){
        ans.emplace_back(k-T[G[k].first].length()+1, G[k].first);
		if(0 == (k = G[k].second)) break;
	}
	assert(ans.size() == D[S.length()]);
	printf("%d\n", (int)ans.size());
	for(auto it=ans.rbegin();it!=ans.rend();++it) printf("%d %d\n", it->second, it->first);
	return;
}

void proc(){
    N = S.length();
	A.assign(N+1, vi());
	for(int i=1,n=T.size();i<n;++i){
		const string & s = T[i];
		int k = 0;
		while(1){
			auto p = S.substr(k).find(s);
			if(p == string::npos) break;

			A[k+p+s.length()].push_back(i);
			if((k += p + 1) >= S.length()) break;
		}
	}

    G.assign(N+1, {-1, -1});
    D.assign(N+1, -1);
	D[0] = 0;
    
	for(int i=1;i<=N;++i){
		int & d = D[i];
		for(int j : A[i]){
			int t = T[j].length();
			for(int k=max(0, i-t);k<=i;++k){
                if(-1 == D[k]) continue;

                if(-1 == d || d > D[k] + 1){
					d = D[k] + 1;
					G[i] = {j, k};
				} 
			}
		}
	}
	if(-1 == D[N]) return (void)printf("-1\n");
	output();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
	while(nofkase--){
        int n; cin >> S >> n;
        T.assign(n+1, "");
		for(int i=1;i<=n;++i) cin >> T[i];
		proc();
	}
    return 0;
}


