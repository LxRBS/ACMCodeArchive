/**
    给定[L, R]，问其中的质数的数量有没有小于总数的三分之一
    LR在10亿以内
    区间越大，质数越稀疏
    太大的区间直接给结论，小区间暴力
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
int const SIZE = sqrt(1E9) + 2;//一般只筛到30000+即可
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

int f(int n){
    for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
        if(0==n%P[i]) return 0;
    }
    return 1;
}
int f(int a,int b){
    if(b-a>=150) return true;
    int cnt = 0;
    for(int i=a;i<=b;++i) cnt+=f(i);
    return cnt+cnt+cnt<b-a+1;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    int nofkase = getUnsigned();
    while(nofkase--){
        int a = getUnsigned();
        int b = getUnsigned();
        printf(f(a,b)?"Yes\n":"No\n");
    }
    return 0;
}

