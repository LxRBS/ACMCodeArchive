/**
 * 给N长度数组，问最少能够将该数组拆分成多少个数值连续的上升子序列
 * 将数组A按照数值排序，并且记录数量
 * 然后不停迭代即可。对每一个 (vi, ci)
 * 如果vi与v[i-1]是不连着的，就要增加ci个子序列
 * 如果ci比c[i-1]大，就要增加ci - c[i-1]个子序列
 * 否则就不用增加子序列
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
vi A;
map<int, int> Map;

int proc(){
    auto value = Map.begin()->first;
    auto cnt = Map.begin()->second;
    int ans = cnt;
    for(auto it=++Map.begin(),et=Map.end();it!=et;++it){
        if(it->first != value + 1){
            ans += cnt = it->second;
            value = it->first;
        }else if(cnt == it->second){
            ++value; 
        }else if(cnt < it->second){
            ++value;
            ans += it->second - cnt;
            cnt = it->second;
        }else{
            ++value;
            cnt = it->second;
        }
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // int nofkase; cin >> nofkase;
    int nofkase = getInt();
    while(nofkase--){
        Map.clear();
        A.assign(N=getInt(), 0);
        for(int & i : A) ++Map[i = getInt()];
        printf("%d\n", proc());          
    }
    return 0;
}