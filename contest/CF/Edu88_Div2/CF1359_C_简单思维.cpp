/**
 * 给定HCT，H表示高温水，C表示低温水，T表示目标温度
 * 现在一杯高温，一杯低温的交替混合，问最接近T，最少用几杯水
 * 由于必须以高温开头，所以偶数必然导致(H+C)/2
 * 只有奇数才需要额外处理，令n为奇数，则
 * ((n+1)H+(n-1)C)/(2n)
 * 是温度，再令该温度<=T，可以解出n
 * 可以直接确定答案
 * 想不清楚的话，直接搜索以下n左右的点即可
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

typedef long long llt;

llt H, C, T;

double f(llt n){
	return fabs(((double)(n+1)*H+(double)(n-1)*C)/(n+n)-T);
}

llt proc(){
	if(H == T) return 1;
	if(T+T <= H+C) return 2;    

	double a = (double)(H-C)/(double)(T+T-H-C);
	double b = (double)(H+H-T-T)/(double)(T+T-H-C);
    llt n = (llt)ceil(a);
	vector<llt> v;
	if(n&1){
		v.assign({n-4,n-2,n,n+2,n+4});
	}else{
		v.assign({n-5,n-3,n-1,n+1,n+3,n+5});
	}
	n = v.back();
	for(int i=v.size()-1;i>=0;--i){
		if(v[i]<1) break;
		if(f(v[i]) <= f(n)) n = v[i];
	}
    return n;
}

int main(){
#ifndef ONLINE_JUDGE	
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
		H = getUnsigned();
		C = getUnsigned();
		T = getUnsigned();
		printf("%lld\n", proc());
		// for(llt i=1;i<=33;i+=2){
		// 	printf("%.4f ", f(i));
		// }
		// printf("\n");
	}
    return 0;
}
