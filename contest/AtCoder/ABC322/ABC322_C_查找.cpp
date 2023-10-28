/**
 * 给定M个数，A1到AM，均在[1, N]范围内
 * for i in [1, N]: 问大于等于i的最小的Aj是多少，输出差
 * 做一个二分查找O(NlogN)
 * 或者双指针O(N)
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> vec(m);
    for(auto & i : vec) cin >> i;
    for(int i=1;i<=n;++i){
        auto p = equal_range(vec.begin(), vec.end(), i);
        if(p.first != p.second){
            assert(i == *p.first);
            cout << 0 << endl;
        }else{
            cout << *p.first - i << endl;
        }
    }
    return 0;
}