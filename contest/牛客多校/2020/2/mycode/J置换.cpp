/**
    称123...n为起点S
    再给定一个排列称作Target——T
    再给定一个数K，
    求一个置换x，使得从S到T恰好经过了K次x变换
    令c为一个置换，从S到T，相当于求方程x^K=c的解
    令c可以分为m个轮换，每个轮换的长度为Li，
    根据数据范围Li与K必然互质，因为K是质数且K>Li
    所以可以求出qi满足qiK=rLi+1，也就是qi是K模Li的逆
    再令这个轮换中的x=c^qi即可。
    对每一个轮换求一次，即可求出x的所有内容
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//The extended Euclidean algorithm implemented by iteration
//returns gcd(a,b), and x, y are satisfied with ax + by = gcd
llt exEuclid(llt a,llt b,llt&x,llt&y){
    llt x0 = 1, y0 = 0;
    llt x1 = 0, y1 = 1;
    x = 0; y = 1;
    llt r = a % b;
    llt q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

//returns the inverse of a mod p satisfied with 1 == ax%p
//it will be success only when a and p are co-prime
inline llt inv(llt a,llt p){
    llt x,y;
    llt r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

llt A[100010];
bool Flag[100010];
llt Tmp[100010];
llt Tmp2[100010];
llt Result[100010];

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int n = getUnsigned();
    llt k = getUnsigned();
    for(int i=1;i<=n;++i)A[i]=getUnsigned();
    //求循环节
    for(int i=1;i<=n;++i){
        if(Flag[i]) continue;

        llt cnt = 0;
        int t = i;
        do{
            Flag[t] = true;
            Tmp[t] = A[t]; //置换:At变成t
            t = A[t];
            ++cnt;
        }while(!Flag[t]);
        //求出了一个轮换，且长度为cnt，求逆
        if(cnt==1) continue;
        llt qi = inv(k%cnt, cnt);
        //把变换写成连续的形式以方便循环移位
        t = i;
        for(int j=0;j<cnt;++j){
            Tmp2[j] = Tmp[t];
            t = A[t];
        }
        //Tmp中即置换ci，现在求ci^qi，也就是做一个循环移位
        if(--qi) rotate(Tmp2,Tmp2+qi,Tmp2+cnt);
        //保存结果
        t = i;
        for(int j=0;j<cnt;++j){
            Tmp[t] = Tmp2[j];
            t = A[t];
        }
    }
    //输出
    for(int i=1;i<=n;++i)printf("%lld ",Tmp[i]);
    printf("\n");
    return 0;
}
