/// 类欧几里德算法, O(logN)计算如下三个和式
/// floor为向下取整
/// f = SIGMA{floor((ai+b)/c), i=0...n}
/// g = SIGMA{i * floor((ai+b)/c), i=0...n}
/// h = SIGMA{floor((ai+b)/c) ^ 2, i=0...n}
/// 其中f可以单独计算，g和h需要跟f同步混合计算
namespace FloorSum{

using llt = long long;
using t3t = tuple<llt, llt, llt>;

llt const MOD = 998244353LL;
llt const INV_TWO = 499122177LL; // 2的逆
llt const INV_SIX = 166374059LL; // 6的逆

/// 单独计算f = SIGMA{floor((ai+b)/c), i=0...(n-1)!!!}
/// 不取模，可以处理负数
llt fNoMod(llt n, llt a, llt b, llt c){
    llt ans = 0;
    if(a < 0){
        auto a2 = (a % c + c) % c;
        ans -= n * (n - 1) / 2 * ((a2 - a)/ c);
        a = a2;
    }
    if(b < 0){
        auto b2 = (b % c + c) % c;
        ans -= n * ((b2 - b) / c);
        b = b2;
    }
    while(1){
        if(a >= c){
            ans += n * (n - 1) / 2 * (a / c);
            a %= c;
        }
        if(b >= c){
            ans += n * (b / c);
            b %= c;
        }       
        auto y_max = a * n + b;
        if(y_max < c) break;

        n = y_max / c;
        b = y_max % c;
        swap(c, a); 
    }
    return ans;
}

t3t run(llt n, llt a, llt b, llt c){
    function<t3t(llt, llt, llt, llt)> _dfs_run = [&](llt n, llt a, llt b, llt c)->t3t{
        llt ac = a / c, bc = b / c, m = (a * n + b) / c, n1 = n + 1, n21 = n * 2 + 1;
        if(0 == a){
            return {bc * n1 % MOD, bc * n % MOD * n1 % MOD * INV_TWO % MOD, bc * bc % MOD * n1 % MOD};
        }     
        if(a >=c || b >= c){
            t3t d = {
                (n * n1 % MOD * INV_TWO % MOD * ac % MOD + bc * n1 % MOD) % MOD,
                (ac * n % MOD * n1 % MOD * n21 % MOD * INV_SIX % MOD + bc * n % MOD * n1 % MOD * INV_TWO % MOD) % MOD,
                (bc * bc % MOD * n1 % MOD + ac * bc % MOD * n % MOD * n1 % MOD) % MOD
            };
            auto e = _dfs_run(n, a % c, b % c, c);
            const auto & ef = get<0>(e);
            const auto & eg = get<1>(e);
            const auto & eh = get<2>(e);
            (get<2>(d) += eh + 2 * bc % MOD * ef % MOD + 2 * ac % MOD * eg % MOD) %= MOD;
            (get<1>(d) += eg) %= MOD;
            (get<0>(d) += ef) %= MOD;
            return d;
        }
        auto e = _dfs_run(m - 1, c, c - b - 1, a);
        const auto & ef = get<0>(e);
        const auto & eg = get<1>(e);
        const auto & eh = get<2>(e);
        auto df = ((n * m % MOD - ef) % MOD + MOD) % MOD;
        return {
            df,
            ((n * m % MOD * n1 % MOD - eh - ef) % MOD + MOD) % MOD * INV_TWO % MOD,
            ((n * m % MOD * (m + 1) % MOD - 2 * eg - 2 * ef - df) % MOD + MOD) % MOD 
        };
    };
    return _dfs_run(n, a, b, c);
}

};
