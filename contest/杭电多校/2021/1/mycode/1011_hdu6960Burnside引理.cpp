/**
 * N������Ⱦ3����ɫ����ɫ������k��������ɫ�ķ������Ƕ��٣�������ת�����ԡ�
 * �����Ƶ�Ⱦɫ����������Burnside����
 * ans = SIGMA{e(g)}/|G|
 * ����|G|��ʾ�û�Ⱥ�������û���������e(g)��ʾ��ÿһ��������û�g�Ĳ���Ԫ������
 * ������һ����N����ת��������תr��ʾ��תr����û�������Ҫ������תr����µĲ��������ж��١�
 * �����׵�֪��תr�����һ�����Ϊgcd(N, r)�Σ���ÿ��ѭ���ڵĳ���ΪN/gcd(N, r)
 * ʵ���Ͼ���˵ѭ���ڳ��ȱ���ΪN�����ӣ���ĳ��ѭ���ڳ���ΪL��
 * ֻ��Ҫ����L��Ⱦɫ�����������ɣ����е�N/L��Ƭ�ξ��մ�Ⱦɫ�����ܹ���һ������Ԫ
 * �����Ŀ��Ϊ��ɫ������k����������ɫ������ΪL��Ⱦɫ��������
 * �ٽ���Ŀϸ��Ϊ��ɫ����Ϊi��������ɫ����ΪL��Ⱦɫ��������
 * ע�⵽������ɫ���൱���ǻ�������i���̱�Ȼ������L�ֳ�i�Σ�
 * Ȼ����i��ÿһ�ο��Ե���Ⱦɫ����ʵ����ÿһ��ֻ��2��Ⱦɫ��������Ϊʣ�µ�������ɫ��ȻҪ������ɫ
 * �ٿ���L���м�ѡi���ֳ�i�εķ�������һ�����������ʹ�ø��巨�����׵õ�
 * �����ѡͷ������C(L-i, i)�֣����ѡͷ����C(L-i-1, i-1)��
 * ע����ɫΪ0��ʱ��Ҫ���㡣
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 998244353LL;

inline void addAssMul(llt&a, llt b, llt c){a+=b*c;a%=MOD;}

int const SIZE = 1000001;//TODO
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Euler[SIZE] = {0,1};
void sieve(){
    llt tmp;
    for(llt i=2;i<SIZE;++i){
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

llt InvFac[SIZE] = {1LL, 1LL};
llt Fac[SIZE] = {1LL, 1LL};
llt Inv[SIZE] = {1LL, 1LL};
void initFac(){
    for(int i=2;i<SIZE;++i){
        Inv[i] = (MOD-MOD/i) * Inv[MOD%i] % MOD;
        Fac[i] = Fac[i-1] * i % MOD;
        InvFac[i] = InvFac[i-1] * Inv[i] % MOD;
    }
}

/// �������
llt C(int n, int m){
    return Fac[n] * InvFac[m] % MOD * InvFac[n-m] % MOD;
}

llt powerMod(llt a, llt n){
    llt ans = 1LL;
    while(n){
        if(n&1) ans = ans * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ans;
}

llt f(llt n, llt L, llt k){
    llt ans = L&1 ? 0 : 2; // ��ɫΪ0�ķ�����
    for(llt i=1;i<=k;++i){ // ��ɫΪi�ķ�����
        ans += powerMod(2, i) * (C(L-i, i) + C(L-i-1, i-1)) % MOD;
    }
    return ans % MOD;
}

llt proc(llt n, llt k){
    llt i=1, ans = 0LL;
    for(;i*i<n;++i){ // ѭ���ڳ���Ϊi�Լ�n/i�ķ�����
        if(n%i) continue;
        addAssMul(ans, f(n, i, min(k*i/n, i/2)), Euler[n/i]);
        addAssMul(ans, f(n, n/i, min(k/i, n/i/2)), Euler[i]);
    }
    if(i*i==n){
        addAssMul(ans, f(n, i, min(k/i, i/2)), Euler[i]);
    }
    return ans * Inv[n] % MOD;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    initFac();
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        int n, k;
        scanf("%d%d", &n, &k);
        printf("%lld\n", proc(n, k));
    }
    return 0;
}