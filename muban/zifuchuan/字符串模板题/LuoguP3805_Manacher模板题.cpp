#include <bits/stdc++.h>
using namespace std;


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


namespace zifuchuan{


template<typename IT = const char *>
struct Manacher{

using vi = vector<int>;
using pii = pair<int, int>;

/// 从begin开始，一共n个
Manacher(IT begin, int n){
    tmp.reserve(n + n + 3);
    tmp.emplace_back(-2);
    tmp.emplace_back(-1);

	auto it = begin;
    for(int i=0;i<n;++i){
        assert(*it >= 0);
        tmp.emplace_back(*it++);
        tmp.emplace_back(-1);
    }
    tmp.emplace_back(-3);
    assert(tmp.size() == n + n + 3);

    r.assign(tmp.size(), 0);
    r[0] = r[1] = 1;

    int x = 1, total = r.size(), k;
    while(x < total){
        for(k=1;k<r[x];++k){
            if(k + r[x - k] == r[x]) break;
            r[x + k] = min(r[x - k], r[x] - k);
        }

        /// 半径至少是1或者r[x - k]
        r[x + k] = k == r[x] ? 1 : r[x - k];
        if((x += k) >= total - 1) break;
        while(tmp[x + r[x]] == tmp[x - r[x]]) ++r[x];
    }

    auto & ret = result.first;
    auto & start = result.second;
    for(int t,i=0;i<total;++i){
        t = r[i] - 1;
        if(ret < t) start = (i - (ret = t)) >> 1;
    }

    return;
}

const pii & get() const {return result;}

private:
vi tmp; // 临时数组
vi r; // 回文半径数组
pii result; // <最长回文长度, 第一个开始的地方>, 从0开始编号

};


}


#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 1.E7 + 10;
#endif


char S[SIZE];
vector<int> A;
int N;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);
    scanf("%s", S);
	zifuchuan::Manacher<> m(S, N=strlen(S));
	auto p = m.get();
	cout << p.first << endl;
    return 0;
}