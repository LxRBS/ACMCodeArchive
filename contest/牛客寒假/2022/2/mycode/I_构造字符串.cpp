/**
 * 给定两类字母，一类字母是自身与自身对称，另一类字母是两两对称
 * 现在给定N和M，要求使用M种不同的字母，构造一个长度为N的对称字符串。
 * 将N和M分奇偶讨论，一共4种情况。每种情况使用贪心构造。
 * 例如当N和M都是偶数时，优先使用第二类字母，直到用完M种，
 * 然后将剩下的位置填充最后两类字母即可
 * 第二类字母用完，接着使用第一类字母，直到达到M种，剩下填充最后一类字母即可
 * 否则就是无法填充，返回-1
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

llt const MOD = 1000000007LL;

int N, M;

string const T = "\"!\'*+-.08:=^_WTYUIOAHXVM|";
string const P = "<>\\/[]{}()";

using FunTy = function<string()>;

FunTy F[4] = {
/// N和M都是偶数
[]()->string{
	if(M > N) return "-1";

    string ans(N, ' ');    
    int k = 0, m = M; 
	for(int i=0;i<P.length();i+=2){
        ans[k] = P[i];
		ans[N-1-k] = P[i+1];
		m-=2, ++k;
		if(m == 0 || k == N / 2) break;
    }
	if(N / 2 == k) return 0 == m ? ans : "-1";
	if(0 == m){
		fill(ans.begin()+k, ans.begin()+N/2, ans[k-1]);
		fill(ans.begin()+N/2, ans.end()-k, ans[N-k]);
		return ans;
	}
	int t = 0;
	while(t < T.length()){
        ans[k] = ans[N-1-k] = T[t++];
		++k; --m;
        if(m == 0 || k == N / 2) break;
	}
	if(N / 2 == k) return 0 == m ? ans : "-1";
	if(0 == m){
		fill(ans.begin()+k, ans.begin()+N/2, ans[k-1]);
		fill(ans.begin()+N/2, ans.end()-k, ans[N-k]);
		return ans;		
	}
    return "-1";
},
/// N是偶数，M是奇数
[]()->string{
	if(M > N) return "-1";
	if(1 == M) return string(N, 'A');

	string ans(N, ' ');
	int k = 0, m = M;
	for(int i=0;i<P.length();i+=2){
        ans[k] = P[i];
		ans[N-1-k] = P[i+1];
		m -= 2, ++k;
		if(m == 1 || k == N / 2) break;
	}
	if(k == N / 2) return "-1";
	if(1 == m){
		fill(ans.begin()+k, ans.end()-k, 'A');
		return ans;
	}
	int t = 0;
	while(t < T.length()){
        ans[k] = ans[N-1-k] = T[t++];
		++k; --m;
        if(m == 0 || k == N / 2) break;		
	}
	if(N / 2 == k) return 0 == m ? ans : "-1";
	if(0 == m){
		fill(ans.begin()+k, ans.end()-k, ans[k-1]);
		return ans;
	}
	return "-1";
},
/// N是奇数，M是偶数
[]()->string{
	if(M > N) return "-1";

    string ans(N, ' ');    
    if(2 == M){
		ans[N/2] = 'A';
		fill(ans.begin(), ans.begin()+N/2, 'V');
		fill(ans.begin()+N/2+1, ans.end(), 'V');
		return ans;
	}
	
	int k = 0, m = M; 
	for(int i=0;i<P.length();i+=2){
        ans[k] = P[i];
		ans[N-1-k] = P[i+1];
		m -= 2, ++k;
		if(m == 2 || k == N / 2) break;
    }
	if(k == N / 2) return "-1";
	if(2 == m){
		ans[N/2] = 'A';
		fill(ans.begin()+k, ans.begin()+N/2, 'V');
		fill(ans.begin()+N/2+1, ans.end()-k, 'V');
		return ans;
	}
	int t = 0;
	while(t < T.length()){
		ans[k] = ans[N-1-k] = T[t++];
		--m; ++k;
		if(m == 0 || k == N / 2 + 1) break;
	}
    if(0 == m){
		if(k != N / 2 + 1) fill(ans.begin()+k, ans.end()-k, ans[k-1]);
		return ans;
	}
    return "-1";	
},
/// N是奇数，M是奇数
[]()->string{
	if(M > N) return "-1";
	if(1 == M) return string(N, 'A');

	string ans(N, ' ');
	int k = 0, m = M;
	for(int i=0;i<P.length();i+=2){
		ans[k] = P[i];
		ans[N-1-k] = P[i+1];
		m -= 2; ++k;
		if(1 == m || k == N / 2) break;
	}	

	if(N / 2 == k){
        if(m != 1) return "-1";
		ans[k] = 'A';
		return ans;
	}

	if(1 == m){
		fill(ans.begin()+k, ans.end()-k, 'A');
		return ans;
	}

	int t = 0;
	while(t < T.length()){
		ans[k] = ans[N-1-k] = T[t++];
		--m; ++k;
		if(0 == m || k == N / 2 + 1) break;
	}
	if(k == N / 2 + 1) return ans;
	if(0 == m){
		fill(ans.begin()+k, ans.end()-k, ans[k-1]);
	    return ans;
	}
	return "-1";
}


};

string proc1(){
    if(M > N) return "-1";
	if(1 == N) return "A";

	string ans(N, ' ');
	if(M & 1){
		int k = 0;
        for(int i=0;i<P.length();i+=2){
			ans[k] = P[i];
			ans[N-1-k] = P[i+1];
			if(++k == N/2) break;
			if((M -= 2) == 1) break;
		}
		int t = 0;
        while(1){
			if(k == N/2 || M == 1 || t == T.length()) break;
			ans[k] = ans[N-1-k] = T[t++];
			++k, --M;
		}
		if(k == N/2 && M > 1) return "-1";
		if(t == T.length()) return "-1";
		fill(ans.begin()+k, ans.end()-k, '|');
		return ans;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    while(cin >> N >> M){
		int st = ((N & 1) << 1) | (M & 1);
		cout << (F[st]()) << endl;		
	}

    return 0;
}


