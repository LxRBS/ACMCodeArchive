/**
    ����ʽ����ģ���⣬����a��b����q��r������
    a=bq+r
    ��һ��ת�ò�������ϵ���Ի�
    �� qr = ar * br^(-1)
    �� r = a-bq
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
void disp(T const a[],int n){
    for(int i=0;i<n;++i)cout<<a[i]<<" ";
    cout<<endl;
}

typedef long long llt;

int const SIZE_OF_OMEGA = 20;
int const SIZE = 1 << SIZE_OF_OMEGA;
llt const NTT_MOD = 998244353LL;
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

llt TA[SIZE],TB[SIZE];//��ʱ����
//�����ʽa���棬nΪ����ʽ�ĳ��ȣ�n-1Ϊ����ʽ����ߴ���
void inv(llt const a[],int n,llt ans[]){
    if(1==n){
        ans[0] = inv(a[0],NTT_MOD);
        return;
    }

    inv(a,(n+1)>>1,ans);//�ݹ�

    //��NTT�ĺ��ʳ���
    int limit = 1, len = 0;
    while(limit<(n<<1)) limit<<=1,++len;

    fill(TA,TA+limit+1,0);
    fill(TB,TB+limit+1,0);

    copy(a,a+n,TA);
    copy(ans,ans+n,TB);

    ntt(TA,limit);
    ntt(TB,limit);

    //����B(2-AB)��NTT�任
    for(int i=0;i<limit;++i){
        TB[i]= TB[i] * ( (2-TA[i]*TB[i]%NTT_MOD+NTT_MOD)%NTT_MOD ) % NTT_MOD;
    }

    //�����������NTT��任
    ntt(TB,limit,true);

    //�������
    copy(TB,TB+n,ans);
    fill(ans+n,ans+limit+1,0);
}
llt X[SIZE],Y[SIZE];

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//����ʽ�˷�ans=a*b��naΪa����ߴΣ�nbΪb����ߴ�
//��ı�b�е����ݣ����a!=ans,��a���ֲ���
void multi(llt const a[],int na,llt b[],int nb,llt ans[]){
    if(a!=ans)copy(a,a+(++na),ans);//����a

    ++nb;
	int ff = 1;
	while( ff < na + nb ) ff <<= 1;

    ntt(ans,ff);
	ntt(b,ff);

	for(int i=0;i<ff;++i) ans[i] = ans[i] * b[i] % NTT_MOD;

	ntt(ans,ff,true);
}

//�����ʽq��r������a=bq+r,����naΪa����ߴΣ�nbΪb����ߴ�
//����ar��br�ֱ�Ϊa��b��reverse�������漴�����
//��ı�b������
void divide(llt const a[],llt ar[],int na,llt b[],llt br[],int nb,llt q[],llt r[]){
    //��br���棬ģx^(na-nb+1)
    inv(br,na-nb+1,r);
    //��ar*br^(-1)
    multi(ar,na,r,na-nb,q);
    //��q��reverse����
    reverse(q,q+na-nb+1);
    fill(q+na-nb+1,q+SIZE,0);
    //��q*b��ע����ߴ���
    multi(q,na+na,b,na+na,r);
    //��a-bq
    for(int i=0;i<nb;++i)r[i]=(a[i]-r[i]+NTT_MOD)%NTT_MOD;
}

llt A[SIZE],B[SIZE],Q[SIZE],R[SIZE],Ar[SIZE],Br[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    initOmega();
    int n = getUnsigned(), m = getUnsigned();
    for(int i=0;i<=n;++i) A[i] = Ar[n-i] = getUnsigned();
    for(int i=0;i<=m;++i) B[i] = Br[m-i] = getUnsigned();
    divide(A,Ar,n,B,Br,m,Q,R);
    for(int i=0;i<=n-m;++i)printf("%lld ",Q[i]);
    printf("\n");
    for(int i=0;i<m;++i)printf("%lld ",R[i]);
    printf("\n");
    return 0;
}
