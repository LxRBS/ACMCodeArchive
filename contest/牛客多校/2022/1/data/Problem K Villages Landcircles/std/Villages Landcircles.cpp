//
// Created by 钟梓皓 on 2022/3/30.
//
 
//
// Created by 钟梓皓 on 2022/1/6.
//
 
#ifndef WORKSPACE_TEMPLATE_H
#define WORKSPACE_TEMPLATE_H
 
#include <bits/stdc++.h>
#define mp std::make_pair
#define scanf dont_use_scanf
#define printf dont_use_printf
#define puts dont_use_puts
#define endl dont_use_endl
 
using ll = int64_t;
using pii = std::pair <int, int>;
using piii = std::tuple <int, int, int>;
using piiii = std::tuple <int, int, int, int>;
using pll = std::pair <ll, ll>;
using plll = std::tuple <ll, ll, ll>;
using pllll = std::tuple <ll, ll, ll, ll>;
 
using db = long double;
const db eps = 1e-9;
const db PI = acos(-1.0);
const db INF = 1e100;
 
inline int sig(db p){
    return (p > eps) - (p < -eps);
}
 
inline db sqr(db p){return p * p;}
 
class P{
public:
    db x, y;
    explicit P (db x = 0, db y = 0): x(x), y(y){}
    P operator + (const P &p)const{return P (x + p.x, y + p.y);}
    P operator - (const P &p)const{return P (x - p.x, y - p.y);}
    P operator * (const db &p)const{return P (x * p, y * p);}
    friend P operator * (const db &d, const P &p){return P (d * p.x, d * p.y);}
    P operator / (const db &p)const{return P (x / p, y / p);}
    db operator ^ (const P &p)const{return x * p.y - y * p.x;}
    db operator % (const P &p)const{return x * p.x + y * p.y;}
    db abs2()const{return *this % *this;}
    db abs()const{return std::sqrt(abs2());}
    db angle()const{return std::atan2(y, x);}
 
    // 逆时针旋转 rad 弧度
    P rot(const db &rad)const{
        db sin = std::sin(rad), cos = std::cos(rad);
        return P (x * cos - y * sin, x * sin + y * cos);
    }
 
    P rot90()const{
        return P (-y, x);
    }
 
    P rot60()const{
        const static db sin60 = std::sqrt(3) * 0.5;
        const static db cos60 = 0.5;
        return P(x * cos60 - y * sin60, x * sin60 + y * cos60);
    }
 
    bool operator < (const P &p)const{
        if (sig(x - p.x)) return x < p.x;
        return y < p.y;
    }
 
    bool operator == (const P &p)const{
        return !sig(x - p.x) && !sig(y - p.y);
    }
 
    void read(){
        std::cin >> x >> y;
    }
};
 
class L{
public:
    P p, v;
 
    L (){}
    L (P a, P b):p(a), v(b - a){}
 
    P point(double t){
        return p + v * t;
    }
};
 
// v1 和 v2 是两直线的方向向量
double isLL(L l1, L l2){
    P u = l2.p - l1.p;
    return (u ^ l2.v) / (l1.v ^ l2.v); // 返回交点在 p1v1 上的位置，可以用来判断射线、线段等
}
 
// >0表示 q 在 l 左边
double onLeft(L l, P p){
    return l.v ^ (p - l.p);
}
 
bool check120(P p1, P p2){
    db dot = p1 % p2;
    if (dot >= 0){
        return false;
    }
    return sqr(dot) >= 0.25 * p1.abs2() * p2.abs2();
}
 
bool check_equal120(P p1, P p2){
    db dot = p1 % p2;
    if (dot >= 0){
        return false;
    }
    return !sig(1 - 0.25 * p1.abs2() * p2.abs2() / sqr(dot));
}
 
std::optional <P> fermat_point(P p1, P p2, P p3){
    if (check120(p2 - p1, p3 - p1) || check120(p3 - p2, p1 - p2) || check120(p1 - p3, p2 - p3)){
        return std::nullopt;
    }
    if (sig(onLeft(L(p1, p2), p3)) <= 0){
        std::swap(p2, p3);
    }
    P p4 = p2 + (p1 - p2).rot60();
    P p5 = p3 + (p2 - p3).rot60();
    L l1(p4, p3), l2(p5, p1);
    db t = isLL(l1, l2);
    return l1.point(t);
}
 
//
// Created by 钟梓皓 on 2022/1/23.
//
 
#ifndef WORKSPACE_DISJOINTSET_H
#define WORKSPACE_DISJOINTSET_H
 
#include <bits/stdc++.h>
 
class DisjointSet{
public:
    std::vector <int> fa, sz;
 
