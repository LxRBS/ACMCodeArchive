//#include "input.h"
//#include "output.h"
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")


#define NDEBUG
NDEBUG


#include <algorithm>
//#include <array>
#include <bitset>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <queue>
#include <random>


using namespace std;

template<class T>
using vec = std::vector<T>;

template<class T>
using vec2d = std::vector<std::vector<T>>;


template<class T>
vec2d<T> makeVec2d(const int n1, const int n2, const T initValue) {
  return vec2d<T>(n1, vec<T>(n2, initValue));
}


#define FOR(i, n) for (int i = 0; i < (n); ++i)


#define all(c) c.begin(), c.end()


// TC_REMOVE_BEGIN
/// caide keep
bool __hack = std::ios::sync_with_stdio(false);
/// caide keep
auto __hack1 = cin.tie(nullptr);
// TC_REMOVE_END


// Section with adoption of array and vector algorithms.


//#include "ext/pb_ds/tree_policy.hpp"
//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
//
//template <class T> using StdTree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;


//bool __hack = std::ios::sync_with_stdio(false);
//auto __hack1 = cin.tie(nullptr);

struct Input {

    Input(istream &in) : in(&in) {}

    template<class T>
    T next() const {
        T x;
        *in >> x;
        return x;
    }

    int ni() const {
        return next<int>();
    }

    
    istream *in;
};

Input in(cin);


class Output {

private:
ostream *out;

template<typename T>
void printSingle(const T &value) {
    *out << value;
}


template<typename T>
void printSingle(const vec<T> &v) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i == 0) {
            printSingle(v[i]);
//                *out << v[i];
        } else {
            *out << ' ';
            printSingle(v[i]);
//                *out << ' ' << v[i];
        }
    }
}

public:
Output(ostream &out) : out(&out) {}


inline void print() {}

template<typename T, typename...Ts>
inline void print(const T &f, const Ts&... args) {
    printSingle(f);
    if (sizeof...(args) != 0) {
        *out << ' ';
        print(args...);
    }
}

template<typename...Ts>
inline void println(const Ts&... args) {
    print(args...);
    (*out) << '\n';
}

template<typename...Ts>
inline void operator() (const Ts&... args) {
    println(args...);
}


};

Output out(cout);


namespace template_util {
    

    constexpr int bytecount(uint64_t x) {
        return x ? 1 + bytecount(x >> 8) : 0;
    }

    template<int N>
    struct bytetype {
        
    };

    
    /// caide keep
    template<uint64_t N>
    struct minimal_uint : bytetype<bytecount(N)> {
    };
}


#define dbg(...) ;


const long double EPS = 1e-10;

void solve(istream& inStream, ostream& outStream) {
    in = Input(inStream);
    out = Output(outStream);
    auto n = in.ni();
    auto d = in.ni();
    vec<pair<int, int>> a(n);
    FOR(i, n) {
        auto aa = in.ni();
        a[i] = {aa, i};
    }
    sort(all(a));
    reverse(all(a));

    vec<long double> dp(10, -1e100);
    dp[1] = 0;
    vec2d<pair<int, int>> parent = makeVec2d<pair<int, int>>(n + 1, 10, {-1, -1});
    FOR(i, n) {
        vec<long double> nxt(10, -1e100);
        auto x = log(double(a[i].first));
        dbg("log of", a[i], x);
        FOR(j, 10) {
            if (dp[j] >= -0.5) {
                auto nd = (a[i].first * j) % 10;
                if (nxt[nd] < dp[j] + x - EPS) {
                    nxt[nd] = dp[j] + x;
                    parent[i + 1][nd] = {j, 1};
                }
                if (nxt[j] < dp[j] - EPS) {
                    nxt[j] = dp[j];
                    parent[i + 1][j] = {j, 0};
                }
            }
        }
        dp = nxt;
        dbg("dp is", dp);
    }
    if (dp[d] >= -0.5) {
        vec<int> values;
        int cur = d;
        for (int i = n; i > 0; --i) {
            auto p = parent[i][cur];
            if (p.second == 0) {
                continue;
            } else {
                values.push_back(a[i-1].first);
                cur = p.first;
            }
        }
        sort(all(values));
        if (values.empty()) {
            out(-1);
            return;
        }
        out(values.size());
        out(values);
        return;
    }
    out(-1);
}

//#include <fstream>


int main() {
//  ifstream fin("input.txt");
//  ofstream fout("output.txt");
//    Input in(in);
//    Output out(out);
    solve(cin, cout);
//  solve(fin, fout);
    return 0;
}

