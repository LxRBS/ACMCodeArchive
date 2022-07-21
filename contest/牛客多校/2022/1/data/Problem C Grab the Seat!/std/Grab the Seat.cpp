#include <bits/stdc++.h>
 
const int N = 200010;
using ll = long long;
 
struct frac{
    ll x, y;
 
    explicit frac(ll x = 0, ll y = 1):x(x), y(y){
        if (y < 0){
            this -> x = -this -> x;
            this -> y = -this -> y;
        }
    }
 
    bool operator < (const frac &f)const{
        return x * f.y < y * f.x;
    }
 
    bool operator > (const frac &f)const{
        return x * f.y > y * f.x;
    }
};
 
std::vector <int> vec[N];
int x[N], y[N], min[N];
 
int main(){
    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (int i = 0; i < k; ++ i){
        scanf("%d%d", &x[i], &y[i]);
    }
    while (q --){
        int pos;
        scanf("%d", &pos);
        -- pos;
        scanf("%d%d", &x[pos], &y[pos]);
        for (int i = 0; i < N; ++ i){
            vec[i].clear();
        }
        for (int i = 0; i < k; ++ i){
            vec[y[i]].emplace_back(x[i]);
        }
        for (int i = 1; i <= m; ++ i){
            min[i] = n + 1;
        }
        frac max(-1, 0);
        for (int i = 1; i <= m; ++ i){
            if (i == 1){
                for (auto u : vec[i]){
                    min[i] = std::min(min[i], u);
                }
                continue;
            }
            for (auto u : vec[i]){
                max = std::max(max, frac( i - 1, u - 0));
            }
            if (max.y != 0){
                ll x_pos = max.y * (i - 1);
                x_pos = (x_pos + max.x - 1) / max.x;
                if (x_pos < min[i]){
                    min[i] = x_pos;
                }
            }
        }
        max = frac(-1, 0);
        for (int i = m; i >= 1; -- i){
            if (i == m){
                for (auto u : vec[i]){
                    min[i] = std::min(min[i], u);
                }
                continue;
            }
            for (auto u : vec[i]){
                max = std::max(max, frac( m - i, u - 0));
            }
            if (max.y != 0){
                ll x_pos = max.y * (m - i);
                x_pos = (x_pos + max.x - 1) / max.x;
                if (x_pos < min[i]){
                    min[i] = x_pos;
                }
            }
        }
        ll ans = 0;
        for (int i = 1; i <= m; ++ i){
            ans += min[i] - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
