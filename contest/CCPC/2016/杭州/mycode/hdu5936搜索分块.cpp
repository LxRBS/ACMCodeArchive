/*
    令f(y,K)=SIGMA(y的每个数字的K次方)
    例如 f(233,2) = 2^2 + 3^2 + 3^2
    再令 x = f(y,K) - y
    给定x和K，问有多少个y满足条件
    考虑使用搜索，经过计算可知最多有10位数
    令A记录前5位数的f值，B记录后5位数的f值
    原题变为有多少个Ai和Bj满足Ai+Bj==x
    对A做一个排序，可以在10万log(10万)完成
*/
#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;
typedef long long int llt;

//A[i][j]表示j的i次方减去j
llt A[10][100000];
//B[i][j]表示j的i次方减去j*100000
llt B[10][100000];
//Pow[i][j]表示i的j次方
llt Pow[10][10];
//Flag[i]表示A、B的第i行是否计算过
bool Flag[10];

llt f(llt y,int k,llt t10){
    int yy = y;
    int a[10],t=0;
    while(y){
        a[t++] = y%10;
        y/=10;
    }
    int sum = 0;
    for(int i=0;i<t;++i){
        sum += Pow[a[i]][k];
    }
    if(yy==42949&&t10==100000){
        int xxxx=1324342;
    }
    return sum - yy*t10;
}

void init(int k){
    if(Flag[k]) return;

    Flag[k] = true;
    //计算A和B的第k行
    for(int n=1;n<100000;++n){
        A[k][n] = f(n,k,1);
        B[k][n] = f(n,k,100000);
    }
    sort(A[k],A[k]+100000);
}


int main(){
    //freopen("1.txt","r",stdin);
    //计算Pow
    for(int i=1;i<10;++i){
        Pow[i][0] = 1;
        for(int j=1;j<10;++j){
            Pow[i][j] = Pow[i][j-1] * i;
        }
    }

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int x,k;
        scanf("%d%d",&x,&k);

        init(k);

        //在A[k]和B[k]中搜索有多少A[k][i]+B[k][j]==x
        int ans = 0;
        for(int i=0;i<100000;++i){
            llt tmp = x - B[k][i];
            pair<llt*,llt*> pp = equal_range(A[k],A[k]+100000,tmp);
            int tt = pp.second - pp.first;
            if(tt>0){
                ans += tt;
                //如果过零的话需要减1
                if(*pp.first<=0&&(0<*pp.second||pp.second==A[k]+100000)){
                    --ans;
                }

            }
        }
        printf("Case #%d: %d\n",kase,ans);
    }
    return 0;
}
