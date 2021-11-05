/*
    ����n�����ж�����(a,b)����
    lcm(a,b)=n

    ����������������
    n = PI(pi^ki)

    ��ÿһ��������pi��
    a��b����pi�Ĳ�ͬ���һ����2ki+1��
    ��Ϊa����b֮�б�����һ������pi^ki
    Ȼ����һ������pi��ָ������ȡ��0~ki

    ���ȥһ����
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

//����ɸ��
int const SIZE = 1E7+5;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[665000];//1E7���ڵ�����Ϊ664000+
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

typedef long long llt;

int main(){
    //freopen("1.txt","r",stdin);
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        llt n;
        scanf("%lld",&n);

        llt ans = 1LL;
        for(int i=0;(llt)P[i]*(llt)P[i]<=n&&i<PCnt;++i){
            if ( 0 == n % P[i] ){
                int k = 0;
                while( 0 == n % P[i] ) n /= P[i], ++k;
                ans *= 2 * k + 1;
            }
        }
        if ( n != 1 ) ans *= 3;
        printf("Case %d: %lld\n",kase,(ans+1)>>1);
    }
    return 0;
}