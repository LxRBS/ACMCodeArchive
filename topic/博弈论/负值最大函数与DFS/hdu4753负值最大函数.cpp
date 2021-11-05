#include <cstdio>
#include <algorithm>
using namespace std;

int const B00 = 1;
int const B01 = B00 << 1;
int const B02 = B00 << 2;
int const B03 = B00 << 3;
int const B04 = B00 << 4;
int const B05 = B00 << 5;
int const B06 = B00 << 6;
int const B07 = B00 << 7;
int const B08 = B00 << 8;
int const B09 = B00 << 9;
int const B10 = B00 << 10;
int const B11 = B00 << 11;
int const B12 = B00 << 12;
int const B13 = B00 << 13;
int const B14 = B00 << 14;
int const B15 = B00 << 15;
int const B16 = B00 << 16;
int const B17 = B00 << 17;
int const B18 = B00 << 18;
int const B19 = B00 << 19;
int const B20 = B00 << 20;
int const B21 = B00 << 21;
int const B22 = B00 << 22;
int const B23 = B00 << 23;

int const Point2Edge[][17] = {
    // 0   1   2   3   4   5   6   7   8
/*0*/ {0},
/*1*/ {000,000,B00,000,000,B03},
/*2*/ {000,B00,000,B01,000,000,B04},
/*3*/ {000,000,B01,000,B02,000,000,B05},
/*4*/ {000,000,000,B02,000,000,000,000,B06},
    // 0   1   2   3   4   5   6   7   8   9   10  11  12
/*5*/ {000,B03,000,000,000,000,B07,000,000,B10},
/*6*/ {000,000,B04,000,000,B07,000,B08,000,000,B11},
/*7*/ {000,000,000,B05,000,000,B08,000,B09,000,000,B12},
/*8*/ {000,000,000,000,B06,000,000,B09,000,000,000,000,B13},
    // 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16
/*9*/ {000,000,000,000,000,B10,000,000,000,000,B14,000,000,B17},
/*10*/{000,000,000,000,000,000,B11,000,000,B14,000,B15,000,000,B18},
/*11*/{000,000,000,000,000,000,000,B12,000,000,B15,000,B16,000,000,B19},
/*12*/{000,000,000,000,000,000,000,000,B13,000,000,B16,000,000,000,000,B20},
    // 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16
/*13*/{000,000,000,000,000,000,000,000,000,B17,000,000,000,000,B21},
/*14*/{000,000,000,000,000,000,000,000,000,000,B18,000,000,B21,000,B22},
/*15*/{000,000,000,000,000,000,000,000,000,000,000,B19,000,000,B22,000,B23},
/*16*/{000,000,000,000,000,000,000,000,000,000,000,000,B20,000,000,B23}
};

void _test(){
    int ret = 0;
    for(int i=1;i<=16;++i)for(int j=1;j<=16;++j){
        if ( Point2Edge[i][j] != Point2Edge[j][i] )printf("%d %d\n",i,j);
        if ( Point2Edge[i][j] ) ++ret;
    }
    printf("Toatal: %d\n",ret);
}

