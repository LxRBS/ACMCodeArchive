#include <cstdio>
#include <cstring>
typedef long long int llt;
llt const MOD = 1000000007LL;

llt D[16][16][16][16][16][6];

//a:还剩下1个的颜色的种类的数量
//b:还剩下2个的颜色的种类的数量
//c:...d:...e:...
//last:上一次取出的颜色是属于1/2/3/4/5的哪一大类
llt dp(int a,int b,int c,int d,int e,int last){
    if ( -1 != D[a][b][c][d][e][last] ) return D[a][b][c][d][e][last];

    llt ret = 0LL;

    if ( a ) ret += (a - (2==last)) * dp(a-1,b,c,d,e,1), ret %= MOD;
    if ( b ) ret += (b - (3==last)) * dp(a+1,b-1,c,d,e,2), ret %= MOD;
    if ( c ) ret += (c - (4==last)) * dp(a,b+1,c-1,d,e,3), ret %= MOD;
    if ( d ) ret += (d - (5==last)) * dp(a,b,c+1,d-1,e,4), ret %= MOD;
    if ( e ) ret += e * dp(a,b,c,d+1,e-1,5), ret %= MOD;

    return D[a][b][c][d][e][last] = ret;
}

int main(){
    int k;
    scanf("%d",&k);
    int a[6] = {0};
    for(int i=0;i<k;++i){
        int x;
        scanf("%d",&x);
        ++a[x];
    }

    memset(D,-1,sizeof(D));
    D[0][0][0][0][0][0] = D[0][0][0][0][0][1] = D[0][0][0][0][0][2]
        = D[0][0][0][0][0][3] = D[0][0][0][0][0][4] = D[0][0][0][0][0][5] = 1;
    printf("%lld\n",dp(a[1],a[2],a[3],a[4],a[5],0));
    return 0;
}
