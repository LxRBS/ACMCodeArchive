/**
 * 有一个长度为N的排列，从中删除一个数，再将剩余的N-1个数给出。
 * 这样的信息给出N次。
 * 恢复这个排列。
 * 最开始不确定是否每个数恰好删除一次，后来发现确实是的
 * 无论所给信息是否有重复，都可以使用拓扑排序来做。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

namespace IO{

char *__abc147, *__xyz258, __ma369[1000000];
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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}

using vi = vector<int>;
using vvi = vector<vi>;
using llt = long long;
using vll = vector<llt>;
using vvll = vector<vll>;
using v3ll = vector<vvll>;
using si = set<int>;

using namespace IO;

int N;
vector<vector<int>> A;

int proc(){
    vector<set<int>> g(N+1, set<int>());
    vi deg(N + 1, 0);
    for(const auto & vec : A){
        for(int i=1;i<N-1;++i){
            auto p = g[vec[i-1]].insert(vec[i]);
            if(p.second) ++deg[vec[i]];
        }
    }   
    
    vector<int> d; d.reserve(N);
    for(int i=1;i<=N;++i)if(0==deg[i]){d.emplace_back(i);break;}
    int k = 0;
    while(k < N){
        auto h = d[k++];
        for(auto v : g[h]){
            if(0 == --deg[v]){
                d.emplace_back(v);
            }
        }
    }

    for(int i=0;i<N;++i)printf("%d%c", d[i], (i==N-1?'\n':' '));
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // int nofkase; cin >> nofkase;
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        A.assign(N, vector<int>(N - 1, 0));
        for(auto & vec : A)for(auto & i : vec) i = getInt();
        proc();          
    }
    return 0;
}