/**
    ����չ��ģ����
    СN������ƽ�����Ӷ�
    ��N��Ҫ��NlogN���Ӷ�
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long llt;

llt const MOD = 998244353LL;
int const SIZE = 1000100;

//�׳�����
llt Fac[SIZE] = {1,1};
void initFac(int n){
    for(int i=2;i<=n;++i)Fac[i] = Fac[i-1]*i%MOD;
}

//����չ��,n�Ƚϴ�,a[1:n]��������,c�����䵱��״����
//��Ҫ��������׳�����
llt Cantor(llt const a[],int n,int c[]){
    fill(c,c+n+1,0);
    llt ans = 1;
    for(int i=1;i<=n;++i){
        //��ai�����ѳ��ֵ����ж��ٱ���С��
        int r = 0;
        for(int j=a[i];j;j-=(j&-j))r+=c[j];
        //�ۼӴ�
        ans += (a[i]-r-1) * Fac[n-i] % MOD;
        //��ai������״����
        for(int j=a[i];j<=n;j+=(j&-j))c[j]+=1;
    }
    return ans % MOD;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

llt A[SIZE];
int C[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    initFac(n);
    for(int i=1;i<=n;++i)A[i]=getUnsigned();
    printf("%lld\n",Cantor(A,n,C));
    return 0;
}
