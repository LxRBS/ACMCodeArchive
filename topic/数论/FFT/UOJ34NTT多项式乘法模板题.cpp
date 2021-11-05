//�������۱任������ʽ�˷���ģ����
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long long llt;

int const SIZE_OF_OMEGA = 20;
int const SIZE = 1 << SIZE_OF_OMEGA;
llt const NTT_MOD = (479LL << 21) | 1LL;//������
llt const G = 3LL;   //��������ԭ��
llt  Omega[SIZE_OF_OMEGA];

//������ȡģ
llt powerMod(llt a, llt n){
    llt ans = 1LL;
    a %= NTT_MOD;
    while(n){
        if(n & 1LL) ans = ans * a % NTT_MOD;
        a = a * a % NTT_MOD;n >>= 1;
    }
    return ans;
}

void initOmega(){
    for(int i=0;i<SIZE_OF_OMEGA;++i){
        int t = 1 << i;
        Omega[i] = powerMod(G, (NTT_MOD - 1) / t);
    }
}

//�׵��㷨������ϵ��λ�ã�nΪ���鳤�ȣ���0��ʼ
void Rader(llt a[],int n){
    for(int i=1,j=n>>1,k;i<n-1;++i){
        if ( i < j ) swap(a[i],a[j]);
        k = n >> 1;
        while( j >= k ) j -= k, k >>= 1;
        if ( j < k ) j += k;
    }
}


//�������۱任��aΪ�������������nΪ���ȣ�������2����
void ntt(llt a[], int n, bool isInv=false){
    Rader(a,n);

    for(int h=2,id=1;h<=n;h<<=1,++id){
        for(int j = 0; j < n; j += h){
            llt u,v,w = 1LL;
            for(int k=j,tmp=j+(h>>1);k<tmp;++k){
                u = a[k] % NTT_MOD;
                v = w * a[k+(h>>1)] % NTT_MOD;
                a[k] = ( u + v ) % NTT_MOD;
                a[k+(h>>1)] = ( u - v + NTT_MOD) % NTT_MOD;
                w = w * Omega[id] % NTT_MOD;
            }
        }
    }
    if(isInv){
        for(int i=1,tmp=n>>1; i < tmp; ++i) swap(a[i], a[n-i]);
        llt invv = powerMod(n, NTT_MOD - 2LL);
        for(int i=0;i<n;++i) a[i] = a[i] * invv % NTT_MOD;
    }
}

//����ʽ�˷�ans=a*b��naΪa����ߴΣ�nbΪb����ߴ�
//��ı�a��b�е�����
void multi(llt a[],int na,llt b[],int nb,llt ans[]){
    ++na,++nb;
	int ff = 1;
	while( ff < na + nb ) ff <<= 1;

    ntt(a,ff);
	ntt(b,ff);

	for(int i=0;i<ff;++i) ans[i] = a[i] * b[i] % NTT_MOD;

	ntt(ans,ff,true);
}

llt X[SIZE],Y[SIZE];

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    initOmega();

	int n = getUnsigned();
	int m = getUnsigned();

	for(int i=0;i<=n;++i)X[i]=getUnsigned();
	for(int i=0;i<=m;++i)Y[i]=getUnsigned();

	multi(X,n,Y,m,X);

	n += m;
	printf("%lld",X[0]);
	for(int i=1;i<=n;++i){
        printf(" %lld",X[i]);
	}
    putchar('\n');
	return 0;
}
