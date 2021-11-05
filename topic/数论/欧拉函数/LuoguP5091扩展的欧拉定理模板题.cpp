/**
    扩展的欧拉定理模板题
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long llt;

//returns a^n%mod
llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}


int const SIZE = 35000;//TODO
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
llt Euler[SIZE] = {0,1};
void sieveEuler(int limit=SIZE){
    llt tmp;
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i, Euler[i] = i - 1;

		for(int j=0;j<PCnt&&(tmp=i*P[j])<SIZE;++j){
			isComp[tmp] = true;

			if ( 0 == i % P[j] ){
				Euler[tmp] = Euler[i] * P[j];
				break;
			}else{
				Euler[tmp] = Euler[i] * ( P[j] - 1 );
			}
		}
	}
}

//求n的欧拉函数即phi(n)
int phi(llt n,int limit=SIZE){
    if(n<SIZE) return Euler[n];
    //找到n的一个质因子
    for(int i=0;P[i]*P[i]<=n;++i){
        if(0==n%P[i]){
            if(n/P[i]%P[i]) return (P[i]-1)*phi(n/P[i]);
            return P[i]*phi(n/P[i]);
        }
    }
    //都不整除说明是一个大质数
    return n-1;
}

//扩展的欧拉定理，求a^n%p,其中a、p不互质，p未必是质数
//n是一个很大很大的数，用字符串表示
//a、p互质根据欧拉定理，a^phi(p)%p=1
//a、p不互质，当n大于等于phi(p)时，a^n = a^(n%phi(p)+phi(p)) (mod p)
//注意当n小于phi(p)时，不能用上述公式
llt exEuler(llt a,char const*n,llt p){
    //先求出p的欧拉函数
    llt fai = phi(p);
    //再求n对fai的模
    llt ret = 0;
    char const *pt = n;
    while(*pt&&ret<fai)ret = ret * 10 + (*pt++-'0');
    //小于fai，直接做快速幂取模
    if(!*pt) return powerMod(a,ret,p);
    //大于等于fai，使用扩展的欧拉公式
    ret %= fai;
    while(*pt)ret = (ret * 10 + (*pt++-'0'))%fai;
    ret += fai;
    return powerMod(a,ret,p);
}

char B[20000010];
int main(){
    //freopen("1.txt","r",stdin);
    sieveEuler();
    llt a,m;
    scanf("%lld%lld%s",&a,&m,B);
    printf("%lld\n",exEuler(a,B,m));
    return 0;
}
