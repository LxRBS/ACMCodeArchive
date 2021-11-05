/*
    已知S=a*b，a<b
    已知a的最小可能的值
    问一共有多少组(a,b)满足ab=S

    求出S的总的约数的个数的一半，
    然后剔除比a小的约数即可
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

//线性筛法
int const SIZE = 1E6+10;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
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

    llt s,a;
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%lld%lld",&s,&a);

        if ( s / a < a ){
            printf("Case %d: 0\n",kase);
            continue;
        }

        //求出s的约数个数
        llt ans = 1, ss = s;
        for(int i=0;P[i]*P[i]<=ss&&i<PCnt;++i){
            if ( 0 == ss % P[i] ){
                int k = 0;
                while( 0 == ss % P[i] ) ss /= P[i], ++k;
                ans *= ( k + 1 );
            }
        }

        if ( ss != 1 ) ans <<= 1;
        ans >>= 1;//只取一半的数量

        //检查小于b的约数数量，这个暴力法太暴力
        for(int i=1;i<a;++i)if(0==s%i)--ans;

        printf("Case %d: %d\n",kase,ans);
    }
    return 0;
}
