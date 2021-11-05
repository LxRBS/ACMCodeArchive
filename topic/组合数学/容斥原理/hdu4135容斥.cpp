//�ݳ�ԭ�������⣬0ms��248k��933B 
#include <iostream>
typedef long long llt;

llt Prm[1001] = {0LL};
int Pcnt = 0;

//��1��a���ж��ٸ���n���ʵ���
llt fun(llt a,llt n){
    llt ans = 0;

    //һ����Pcnt��������
    for(llt i=1;i<(1LL<<Pcnt);++i){
        int flag = 0;
        llt tmp = 1;
        for(int j=0;j<Pcnt;++j){
            if ( (i>>j) & 1 ){
                ++flag;
                tmp *= Prm[j];
            }
        }

        if ( flag & 1 ) ans += a / tmp;
        else            ans -= a / tmp;
    }
    //ans��[1,a]����n�����ʵĸ���
    return a - ans;
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);

    for(int kase=1;kase<=nofkase;++kase){
        llt a,b,n;
        scanf("%I64d%I64d%I64d",&a,&b,&n);

        Pcnt = 0;

        for(llt i=2;i*i<=n;++i){
            if ( n % i ) continue;

            Prm[Pcnt++] = i;
            n /= i;
            while( n % i == 0 ) n /= i;

            if ( 1 == n ) break;
        }

        if ( n != 1 ) Prm[Pcnt++] = n;

        printf("Case #%d: %I64d\n",kase,fun(b,n)-fun(a-1,n));
    }

    return 0;
}
