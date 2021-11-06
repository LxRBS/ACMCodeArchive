/**
    签到
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

int A[200010];
int main(){
    // freopen("1.txt","r",stdin);
    // freopen("2.txt","w",stdout);
    int n = getUnsigned();
    for(int i=0;i<n;++i)A[i]=getUnsigned();
	sort(A,A+n);
	double ans = 1.0,tmp;
	for(int i=0;i<n;++i){
		tmp=A[i]/(i+1.0);
		if(tmp>1){
			ans = -1;
			break;
		}else if(tmp < ans){
			ans = tmp;
		}		
	}
	printf("%.8f\n",ans);
    return 0;
}

