/**
 * 给定一个三角形，问能否用水平线或者竖直线将其切成两个三角形
 * 对三个顶点依次判断即可
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

inline int sgn(llt x){return x > 0 ? 1 : (x < 0 ? -1 : 0);}

llt X[3], Y[3];

bool isOK(int a, int b, int c){
	llt xb = sgn(X[b] - X[a]);
	llt xc = sgn(X[c] - X[a]);
	if(xb * xc < 0) return true;
	
	xb = sgn(Y[b] - Y[a]);
	xc = sgn(Y[c] - Y[a]);
	return xb * xc < 0;
}

bool proc(){
	for(int i=0;i<3;++i){
		if(isOK(i, (i+1)%3, (i+2)%3)){
			return true;
		}
	}
	return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        for(int i=0;i<3;++i) X[i] = getInt(), Y[i] = getInt();
		puts(proc()?"YES":"NO");
	}
    return 0;
}


