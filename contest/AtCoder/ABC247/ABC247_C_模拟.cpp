/*
  定义字符串:
  s1 = 1, sn = s[n-1], n, s[n-1]
  例如: s2 = 121, s3 = 1213121
  给定n，问sn是多少，n最多16
  直接操作即可
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000+1];
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
int const SIZE = 11;
#else
int const SIZE = 1e5+5;
#endif

using vs = vector<string>;
vs A[17];

string int2string(int n){
    stringstream ss;
    ss<<n;
    return ss.str();
}

void output(int pos){
    const vs & vec = A[pos];
    cout<<vec.front();
    for(int i=1,n=vec.size();i<n;++i){
        cout<<" "<<vec[i];
    }
    cout<<endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    A[1].assign(1, "1");
    for(int i=2;i<=16;++i){
        A[i].insert(A[i].end(), A[i-1].begin(), A[i-1].end());
        A[i].emplace_back(int2string(i));
        A[i].insert(A[i].end(), A[i-1].begin(), A[i-1].end());
    }
    int n; cin>>n;
    output(n);
    return 0;
}
