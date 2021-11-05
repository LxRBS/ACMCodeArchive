/**
    ����ʽ������ģ����
    ����A(x)����B(x)������
    B^2=A(mod x^n)
    �����Ѿ����H=A(mod x^(n/2))
    �� B-H=0(mod x^(n/2))��ƽ���ɵ�
    BB-2HB+HH=0(mod x^n)
    ע�⵽BB=A������B = ( A + HH ) / (2H)
    B = A/(2H) + H/2
*/

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
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

//����ʽ�˷�ans=a*b��naΪa����ߴΣ�nbΪb����ߴ�
//��ı�b�е����ݣ����a!=ans,��a���ֲ��䣬b��ans���ܴ�ͬһ������
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

llt const TWO_1 = inv(2,NTT_MOD);
llt TC[SIZE],TD[SIZE];

//��������ʽa�����俪��,nΪ��ǰ�ݹ�ʱ����ʽ�ĳ��ȣ�����ߴ�Ϊn-1
void sqrt(llt const a[],int n,llt ans[]){
    //a0��֤��1
    if(1==n){ans[0]=1;return;}

    sqrt(a,(n+1)>>1,ans);//�ݹ�
    //��ans���棬TC����ʱ����
    inv(ans,n,TC);

    //����˻�TC*a��TD����ʱ����
    multi(a,n-1,TC,n-1,TD);
    //����(TB+ans)/2
    for(int i=0;i<n;++i)ans[i] = ( ans[i] + TD[i] ) % NTT_MOD * TWO_1 % NTT_MOD;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

llt A[SIZE],B[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    initOmega();
    int n = getUnsigned();
    for(int i=0;i<n;++i)A[i]=getUnsigned();
    sqrt(A,n,B);
    for(int i=0;i<n;++i)printf("%lld ",B[i]);
    printf("\n");
    return 0;
}
