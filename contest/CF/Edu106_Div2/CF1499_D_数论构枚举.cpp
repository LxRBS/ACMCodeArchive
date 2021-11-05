/**
    给定c、d、x，求有多少对正整数(a, b)满足
    clcm(a,b) - dgcd(a,b) = x
    令gcd(a,b) = g, 则 a = ug, b = vg
    所以有 uv = (x/g + d) / c，且uv互质
    对x的每一个因子，计算出uv的值，并求出有多少对不同的uv
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

typedef long long int llt;
llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

int const SIZE = 20000010;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
int FCnt[SIZE];//不同的质因子的个数
void sieve(){
    for(llt i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i, FCnt[i] = 1;

        for(llt j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ){ 
                FCnt[i*P[j]] = FCnt[i];
                break;
            }else{
                FCnt[i*P[j]] = FCnt[i] + 1;
            }
        }
    }
}

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

inline llt f(llt c,llt d,llt x){
    llt g = gcd(c, gcd(d, x));
    c /= g, d /= g, x /= g;

    llt ans = 0;
    /// 对x的每一个因子
    for(llt uv,i=1;i*i<=x;++i){
        if(x%i) continue;

        if(0==(x/i+d)%c){
            uv = (x/i+d)/c;
            ans += (1LL<<FCnt[uv]);
        }        

        if(i*i==x||(i+d)%c) continue;

        uv = (i+d)/c;
        ans += (1LL<<FCnt[uv]);        
    }
    return ans;
}

int main(){
    // freopen("1.txt","r",stdin);
    // freopen("2.txt","w",stdout);
	sieve();
    // for(int i=12;i<=20;++i)cout<<FCnt[i]<<" ";
    //*
    int nofkase = getULL();
	while(nofkase--){
		llt c = getULL();
		llt d = getULL();
		llt x = getULL();
		printf("%lld\n",f(c,d,x));
	}//*/
    return 0;
}
