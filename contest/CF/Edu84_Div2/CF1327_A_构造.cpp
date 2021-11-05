/**
  给定n和k，问n能否表示为k个不同奇数之和
  前k个奇数之和是k^2，如果n比这个小显然否
  然后看k^2和n的奇偶性即可。
  如果奇偶性相同，则1+n-K^2显然也是一个奇数， 
  用它替换1，再加上除1之外的前k个奇数，即可。
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

bool f(int n,int k){
    llt t = (llt)k*(llt)k;
    if ( t > n ) return false;
    return !(( n - t ) & 1);
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n,k;
        scanf("%d%d",&n,&k);
        printf(f(n,k)?"YES\n":"NO\n");
    }
    return 0;
}
