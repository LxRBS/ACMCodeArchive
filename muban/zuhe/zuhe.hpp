#include <bits/stdc++.h>
using namespace std;


#include "mint.hpp"

namespace ZUHE{


struct CSimple{ // 小规模计算组合数

using T = SHULUN::mint;

using vt = vector<T>;
using vvt = vector<vt>;

vvt c;

CSimple() = default;

// n取m的组合数
T get(int n, int m) const {return c[n][m];}

void init(int n){
    this->c.assign(n + 1, vt());
    for(int i=0;i<=n;++i){
        auto & vec = c[i];
        vec.reserve(i + 1);
        vec.emplace_back(T(1));
    }
    for(int i=1;i<=n;++i){
        const auto & prv = c[i - 1];
        auto & vec = c[i];
        for(int j=1;j<i;++j){
            vec.emplace_back(prv[j - 1] + prv[j]);
        }
        vec.emplace_back(T(1));
    }
    return;
}

};


}

