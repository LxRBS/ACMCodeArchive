/// 很直白多重背包
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


namespace DS{

using T = int;

void beibao01(vector<T> & d, int maxv, int cost, T gains){
	for(int v=maxv;v>=cost;--v){
		d[v] = max(d[v], d[v - cost] + gains);
	}
}

void beibaoComplete(vector<T> & d, int maxv, int cost, T gains){
	for(int v=cost;v<=maxv;++v){
		d[v] = max(d[v], d[v - cost] + gains);
	}
}

void beibaoMulti(vector<T> & d, int maxv, int cost, T gains, int cnt){
	if(cost * cnt >= maxv){
		beibaoComplete(d, maxv, cost, gains);
		return;
	}

	for(int k=1;k<cnt;k<<=1){
		beibao01(d, maxv, k*cost, k*gains);
		cnt -= k;
	}

	if(cnt) beibao01(d, maxv, cnt * cost, cnt * gains);
	return;
}


}

using llt = long long;
using vll = vector<llt>;


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
    int n = getInt();
	int x = getInt();
	vector<int> a(n), b(n);
	for(int i=0;i<n;++i) a[i] = getInt(), b[i] = getInt();
	// vector<int> d(x + 1, -2000000000);
	vector<int> d(x + 1, 0); // 初始化为0或者-INF均可。只要后面用d[x] == x判断，以为此题代价和收益相同
	d[0] = 0;
	for(int i=0;i<n;++i){
		DS::beibaoMulti(d, x, a[i], a[i], b[i]);
	}
	cout << (d[x] == x ? "Yes" : "No") << endl; 
    return 0;
}