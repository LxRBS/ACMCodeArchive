/**
 * 给定N和K，找到一个数x，满足：
 * 1 x大于等于N
 * 2 x中的不同数字的数量不超过K个
 * 考虑N的第i位:  ...ai....
 * 要得到一个新数比N大，只需ai+1即可，此时比i低的为全部可设为0
 * 但是有可能数字超过了K，则需要将低位全部设为已有数字的最小的那个，如果还不行，说明不是改这一位
 * 从低到高找到第一个能改动的位即可
 * 当K==1时，单独判一下。
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

typedef long long llt;
llt const INF = 1E17;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 13;
#endif

int N, K;
int A[SIZE], ACnt;
int Cnt[SIZE], Diff;
int Min[SIZE]; // Min[i] 表示第i位以上的最小值

inline int get(int const a[]){
	llt ans = 0;
	for(int i=ACnt-1;i>=0;--i)ans=ans*10LL+a[i];
	return ans;
}

inline bool isOK(int const a[]){
	int cnt[10] = {0}, c=0;
	for(int i=0;i<ACnt;++i){
		if(1 == ++cnt[a[i]] && ++c > K){
			return false;
		}
	}
	return true;
}

llt proc(int idx){
	int b[SIZE] = {0};
	copy(A, A+ACnt, b);
	
	int &cur = b[idx];
	while(1){
		if(++cur == 10) break;

		/// 要么全为0
        fill(b, b+idx, 0);
		if(isOK(b)) return get(b);

		/// 要么全为最小值
		fill(b, b+idx, min(cur, Min[idx+1]));
		if(isOK(b)) return get(b);
	}
	return INF;
}

llt proc1(){   
	int k = ACnt - 1;
	int m = A[k];
	while(k>=0 && m==A[k]) --k;
	if(k<0) return N;

	if(A[k]>m) ++m;
	llt ans = 0LL;
	for(int i=0;i<ACnt;++i)ans=ans*10LL+m;
	return ans;
}

llt proc(){
    memset(Cnt, 0, sizeof(Cnt));
	ACnt = 0;

    Diff = 0;
	for(int n=N;n;n/=10){
		if(1 == ++Cnt[A[ACnt++] = n%10]) ++Diff;
	}
 
    if(Diff <= K) return N;

	if(1 == K) return proc1();

    Min[ACnt-1] = A[ACnt-1];
	for(int i=ACnt-2;i>=0;--i){
        Min[i] = min(Min[i+1], A[i]);
	}

    llt ans = INF;
	for(int i=0;i<ACnt;++i){
        if((ans=proc(i)) != INF){
			return ans;
		}
	}
	throw runtime_error("XXXX");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		N = getInt(); K = getInt();
		printf("%lld\n", proc());
	}
    return 0;
}

