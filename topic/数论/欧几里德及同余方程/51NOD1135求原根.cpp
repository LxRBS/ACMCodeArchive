#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

typedef long long int llt;

//����ɸ��
int const SIZE = sqrt(1E9) + 2;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

//�����ӷֽ⣬n�Ǵ��ֽ����,p���������ӣ�cnt�ǲ�ͬ�����ӵ�����
void primeFactor(int n,int p[],int&cnt){
    cnt = 0;
    for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
        if ( 0 == n % P[i] ){
            p[cnt++] = P[i];
            while( 0 == n % P[i] ) n /= P[i];
        }
    }
    if ( n != 1 ) p[cnt++] = n;
}

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

//��prime����Сԭ����prime������,p��������prime-1��������
llt minPrimitiveRoot(llt prime,int p[]){
    //�ֽ�������
    llt n = prime - 1;
    int cnt;
    primeFactor(n,p,cnt);
    for(llt g=2;g<prime;++g){
        bool flag = true;
        for(int i=0;i<cnt;++i){
            if ( 1 == powerMod(g,n/p[i],prime) ){
                flag = false;
                break;
            }
        }
        if (flag) return g;
    }
}

int A[SIZE];
int main(){
    sieve();
    llt prime;
    scanf("%lld",&prime);
    printf("%lld\n",minPrimitiveRoot(prime,A));
    return 0;
}
