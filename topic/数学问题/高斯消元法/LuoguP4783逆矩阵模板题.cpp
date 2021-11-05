/**
    矩阵求逆，模板题
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

llt const MOD = 1000000007;
int const SIZE = 410;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
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

//求矩阵a的逆，答案放在b中，输入要保证b为单位阵
//0 indexed, 执行完毕后，a变为单位阵
//返回0表示无逆矩阵，返回1表示成功
int inv(llt a[][SIZE],int n,llt b[][SIZE]){
    for(int row=0;row<n;++row){
        //整型不需要找列主元，只需找非零元即可
        int maxr = row;
        while(maxr<n&&0==a[maxr][row]) ++maxr;
        //无解
        if(n==maxr) return 0;
        //交换
        if(row!=maxr){
            for(int j=row;j<n;++j){
                swap(a[row][j],a[maxr][j]);
                swap(b[row][j],b[maxr][j]);
            }
        }
        //求逆元
        llt tmp = inv(a[row][row],MOD);
        //更新当前行
        for(int j=0;j<n;++j){
            a[row][j] = a[row][j]*tmp%MOD;
            b[row][j] = b[row][j]*tmp%MOD;
        }
        //更新其余行
        for(int i=0;i<n;++i)if(i!=row){
            llt tt = MOD - a[i][row];
            for(int j=0;j<n;++j){
                a[i][j] = ( a[i][j] + tt*a[row][j]%MOD ) % MOD;
                b[i][j] = ( b[i][j] + tt*b[row][j]%MOD ) % MOD;
            }
        }
    }
}

llt A[SIZE][SIZE],B[SIZE][SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j)A[i][j]=getInt();
        B[i][i] = 1;
    }
    int ret = inv(A,n,B);
    if(!ret){
        printf("No Solution\n");
        return 0;
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j)printf("%lld ",B[i][j]);
        printf("\n");
    }
    return 0;
}
