/**
  问[1, n]与[1, m]中有多少个数对(a, b)
  满足a乘b是2016的倍数
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt Cnt = 0;

llt f(llt a, llt b){
    llt na = a / 2016;
    a %= 2016;
    llt nb = b / 2016;
    b %= 2016;

    llt ans = na * nb * Cnt;
    llt tmpa = 0, tmpb = 0;
    for(int i=0;i<2016;++i){
        for(int j=1;j<=a;++j){
            if(i*j%2016==0) ++tmpa;
        }
        for(int j=1;j<=b;++j){
            if(i*j%2016==0) ++tmpb;
        }
    }
    ans += tmpa * nb + tmpb * na;

    for(int i=1;i<=a;++i)for(int j=1;j<=b;++j){
        if(i*j%2016==0) ++ans;
    }
    return ans;
}

int main(){
    // freopen("1.txt","r",stdin);
    for(int i=0;i<2016;++i)for(int j=0;j<2016;++j){
        if(i*j%2016==0) ++Cnt;
    }

    int s, e;
    while(2 == scanf("%d%d", &s, &e)){
        cout<<f(s, e)<<endl;
    }
    
    return 0;
}
