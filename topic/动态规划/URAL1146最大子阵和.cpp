#include <cstdio>
#include <algorithm>
#include <numeric>
using namespace std;

typedef int value_t;

//a is source array indexed from 0, n is the length;
//d is auxiliary arrays
value_t maxSubSum(value_t const a[],int n,value_t d[]){
    value_t ret = a[0];
    d[0] = a[0];
    for(int i=1;i<n;++i){
        if ( d[i-1] < 0 ) d[i] = a[i];
        else d[i] = d[i-1] + a[i];
        if ( ret < d[i] ) ret = d[i];
    }

    return ret;
}

int const SIZE = 105;
value_t const NINF = -20000000;
value_t maxSubSum(value_t const a[][SIZE],int rows,int cols,value_t b[],value_t d[]){
    value_t ret = NINF;
    for(int c1=0;c1<cols;++c1)for(int c2=c1+1;c2<=cols;++c2){
        for(int r=0;r<rows;++r) b[r] = accumulate(a[r]+c1,a[r]+c2,0);
        value_t t = maxSubSum(b,rows,d);
        if ( ret < t ) ret = t;
    }
    return ret;
}

int A[SIZE][SIZE];
int B[SIZE],D[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)for(int j=0;j<n;++j)scanf("%d",A[i]+j);

    printf("%d\n",maxSubSum(A,n,n,B,D));
    return 0;
}

