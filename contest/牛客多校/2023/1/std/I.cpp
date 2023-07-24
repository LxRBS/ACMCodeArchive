#include <bits/stdc++.h>

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

const int MaxN = 32;

template<typename T>
inline T lowbit(T a) { return a & -a; }

struct VectorGroup;
struct Poly;

// Square matrix over F_2.
struct Matrix {
    uint a[MaxN]; // column vectors
    int dim;      // dimension

    explicit Matrix(int dim) : dim(dim) {}

    static Matrix zero(int dim) {
        Matrix res(dim);
        for (int i = 0; i < dim; i++) res.a[i] = 0;
        return res;
    }

    static Matrix identity(int dim) {
        Matrix res(dim);
        for (int i = 0; i < dim; i++) res.a[i] = 1U << i;
        return res;
    }

    Matrix operator+(const Matrix &rhs) const {
        assert(dim == rhs.dim);
        Matrix res(dim);
        for (int i = 0; i < dim; i++)
            res.a[i] = a[i] ^ rhs.a[i];
        return res;
    }

    Matrix &operator+=(const Matrix &rhs) {
        assert(dim == rhs.dim);
        for (int i = 0; i < dim; i++) a[i] ^= rhs.a[i];
        return *this;
    }

    uint operator*(uint v) const {
        uint res = 0;
        for (int i = 0; i < dim; i++)
            if (v >> i & 1) res ^= a[i];
        return res;
    }

    Matrix operator*(const Matrix &rhs) const {
        assert(dim == rhs.dim);
        Matrix res = Matrix::zero(dim);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                if (rhs.a[i] >> j & 1) res.a[i] ^= a[j];
        return res;
    }

    // left multiply
    Matrix &operator*=(const Matrix &lhs) {
        return *this = lhs * (*this);
    }

    Matrix pow(uint b) const {
        Matrix res = Matrix::identity(dim), tmp = *this;
        for (; b; b >>= 1) {
            if (b & 1) res = res * tmp;
            tmp = tmp * tmp;
        }
        return res;
    }

    VectorGroup image() const;

    int rank() const;

    Poly minimal_polynomial() const;
};

using vectors_t = std::vector<uint>;

// Linear group of vectors over F_2.
struct VectorGroup {
    uint e[MaxN]; // basis vectors
    int cnt = 0;  // count of basis vectors

    VectorGroup() = default;

    explicit VectorGroup(const Matrix &mat) {
        for (int i = 0; i < mat.dim; i++) insert(mat.a[i]);
    }

    int rank() const { return cnt; }

    inline bool insert(uint v) {
        for (int i = 0; i < cnt; i++) {
            if (v & lowbit(e[i])) v ^= e[i];
        }
        if (v == 0) return false;
        e[cnt++] = v;
        return true;
    }
};

VectorGroup Matrix::image() const {
    return VectorGroup(*this);
}

int Matrix::rank() const {
    return image().rank();
}

// Polynomial over F_2 (non-zero).
struct Poly {
    uint coef; // coefficients except z^deg
    int deg;   // degree

    Poly(uint p, int k) : coef(p), deg(k) {}

    // coefficients containing z^deg
    inline ull full_coef() const { return coef | (1ULL << deg); }
};

// Finite field F_2[z] / <p(z)>.
struct Field {
    Poly mod; // p(z)

    explicit Field(const Poly &mod) : mod(mod) {
        assert(mod.deg > 0);
    }

    inline uint multiply_z(uint a) const {
        ull res = (ull) a << 1;
        return (res >> mod.deg & 1) ? (res ^ mod.full_coef()) : res;
    }

    // Calculate a(z) * b(z) mod p(z).
    inline uint multiply(uint a, uint b) const {
        uint res = 0;
        for (int i = 0; b != 0; i++) {
            if (b >> i & 1) {
                b ^= 1U << i;
                res ^= a;
            }
            a = multiply_z(a);
        }
        return res;
    }

    // Find min positive n such that z^n mod p(z) = 1 using BSGS algorithm.
    uint order() const {
        std::unordered_map<uint, uint> map;
        uint chunk_size = 1 << (mod.deg / 2);
        uint tmp = 1, inv = 1, inv_z = (mod.full_coef() ^ 1) >> 1;
        for (uint i = 0; i < chunk_size; i++) {
            if (i > 0 && tmp == 1) return i;
            map.insert({inv, i});
            tmp = multiply_z(tmp);
            inv = multiply(inv, inv_z);
        }
        uint cur = 1;
        for (uint i = 1;; i++) {
            cur = multiply(cur, tmp);
            auto it = map.find(cur);
            if (it != map.end())
                return i * chunk_size + it->second;
        }
    }
};

