/**
    2×N的格子，第一行前k1格是白的，第二行前k2格是白的，其余全黑
    现有w个白色和b个黑色多米诺，问能否盖住（只能盖同色格子）。
    直接算即可
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define hash_t unordered_map

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

char A[][24] = {"NO","YES"};
inline bool f(int n,int k1,int k2,int w,int b){
    int mmin = min(k1, k2);
	int mmax = max(k1, k2);
	int zb = n - mmax;
    
	w -= mmin;
	if(w<0) w = 0;
	b -= zb;
	if(b<0) b = 0;
	// cout<<"w:"<<w<<", b:"<<b<<endl;

    int t = (mmax - mmin)>>1;
	// cout<<"t="<<t<<endl;

	return t >= w && t >= b;
}
int main(){
    // freopen("1.txt","r",stdin);
    // freopen("2.txt","w",stdout);
    int nofkase = getUnsigned();
	while(nofkase--){
		int n = getUnsigned();
		int k1 = getUnsigned();
		int k2 = getUnsigned();
		int w = getUnsigned();
		int b = getUnsigned();	
		puts(A[f(n,k1,k2,w,b)?1:0]);
	}
    return 0;
}
