/**
    nim游戏。每一次选一堆石子，假设其数量为N，
    则把其变为m堆p个，满足m*p==n，其m不是1。
    最后全1就不能动了，为输。
    打表sqrt(1E9)，找规律 
    sg(n)为n的质因子的数量，但是不计重复的2。
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

//线性筛法
int const SIZE = sqrt(1E9)+2;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

//求n的sg值，去掉重复的2，然后看一共有多少个质因子
int sg(int n){
    if(1==n) return 0;

    int ans = (n&1) ? 0 : 1;
    while(!(n&1)) n>>=1;

    for(int i=1;i<PCnt&&P[i]*P[i]<=n;++i){
        if(n%P[i]==0){
            while(n%P[i]==0) ++ans, n /= P[i];
        }
    }

    return n==1?ans:ans+1;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    char const s[2][10] = {"L", "W"};
    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();
        int ans = 0;
        while(n--){
            ans = ans ^ sg(getUnsigned());
        }
        puts(s[ans?1:0]);
    }
    return 0;
}