int go1step(int state,int edgeBit){
    switch( edgeBit ){
    case B00:return ( state & B03 ) && ( state & B04 ) && ( state & B07 ) ? 1 : 0;
    case B01:return ( state & B04 ) && ( state & B05 ) && ( state & B08 ) ? 1 : 0;
    case B02:return ( state & B05 ) && ( state & B06 ) && ( state & B09 ) ? 1 : 0;
    case B03:return ( state & B00 ) && ( state & B04 ) && ( state & B07 ) ? 1 : 0;
    case B04:return ( ( state & B00 ) && ( state & B03 ) && ( state & B07 ) ? 1 : 0 ) +  ( ( state & B01 ) && ( state & B05 ) && ( state & B08 ) ? 1 : 0 );
    case B05:return ( ( state & B01 ) && ( state & B04 ) && ( state & B08 ) ? 1 : 0 ) +  ( ( state & B02 ) && ( state & B06 ) && ( state & B09 ) ? 1 : 0 );
    case B06:return ( ( state & B02 ) && ( state & B05 ) && ( state & B09 ) ? 1 : 0 );
    case B07:return ( ( state & B00 ) && ( state & B03 ) && ( state & B04 ) ? 1 : 0 ) +  ( ( state & B10 ) && ( state & B11 ) && ( state & B14 ) ? 1 : 0 );
    case B08:return ( ( state & B01 ) && ( state & B04 ) && ( state & B05 ) ? 1 : 0 ) +  ( ( state & B11 ) && ( state & B12 ) && ( state & B15 ) ? 1 : 0 );
    case B09:return ( ( state & B02 ) && ( state & B05 ) && ( state & B06 ) ? 1 : 0 ) +  ( ( state & B12 ) && ( state & B13 ) && ( state & B16 ) ? 1 : 0 );
    case B10:return ( state & B07 ) && ( state & B11 ) && ( state & B14 ) ? 1 : 0;
    case B11:return ( ( state & B07 ) && ( state & B10 ) && ( state & B14 ) ? 1 : 0 ) +  ( ( state & B08 ) && ( state & B12 ) && ( state & B15 ) ? 1 : 0 );
    case B12:return ( ( state & B08 ) && ( state & B11 ) && ( state & B15 ) ? 1 : 0 ) +  ( ( state & B09 ) && ( state & B13 ) && ( state & B16 ) ? 1 : 0 );
    case B13:return ( state & B09 ) && ( state & B12 ) && ( state & B16 ) ? 1 : 0;
    case B14:return ( ( state & B07 ) && ( state & B10 ) && ( state & B11 ) ? 1 : 0 ) +  ( ( state & B17 ) && ( state & B18 ) && ( state & B21 ) ? 1 : 0 );
    case B15:return ( ( state & B08 ) && ( state & B11 ) && ( state & B12 ) ? 1 : 0 ) +  ( ( state & B18 ) && ( state & B19 ) && ( state & B22 ) ? 1 : 0 );
    case B16:return ( ( state & B09 ) && ( state & B12 ) && ( state & B13 ) ? 1 : 0 ) +  ( ( state & B19 ) && ( state & B20 ) && ( state & B23 ) ? 1 : 0 );
    case B17:return ( ( state & B14 ) && ( state & B18 ) && ( state & B21 ) ? 1 : 0 );
    case B18:return ( ( state & B14 ) && ( state & B17 ) && ( state & B21 ) ? 1 : 0 ) +  ( ( state & B15 ) && ( state & B19 ) && ( state & B22 ) ? 1 : 0 );
    case B19:return ( ( state & B15 ) && ( state & B18 ) && ( state & B22 ) ? 1 : 0 ) +  ( ( state & B16 ) && ( state & B20 ) && ( state & B23 ) ? 1 : 0 );
    case B20:return ( ( state & B16 ) && ( state & B19 ) && ( state & B23 ) ? 1 : 0 );
    case B21:return ( ( state & B14 ) && ( state & B17 ) && ( state & B18 ) ? 1 : 0 );
    case B22:return ( ( state & B15 ) && ( state & B18 ) && ( state & B19 ) ? 1 : 0 );
    case B23:return ( ( state & B16 ) && ( state & B19 ) && ( state & B20 ) ? 1 : 0 );
    }
    return 0xCCCCCCCC;
}

typedef signed char _t;
_t Dp[(1<<24)];

int negMax(int state){
    if ( 15 != Dp[state] ) return Dp[state];

    int ret = -100000;
    int edgeBit;
    for(int i=0;i<24;++i){
        if ( state & (1<<i) ) continue;

        int t = go1step(state,edgeBit=1<<i);
        t -= negMax(state|edgeBit);

        if ( ret < t ) ret = t;
    }
    return Dp[state] = ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);

        int flag = 1;
        int ret = 0;
        int state = 0;
        int edgeBit;
        for(int i=0;i<n;++i){
            int a,b;
            scanf("%d%d",&a,&b);
            ret += flag * go1step(state,edgeBit=Point2Edge[a][b]);
            state |= edgeBit;
            flag *= -1;
        }

        fill(Dp,Dp+(1<<24),(_t)15);
        Dp[0xFFFFFF] = 0;
        ret += flag * negMax(state);

        printf("Case #%d: ",kase);
        if ( ret > 0 ) printf("Tom200\n");
        else printf("Jerry404\n");
    }
    return 0;
}
