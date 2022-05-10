/**
  给定N，问N以内满足条件数的数量，条件为：
  p*q^3，其中p、q均为质数且p<q
  N在1E18
  只需筛出1E6的质数即可，然后枚举q即可
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
 
using llt = long long;
using Real = long double;
using vi = vector<int>;
 
Real const EPS = 1E-12;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}

int const SIZE = 1E6+2;
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

llt N;

llt proc(){
	llt ans = 0;
    for(int i=1;i<PCnt;++i){
		llt q = P[i];
		llt u = q * q * q;
		if(N <= u) break;
		llt r = N / u;
		int t = lower_bound(P, P+PCnt, r) - P;
		if(P[t] == r) ++t;
		if(t > i) t = i;
		ans += t;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    sieve();
    cin>>N;
	cout<<proc()<<endl;
    return 0;
}
