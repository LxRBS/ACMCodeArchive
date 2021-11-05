/**
 * 在[L, R]范围内找一对数(a, b)使得a%b最大。
 * a%b最大显然是b-1，此时a最小是b+b-1。
 * 因此取R为a，然后根据L确定b即可
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

int f(int s, int e){
    int a = (e+1) >> 1;
    int b = a + a - 1;
    if(a<s){
        a = s;
        b = e;
    } 
    return b % a;
}
int main(){
    // freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        int s = getUnsigned();
        int e = getUnsigned();
        printf("%d\n", f(s, e));
    }
    
    return 0;
}