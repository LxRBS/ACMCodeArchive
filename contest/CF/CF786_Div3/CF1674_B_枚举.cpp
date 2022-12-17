/**
 * 长度为2的字符串，ab作为第一个，以此类推，zy作为最后一个
 * 给定s，问序号。事先把所有字符串全枚举出来记住即可。
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
int const SIZE = 13;
#else
int const SIZE = 1e5+5;
#endif
 
using llt = long long;
using Real = long double;
 
Real const EPS = 1E-12;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}

int N;
int M[256][256] = {0};
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int k = 0;
    for(int i='a';i<='z';++i)for(int j='a';j<='z';++j){
		if(i == j) continue;
		M[i][j] = ++k;
	}
    int nofkase; cin>>nofkase;
    while(nofkase--){
        string s; cin>>s;
		cout<<M[s[0]][s[1]]<<endl;
    }
    return 0;
}