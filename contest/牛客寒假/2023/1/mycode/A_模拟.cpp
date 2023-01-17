/**
 * 给定10个点球的得失情况，对应2个队，问第几轮可以确定胜负。
 * 循环5次，每次处理2个点球。对每个点球，记录其情况，然后看该队是否已经输了。
 * 已经输了的意思就是：该队剩下的球全进，也无法达到另一个球队的分数。
 */
#include <bits/stdc++.h>
using namespace std;
 
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 5500;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using prr = pair<Real, Real>;

Real const EPS = 1E-9;
inline int sgn(Real x) {return x>=EPS?1:(x<=-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);}

string S;
bool judge(int ap, int bp, int aleft, int bleft){
    if(ap + aleft < bp) return true;
    if(bp + bleft < ap) return true;
    return false;
}

int proc(){
    int a = 0, b = 0;
    int k = 1;
    for(int i=0;i<10;i+=2){
        if('1' == S[i]){
            ++a;
        }
        if(judge(a, b, 5 - k, 5 - k + 1)){
            return i + 1;
        }
        if('1' == S[i+1]){
            ++b;            
        }
        if(judge(a, b, 5-k, 5-k)){
            return i + 2;
        }
        ++k;
    }
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> S;
        printf("%d\n", proc());
    }

    return 0;
}


