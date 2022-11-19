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
int const SIZE = 2E5+13;
#endif

int gcd(int a, int b){
    while( b ){
        int r = b;
        b = a % b;
        a = r;
    }
    return a;    
}

int N;
int A[SIZE];
int Map[1010];

int proc(){
    int ans = -1;
    for(int i=1;i<=1000;++i){
        if(0 == Map[i]) continue;
        for(int j=1;j<=1000;++j){
            if(0 == Map[j]) continue;
            if(1 == gcd(i, j)){
                ans = max(Map[i] + Map[j], ans);
            }
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        memset(Map, 0, sizeof(Map));
        N = getInt();
        for(int i=1;i<=N;++i) Map[A[i] = getInt()] = i;
        printf("%d\n", proc()); 
    }   
    return 0;
}
