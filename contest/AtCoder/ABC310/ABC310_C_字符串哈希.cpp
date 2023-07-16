/**
 * 给定若干个字符串，问互异的有多少个。
 * 注意reverse相等的也算相等。
 * 对每个原字符串和reverse，只计算字典序小的哈希即可
 * 将哈希塞入set，最后看set的size即可
 * 自然溢出，双哈希也不行，用了三哈希。
 * 标程直接用set<string>。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N;
set<tuple<ull, ull, ull>> Set;

template<typename IT>
tuple<ull, ull, ull> BKDRHash(IT s, IT e){
    static const ull S1 = 13313;
    static const ull S2 = 31;
    static const ull S3 = 13331;
    tuple<ull, ull, ull> ans = {0ULL, 0ULL, 0ULL};
    for(auto it=s;it!=e;++it){
        get<0>(ans) =get<0>(ans) * S1 + (*it - 'a');  
        get<1>(ans) = get<1>(ans) * S2 + (*it - 'a');  
        get<2>(ans) = get<2>(ans) * S3 + (*it - '0');
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> N;
    for(int i=0;i<N;++i){
        string s; cin >> s;
        string t(s.rbegin(), s.rend());
        if(s <= t) Set.insert(BKDRHash(s.begin(), s.end()));
        else Set.insert(BKDRHash(t.begin(), t.end()));
    }
    cout << Set.size() << endl;
    return 0;
}