/**
  给定数组A，求满足Ai=Aj*Ak的(i,j,k)的数量
  取值在2E5，主循环用O(NlogN)的筛法，然后注意数值1对答案的影响
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
int const SIZE = 12;
#else
int const SIZE = 2E5+5;
#endif  

using llt = long long;

int N, A[SIZE];
llt proc(){
	llt ans = 0;	
	if(A[1]){
		ans += A[1];
		ans += 3LL * A[1] * (A[1]-1LL);
		if(A[1]>2)ans+=A[1]*(A[1]-1LL)*(A[1]-2LL);
		for(int i=2;i<SIZE;++i){
			if(0 == A[i]) continue;
			ans += 2LL * A[i] * A[1];
			ans += 2LL * A[1] * A[i]*(A[i]-1LL);
		}
	}
	for(llt i=2;i*i<SIZE;++i){
		if(0 == A[i]) continue;
		if(A[i*i]){
			ans += 1LL * A[i] * A[i*i];
			ans += A[i] * (A[i]-1LL) * A[i*i];
		} 
		
		for(llt j=i+1;j*i<SIZE;++j){
            if(0 == A[j] || 0 == A[i*j]) continue;
            ans += 2LL*A[i]*A[j]*A[i*j];
		}
	}
    // for(int i=1;i<=N;++i)for(int j=1;j<=N;++j)for(int k=1;k<=N;++k){
	// 	if(A[i] == A[j]*A[k]){printf("%d %d %d\n",A[i],A[j],A[k]);++ans;}
	// }
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    N = getInt();
	for(int i=1;i<=N;++i) ++A[getInt()];
	cout<<proc()<<endl;
    return 0;
}