    explicit DisjointSet(int n){
        n += 10;
        fa.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; ++ i){
            fa[i] = i;
            sz[i] = 1;
        }
    }
 
    int find(int u){
        return fa[u] == u ? u : (fa[u] = find(fa[u]));
    }
 
    void unite(int u, int v){
        u = find(u), v = find(v);
        if (u == v) return;
        fa[u] = v;
        sz[v] += sz[u];
    }
};
 
#endif //WORKSPACE_DISJOINTSET_H
 
class Solver{
public:
    constexpr static int DEGREE = 3;
    constexpr static int N = 10;
    constexpr static int M = N * 2 + 2;
    using Prufer = std::array <int8_t, M>;
 
    std::array <std::array <int, DEGREE>, M> e;
    std::vector <std::vector <P>> p_solution;
    std::vector <std::vector <pii>> e_solution;
    std::vector <P> p_solution_cur;
    std::vector <pii> e_solution_cur;
    db ans_cur;
    std::array <int, M> deg, dep, fa;
    std::array <std::array <int, M>, M> sort_helper;
    std::array <int, M> sort_cnt;
 
    void add_edge(int u, int v){
        e[u][deg[u] ++] = v;
        e[v][deg[v] ++] = u;
    }
 
    void dfs(int u, int pa){
        fa[u] = pa;
        for (int i = 0; i < deg[u]; ++ i){
            int v = e[u][i];
            if (v == pa){
                continue;
            }
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
 
    int fetch(int pos, int x, int y){
        return e[pos][0] ^ e[pos][1] ^ e[pos][2] ^ x ^ y;
    }
 
    void calc(std::vector <P> ps){
        int n = ps.size();
        int tot = 2 * n - 2;
 
        dep[0] = 0;
        dfs(0, -1);
        sort_cnt = {};
        for (int i = 0; i < tot; ++ i){
            sort_helper[dep[i]][sort_cnt[dep[i]] ++] = i;
        }
        int cnt = 0;
        std::array <int, M> order;
        for (int i = M - 1; i >= 0; -- i){
            for (int j = 0; j < sort_cnt[i]; ++ j){
                order[cnt ++] = sort_helper[i][j];
            }
        }
 
        auto e_back = e;
        auto deg_back = deg;
        int cur = 0;
        ps.resize(tot);
        std::array <int, M> shrink;
        for (int i = 0; i < n - 3; ++ i){
            while (deg[order[cur]] != 1){
                ++ cur;
            }
            int s1 = fa[order[cur]], s2 = fa[s1], s3 = fa[s2];
            int A = order[cur], B = fetch(s1, A, s2);
            int v = fetch(s2, s1, s3);
            if (deg[v] == 1){ // non Steiner point
                int direction = sig(onLeft(L(ps[A], ps[B]), ps[v]));
                if (direction == 0){
                    return;
                }
                P n_point;
                if (direction > 0){
                    n_point = ps[B] + (ps[A] - ps[B]).rot60();
                }
                else{
                    n_point = ps[A] + (ps[B] - ps[A]).rot60();
                }
                deg[A] = deg[B] = 0;
                deg[s1] = 1;
                e[s1] = {s2};
                ps[s1] = n_point;
                shrink[i] = s1;
            }
            else{ // Steiner point
                int C = e[v][0] == s2 ? e[v][1] : e[v][0];
                int D = fetch(v, s2, C);
                int sig_ABC = sig(onLeft(L(ps[A], ps[B]), ps[C]));
                int sig_ABD = sig(onLeft(L(ps[A], ps[B]), ps[D]));
                if (sig_ABC == 0 && sig_ABD == 0){
                    return;
                }
                if (sig_ABC == 0 || sig_ABD == 0){
                    sig_ABC = sig_ABD = sig_ABC + sig_ABD;
                }
                if (sig_ABC == sig_ABD){
                    P n_point;
                    if (sig_ABC > 0){
                        n_point = ps[B] + (ps[A] - ps[B]).rot60();
                    }
                    else{
                        n_point = ps[A] + (ps[B] - ps[A]).rot60();
                    }
                    deg[A] = deg[B] = 0;
                    deg[s1] = 1;
                    e[s1] = {s2};
                    ps[s1] = n_point;
                    shrink[i] = s1;
                    continue;
                }
                int sig_CDA = sig(onLeft(L(ps[C], ps[D]), ps[A]));
                int sig_CDB = sig(onLeft(L(ps[C], ps[D]), ps[B]));
                if (sig_CDA == 0 && sig_CDB == 0){
                    return;
                }
                if (sig_CDA == 0 || sig_CDB == 0){
                    sig_CDA = sig_CDB = sig_CDA + sig_CDB;
                }
                if (sig_CDA == sig_CDB){
                    P n_point;
                    if (sig_CDA > 0){
                        n_point = ps[D] + (ps[C] - ps[D]).rot60();
                    }
                    else{
                        n_point = ps[C] + (ps[D] - ps[C]).rot60();
                    }
                    deg[C] = deg[D] = 0;
                    deg[v] = 1;
                    e[v] = {s2};
                    ps[v] = n_point;
                    shrink[i] = v;
                    continue;
                }
                return;
            }
        }
        int center = e[0][0];
        db ans = INF;
        for (int i = -1; i < n - 3; ++ i){
            int extract = i == -1 ? center : shrink[n - 3 - 1 - i];
            auto [A, B, C] = e_back[extract];
            auto result = fermat_point(ps[A], ps[B], ps[C]);
            if (!result){
                return;
            }
            ps[extract] = *result;
            if (i == -1){
                ans = (ps[extract] - ps[A]).abs() + (ps[extract] - ps[B]).abs() + (ps[extract] - ps[C]).abs();
            }
        }
        for (int i = n; i < tot; ++ i){
            for (int j = 0; j < 3; ++ j){
                int v = e_back[i][j];
                if (!sig((ps[i] - ps[v]).abs2())){
                    return;
                }
                int v1 = e_back[i][(j + 1) % 3];
                if (!check_equal120(ps[v] - ps[i], ps[v1] - ps[i])){
                    return;
                }
            }
        }
        db ans1 = 0;
        for (int i = 0; i < tot; ++ i){
            for (int j = 0; j < deg_back[i]; ++ j){
                int v = e_back[i][j];
                if (i < v){
                    ans1 += (ps[i] - ps[v]).abs();
                }
            }
        }
        if (sig(ans - ans1)){
            assert(false);
        }
        if (ans >= ans_cur){
            return;
        }
        ans_cur = ans;
        p_solution_cur = ps;
        e_solution_cur.clear();
        for (int i = 0; i < tot; ++ i){
            for (int j = 0; j < deg_back[i]; ++ j){
                int v = e_back[i][j];
                if (i < v){
                    e_solution_cur.emplace_back(i, v);
                }
            }
        }
    }
 
    void get_tree(Prufer prufer, int sz){
        std::array <int, M> cur_deg{};
        for (int i = 0; i < 2 * (sz - 2); ++ i){
            prufer[i] += sz - 1;
            ++ cur_deg[prufer[i]];
        }
        for (int i = 0; i < 2 * sz - 2; ++ i){
            ++ cur_deg[i];
        }
        e = {};
        deg = {};
        for (int i = 0, j = 0; i < 2 * sz - 2 && j < 2 * sz - 4; ++ i){
            if (cur_deg[i] != 1){
                continue;
            }
            int x = i;
            while (j < 2 * sz - 4){
                add_edge(x, prufer[j]);
                -- cur_deg[x], -- cur_deg[prufer[j]];
                x = prufer[j ++];
                if (cur_deg[x] > 1 || x > i){
                    break;
                }
            }
        }
        for (int i = 0; i < 2 * sz - 2; ++ i){
            if (cur_deg[i] == 1){
                for (int j = i + 1; j < 2 * sz - 2; ++ j){
                    if (cur_deg[j] == 1){
                        add_edge(i, j);
                        break;
                    }
                }
                break;
            }
        }
    }
 
    void get_prufer(int cur, int n, Prufer prufer, const std::vector <P> &ps){
        if (cur == n){
            get_tree(prufer, ps.size());
            calc(ps);
            return;
        }
        for (int j = 0; j <= 2 * (cur - 1); ++ j){
            Prufer new_prufer;
            int cnt = 0;
            new_prufer[cnt ++] = cur;
            for (int k = 0; k < j; ++ k){
                new_prufer[cnt ++] = prufer[k];
            }
            new_prufer[cnt ++] = cur;
            for (int k = j; k < 2 * (cur - 1); ++ k){
                new_prufer[cnt ++] = prufer[k];
            }
            get_prufer(cur + 1, n, new_prufer, ps);
        }
    }
 
    void solve(){
        int n;
        std::cin >> n;
        std::vector <P> ps(n);
        std::vector <db> r(n);
        for (int i = 0; i < n; ++ i){
            ps[i].read();
            std::cin >> r[i];
        }
        std::vector <db> ans(1 << n, INF), dp(1 << n, INF);
        p_solution.resize(1 << n);
        e_solution.resize(1 << n);
        for (int i = 1; i < 1 << n; ++ i){
            std::vector <P> ps1;
            db radius_sum = 0;
            for (int j = 0; j < n; ++ j){
                if (i >> j & 1){
                    ps1.emplace_back(ps[j]);
                    radius_sum += r[j];
                }
            }
            int sz = ps1.size();
            if (sz == 2){
                ans[i] = (ps1[0] - ps1[1]).abs() - radius_sum;
                p_solution[i] = {ps1[0], ps1[1]};
                e_solution[i] = {{0, 1}};
            }
            else if (sz >= 2){
                ans_cur = INF;
                get_prufer(1, sz - 2 + 1, {}, ps1);
                ans[i] = ans_cur - radius_sum;
                p_solution[i] = p_solution_cur;
                e_solution[i] = e_solution_cur;
            }
        }
        std::vector <pii> pre(1 << n);
        for (int i = 1; i < 1 << n; ++ i){
            if (__builtin_popcount(i) <= 1){
                continue;
            }
            pre[i] = {i, 0};
            dp[i] = ans[i];
        }
        for (int i = 1; i < 1 << n; ++ i){
            if (__builtin_popcount(i) <= 1){
                continue;
            }
            int complement = ((1 << n) - 1) ^ i;
            for (int j = complement; j > 0; j = (j - 1) & complement){
                for (int k = 0; k < n; ++ k){
                    if (i >> k & 1){
                        db &target = dp[i | j];
                        db value = ans[(1 << k) | j] + dp[i];
                        if (target > value){
                            target = value;
                            pre[i | j] = {(1 << k) | j, i};
                        }
                    }
                }
            }
        }
        std::cout << std::fixed << std::setprecision(18);
        std::cout << dp[(1 << n) - 1] << "\n";
 
        // output a solution to make sure the answer is valid
        std::vector <int> components;
        int cur = (1 << n) - 1;
        while (cur > 0){
            auto [u, v] = pre[cur];
            cur = v;
            components.emplace_back(u);
        }
        cur = n;
        std::vector <P> ps1(3 * n);
        std::vector <pii> edge;
        for (auto state: components){
            const auto &p_sol = p_solution[state];
            int sz = p_sol.size();
            std::vector <int> id_map(sz);
            int cnt = 0;
            for (int j = 0; j < n; ++ j){
                if (state >> j & 1){
                    id_map[cnt ++] = j;
                }
            }
            for (int j = cnt; j < sz; ++ j){
                id_map[cnt ++] = cur ++;
            }
            //std::cerr << "Component:";
            for (int i = 0; i < cnt; ++ i){
                ps1[id_map[i]] = p_sol[i];
                //std::cerr << ' ' << id_map[i];
            }
            //std::cerr << ", state: " << state << ", ans: " << dp[state] << '\n';
            for (auto &[u, v]: e_solution[state]){
                edge.emplace_back(id_map[u], id_map[v]);
            }
        }
        for (int i = 0; i < n; ++ i){
            assert(!sig((ps[i] - ps1[i]).abs2()));
        }
        DisjointSet set(3 * n);
        for (auto [u, v]: edge){
            set.unite(u, v);
        }
        for (int i = 1; i < n; ++ i){
            assert(set.find(0) == set.find(i));
        }
        for (int i = n; i < cur; ++ i){
            for (int j = 0; j < n; ++ j){
                assert(sig((ps1[i] - ps[j]).abs2() - sqr(r[j])) >= 0);
            }
        }
        db real_ans = 0;
        for (auto [u, v]: edge){
            real_ans += (ps1[u] - ps1[v]).abs();
            if (u < n){
                real_ans -= r[u];
            }
            if (v < n){
                real_ans -= r[v];
            }
        }
        assert(!sig(dp[(1 << n) - 1] - real_ans));
        // output a solution to stderr
        for (int i = 0; i < cur; ++ i){
            if (i >= n){
                //std::cerr << "*";
            }
            //std::cerr << "p[" << i << "]: (" << ps1[i].x << ", " << ps1[i].y << ")\n";
        }
        for (auto [u, v]: edge){
            //std::cerr << u << " <---> " << v << "\n";
        }
    }
};
 
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int test;
    std::cin >> test;
    while (test --){
        Solver solver;
        solver.solve();
    }
    // floating point number output template
    // std::cout << std::fixed << std::setprecision(18) << 1.0 << '\n';
    return 0;
}
 
#endif //WORKSPACE_TEMPLATE_H
 
/*
2
3
0 2 1
-2 -1 1
2 -1 1
4
0 3 1
0 -3 1
6 3 1
6 -3 1
 
3.211102550927978250
12.000000000000000000
 */
