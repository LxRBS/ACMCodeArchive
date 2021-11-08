/**
 * 给n个数，从中挑出2个长度均为x的数组，满足
 * 第一个数组的数都不一样，第二个数组的数都一样
 * 要求x最大
 * 找出众数，然后进行判断即可
*/
#include <bits/stdc++.h>
using namespace std;
int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}
int A[210000];
int Cnt[210000];

int f(int n,int mmax,int cnt){
    int ans = n>>1;
    if(mmax<ans) ans = mmax;
    if(cnt>ans) return ans;
    if(cnt==ans){
        if(ans==mmax) return cnt-1;
        return ans;
    }
    if(cnt+1==ans) return cnt;
    return cnt;
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    while(nofkase--){
        int n = getInt();
        fill(Cnt,Cnt+n+1,0);
        int max_cnt = 0;
        int cntcnt = 0;
        for(int i=1;i<=n;++i){
            if(1==++Cnt[A[i]=getInt()])++cntcnt;
            max_cnt = max(max_cnt,Cnt[A[i]]);
        }
        int ans = f(n,max_cnt,cntcnt);
        printf("%d\n",ans);
    }
    return 0;
}

