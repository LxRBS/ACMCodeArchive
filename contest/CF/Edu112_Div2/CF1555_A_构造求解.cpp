/**
 * 小披萨6块15分钟，中等的8块20分钟，大的10块25分钟
 * 现在有N个人，要求每个人1块披萨，至少需要多少分钟
 * 发现无论大小，每块披萨的时间是一样的。因此只需找到
 * 最小的6x+8y+10z且大于等于N即可。
 * 构造即可，首先如果N是奇数，令N加1变为偶数
 * 其次依次考虑0/2/4/6/8的情况
 * 例如假设N是x8，则只需x个大披萨和1个中披萨即可
 * 如果N是x6，则只需x个大披萨，1个小披萨即可
 * 其他依次类推
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt N;

llt proc(){
    if(N&1) ++N;
    llt t = N % 10;
    llt q = N / 10;
    if(0 == t){
        return q * 25;
    }
    if(2 == t){
        return q>=1 ? (q-1) * 25 + 30 : 15;
    }
    if(4 == t){
        return q >= 1 ? (q-1) * 25 + 35 : 15;
    }
    if(6 == t){
        return q >= 1 ? (q-1) * 25 + 40 : 15;
    }
    return q * 25 + 20;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%lld", &N);
        printf("%lld\n", proc());
    }
    return 0;
}