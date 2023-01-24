#include <bits/stdc++.h>
using namespace std;


namespace zifuchuan{


template<typename IT = const char *>
struct Manacher{

using vi = vector<int>;
using pii = pair<int, int>;

/// 从begin开始，一共n个
Manacher(IT begin, int n){
    tmp.reserve(n + n + 3);
    tmp.emplace_back(-2);
    tmp.emplace_back(-1);

	auto it = begin;
    for(int i=0;i<n;++i){
        assert(*it >= 0);
        tmp.emplace_back(*it++);
        tmp.emplace_back(-1);
    }
    tmp.emplace_back(-3);
    assert(tmp.size() == n + n + 3);

    r.assign(tmp.size(), 0);
    r[0] = r[1] = 1;

    int x = 1, total = r.size(), k;
    while(x < total){
        for(k=1;k<r[x];++k){
            if(k + r[x - k] == r[x]) break;
            r[x + k] = min(r[x - k], r[x] - k);
        }

        /// 半径至少是1或者r[x - k]
        r[x + k] = k == r[x] ? 1 : r[x - k];
        if((x += k) >= total - 1) break;
        while(tmp[x + r[x]] == tmp[x - r[x]]) ++r[x];
    }

    auto & ret = result.first;
    auto & start = result.second;
    for(int t,i=0;i<total;++i){
        t = r[i] - 1;
        if(ret < t) start = (i - (ret = t)) >> 1;
    }

    return;
}

const pii & get() const {return result;}

private:
vi tmp; // 临时数组
vi r; // 回文半径数组
pii result; // <最长回文长度, 第一个开始的地方>, 从0开始编号

};


}

