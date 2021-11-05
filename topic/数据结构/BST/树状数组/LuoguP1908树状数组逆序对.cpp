/*
     逆序对
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

int const SIZE = 1000100;
int A[SIZE],T[SIZE];
int C[SIZE];
int N;

inline int lowbit(int x){return x&-x;}

//查询[1,r]的区间和
int query(int r){
    int sum = 0;
    for(;r;r-=lowbit(r))sum += C[r];
    return sum;
}
//第r个位置加delta
void modify(int r,int delta){
    for(;r<=N;r+=lowbit(r))C[r] += delta;
}

int main(){
    //freopen("1.txt","r",stdin);
    int n = N = getInt();
    for(int i=0;i<n;++i) A[i] = T[i] = getInt();

    //离散化
    sort(T,T+n);
    N = unique(A,A+n) - A;

    long long int ans = 0;
    for(int a,i=n-1;i>=0;--i){
        a = lower_bound(T,T+N,A[i]) - T + 1;
        //查询比a小的数量
        ans += query(a-1);
        //将a的数量增加1
        modify(a,1);
    }
    printf("%lld\n",ans);
    return 0;
}
