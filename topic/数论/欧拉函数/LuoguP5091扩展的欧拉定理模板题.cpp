/**
    ��չ��ŷ������ģ����
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

//��n��ŷ��������phi(n)
int phi(llt n,int limit=SIZE){
    if(n<SIZE) return Euler[n];
    //�ҵ�n��һ��������
    for(int i=0;P[i]*P[i]<=n;++i){
        if(0==n%P[i]){
            if(n/P[i]%P[i]) return (P[i]-1)*phi(n/P[i]);
            return P[i]*phi(n/P[i]);
        }
    }
    //��������˵����һ��������
    return n-1;
}

//��չ��ŷ��������a^n%p,����a��p�����ʣ�pδ��������
//n��һ���ܴ�ܴ���������ַ�����ʾ
//a��p���ʸ���ŷ������a^phi(p)%p=1
//a��p�����ʣ���n���ڵ���phi(p)ʱ��a^n = a^(n%phi(p)+phi(p)) (mod p)
//ע�⵱nС��phi(p)ʱ��������������ʽ
llt exEuler(llt a,char const*n,llt p){
    //�����p��ŷ������
    llt fai = phi(p);
    //����n��fai��ģ
    llt ret = 0;
    char const *pt = n;
    while(*pt&&ret<fai)ret = ret * 10 + (*pt++-'0');
    //С��fai��ֱ����������ȡģ
    if(!*pt) return powerMod(a,ret,p);
    //���ڵ���fai��ʹ����չ��ŷ����ʽ
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
