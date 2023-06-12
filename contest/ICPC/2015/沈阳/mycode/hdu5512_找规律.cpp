/**
  1~N范围内，初始集合{a, b}，两个人轮流选数
  所选数必须是集合内两个数的和或者差，不能选者输
  假设选出的数是t且t=a-b
  接下来的数则是b-t...
  更相减损法，最后的差是gcd(a,b)
  因此能够选出的数的数量是N/gcd
*/

#include <stdio.h>
#include <string.h>
using namespace std;

int gcd(int a,int b){
    while( b ){
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}

char A[2][20] = {
    "Iaka","Yuwgna"
};

int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n,a,b;
        scanf("%d%d%d",&n,&a,&b);
        int g = gcd(a,b);
        n /= g;
        printf("Case #%d: %s\n",kase,A[n&1]);
    }
    return 0;
}