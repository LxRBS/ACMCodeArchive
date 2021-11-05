/**
   ����n��д��һ�����ִ������統n=3ʱ���ô���
   000001002003...010011012...099100101102...998999
   �ʣ��ô�������k��������ͬ��Ƭ���ж��ٸ�������k��1ȡ��n��
   �ҹ��ɣ��ȴ�����ɴ𰸣��۲���ɡ�
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 998244353;

llt Power10[200100]={1};
llt NPower[200100];
llt A[200100];
llt Sum[200100];
int main(){
    llt n;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i){
        Power10[i] = 10 * Power10[i-1] % MOD;
        NPower[i] = ( NPower[i-1] * 10 % MOD + Power10[i] ) % MOD;
        A[i] = ( NPower[i] - NPower[i-1] - Sum[i-1] ) % MOD;
        if (A[i]<0) A[i] += MOD;
        Sum[i] = ( Sum[i-1] + A[i] ) % MOD;
    }
    printf("%lld",A[n]);
    for(int i=n-1;i;--i)printf(" %lld",A[i]);
    printf("\n");
    return 0;
}