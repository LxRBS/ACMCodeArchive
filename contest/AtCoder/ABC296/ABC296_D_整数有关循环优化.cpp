/**
 * 给定N和M，要求找到两个数a和b，满足
 * 1. 1 <= a, b <= N
 * 2. ab >= M
 * 3. ab是所有满足上述2个条件中最小的
 * 输出ab。如果找不到，输出-1
 * 首先可以假设a<=b，然后可以发现a必然与sqrt(M)同量级，否则ab之积肯定不是最小的
 * 因此做一个[1, min(N, sqrt(M))]的循环即可，对每一个固定的a，肯定有一个唯一的b使得ab满足条件，判断一下即可
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using Real = long double;

llt N, M;

llt proc(){
    llt ans = -1;
    llt x;
    for(llt i=1;i<=N;++i){
        x = (M + i - 1) / i;
        if(x <= N){
            if(-1 == ans) ans = i * x;
            else ans = min(ans, i * x);
        }
        if(i >= x) break;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    cout << proc() << endl;
    return 0;
}