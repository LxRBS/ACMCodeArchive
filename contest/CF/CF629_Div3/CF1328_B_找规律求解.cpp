/**
 * 给定n，字符串由n-2个a和2个b构成
 * 要求输出第k小的这样的字符串
 * 观察规律即可
 * aa
 * aba  aab  三位的有2个
 * abba abab aabb 四位的有3个
 * abbba ... aabbb 这里有4个
 * ...
*/
#include <bits/stdc++.h>
using namespace std;
int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef long long int llt;
long long int f(llt k){//返回b的数量
    double x = (sqrt(1.0+8.0*k)-1.0)*0.5 + 1E-4;
    long long int m = (long long int)x;
    if(m*m-m>=k+k) return m-2;
    if(m*m+m>=k+k) return m-1;
    return m;
}
char A[1000010];
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();
        llt k = getUnsigned();
        //m是b前面a的数量
        llt m = f(k);
        //cout<<m<<endl;
        //首先输出前面的a
        int idx=0;
        for(int i=0,t=n-m-2;i<t;++i)A[idx++]='a';
        A[idx++]='b';
        for(llt i=0,t=(m+2)*(m+1)/2-k;i<t;++i)A[idx++]='a';
        A[idx++]='b';
        for(llt i=0,t=m+k-(m+2)*(m+1)/2;i<t;++i)A[idx++]='a';
        A[idx++]='\0';
        printf("%s\n",A);
    }
    return 0;
}
