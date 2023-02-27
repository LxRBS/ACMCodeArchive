/**
 * 给定一个字符串，问最少删除多少个字母，可以使其变为 [NEUQ]* 的格式
 * 直接贪心删除即可。最后需要一个小小的后处理。
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
using llt = long long; 
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif


using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N;
string S;
vi A;

int proc(){
	A.reserve(N);
	int ans = 0;
	int flag = 0;
	for(int i=0;i<N;++i){
		char ch = S[i];
        switch(flag){
			case 0:{
				if(ch != 'N') ++ans;
				else {flag = 1;A.push_back(i);}
			}break;
			case 1:{
				if(ch != 'E') ++ans;
				else {flag = 2;A.push_back(i);}
			}break;
			case 2:{
				if(ch != 'U') ++ans;
				else {flag = 3;A.push_back(i);}
			}break;
			case 3:{
				if(ch != 'Q') ++ans;
				else {flag = 0;A.push_back(i);}
			}break;
			default: assert(0);
		}   
	}

	return ans + A.size() % 4;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    cin >> N >> S;
	cout << proc() << endl;
    return 0; 
}