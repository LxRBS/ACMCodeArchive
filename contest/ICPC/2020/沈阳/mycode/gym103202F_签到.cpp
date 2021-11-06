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

int N, A[1000100],B[1000100];

int f(int pos){
    int t = pos;
    for(int i=pos;i<=N;++i){
        t = max(t, (int)(lower_bound(B+1,B+N+1,A[i])-B));
        if(t==i){
            return i + 1;
        }
    }
    return N+1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    N = getUnsigned();
    for(int i=1;i<=N;++i)A[i]=B[i]=getUnsigned();
    sort(B+1,B+N+1);
    int ans = 0, cur = 1;
    while(1){
        cur = f(cur);
        ++ans;
        if(cur>N) break;
    }
    cout<<ans<<endl;
    return 0;
}
