/*
     给定n，
     求x使得x！末尾有n个零
*/
#include <stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long llt;

//求n！末尾0的数量
int f(int n){
    int ans = 0;
    while(n){
        ans += n / 5;
        n /= 5;
    }
    return ans;
}

llt proc(int n){
    llt left = 1, right = 1000000000LL, mid;
    int tmp;
    do{
        mid = ( left + right ) >> 1;
        if ( ( tmp = f(mid) ) < n ) left = mid + 1;
        else if ( tmp > n ) right = mid - 1;
        else return mid - mid%5;//刚好返回5的倍数
    }while(left<=right);
    return -1;
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);
        llt ans = proc(n);
        printf("Case %d: ",kase);
        if ( -1 != ans ) printf("%lld\n",ans);
        else puts("impossible");
    }
    return 0;
}