// Linear group of matrices over F_2.
struct MatrixGroup {
    struct Item {
        Matrix mat;  // basis matrix
        int ind;     // index of non-zero flag vector in e[i]
        uint mask;   // linear expression of e[i] using v[0]..v[i]
    };
    std::vector<Item> arr;
    int dim;         // dimension of matrices in the group

    MatrixGroup(int dim) : dim(dim) {}

    int rank() const { return arr.size(); }

    inline uint insert(Matrix mat) {
        assert(mat.dim == dim);
        uint res = 0;
        for (auto &e: arr) {
            if (mat.a[e.ind] & lowbit(e.mat.a[e.ind])) {
                mat += e.mat;
                res ^= e.mask;
            }
        }
        for (int i = 0; i < dim; i++) {
            if (mat.a[i] != 0) {
                arr.push_back({mat, i, res | (1U << rank())});
                return 0;
            }
        }
        return res;
    }
};

// Calculate the minimal polynomial of the matrix.
Poly Matrix::minimal_polynomial() const {
    MatrixGroup group(dim);
    Matrix cur = Matrix::identity(dim);
    while (true) {
        uint p = group.insert(cur);
        if (p != 0) return Poly(p, group.rank());
        cur *= *this;
    }
}

using factors_t = std::vector<std::pair<uint, int>>;
using coefs_t = std::vector<int>;

// Factorize `x` and return the (prime, degree) pairs.
factors_t factorize(uint x) {
    factors_t pfac;
    for (uint p = 2; (ull) p * p <= x; p++) {
        if (x % p == 0) {
            int k = 1;
            while ((x /= p) % p == 0) k++;
            pfac.push_back({p, k});
        }
    }
    if (x != 1) pfac.push_back({x, 1});
    return pfac;
}

// Get the coefficients for the calculated `pfac` and store them in `coef`.
int get_factor_coefs(const factors_t &pfac, coefs_t &coef) {
    int num = 1;
    for (auto[p, k]: pfac) {
        coef.push_back(num);
        num *= (k + 1);
    }
    return num;
}


int n;
Matrix trans(0);

uint ord;

factors_t pfac;
coefs_t coef;

std::vector<uint> num;
std::vector<int> dim, ndim;
std::vector<ll> dp;

void dfs(uint x, int id, uint S, int step) {
    if (step < (int) pfac.size()) {
        auto[p, k] = pfac[step];
        uint y = x;
        dfs(y, id, S, step + 1);
        for (int i = 1; i <= k; i++)
            dfs(y *= p, id + i * coef[step], S | (1U << step), step + 1);
    } else {
        num[id] = ord / x;
        dim[id] = n - (trans.pow(num[id]) + Matrix::identity(n)).rank();
        ndim[id] = dim[id];
        dp[id] = 1LL << dim[id];
        for (uint T = S; T != 0; T = (T - 1) & S) {
            int id_y = id, mu = 1;
            for (int i = 0; i < step; i++) {
                if (T >> i & 1) {
                    id_y -= coef[i];
                    mu *= -1;
                }
            }
            ndim[id_y] += mu * ndim[id];
            dp[id_y] += mu * dp[id];
        }
    }
}

void xor_shift(Matrix &mat, int bits) {
    uint mask = (1ULL << n) - 1;
    for (int i = 0; i < n; i++)
        mat.a[i] ^= bits > 0 ? (mat.a[i] << bits) & mask : mat.a[i] >> -bits;
}

typedef long long ll;
const ll P = 998244353;

ll pw(ll a, ll x = P - 2) {
    ll ret = 1;
    for (; x; x >>= 1, a = a * a % P)
        if (x & 1) ret = ret * a % P;
    return ret;
}

int main() {
    int m;
    scanf("%d%d", &m, &n);

    trans = Matrix::identity(n);
    for (int i = 0; i < m; i++) {
        int b;
        scanf("%d", &b);
        xor_shift(trans, b);
    }

    Poly mpoly = trans.minimal_polynomial();

    Field field(mpoly);
    ord = field.order();

    pfac = factorize(ord);
    int fcnt = get_factor_coefs(pfac, coef);

    num.resize(fcnt);
    dim.resize(fcnt);
    ndim.resize(fcnt);
    dp.resize(fcnt);
    dfs(1, 0, 0, 0);

    ll ans = 0;
    for (int i = 0; i < fcnt; i++) {
        (ans += dp[i] % P * (ll) num[i]) %= P;
    }
    printf("%lld\n", ans * pw(2, P - 1 - n) % P);
    return 0;
}
