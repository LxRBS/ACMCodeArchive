#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

// if mod is not close to 2^(word_bits-1), it's faster to use comment lines
template <class word, class dword, class sword, word mod, word root>
class Mod {
public:
  static constexpr word mul_inv(word n, int e = 6, word x = 1) {
    return e == 0 ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }

  static constexpr word inv = mul_inv(mod);
  static constexpr word r2 = -dword(mod) % mod;
  static constexpr int word_bits = sizeof(word) * 8;
  static constexpr int level = __builtin_ctzll(mod - 1);

  static word modulus() {
    return mod;
  }
  static word init(const word& w) {
    return reduce(dword(w) * r2);
  }
  static word reduce(const dword& w) {
    word y = word(w >> word_bits) - word((dword(word(w) * inv) * mod) >> word_bits);
    return sword(y) < 0 ? y + mod : y;
    //return word(w >> word_bits) + mod - word((dword(word(w) * inv) * mod) >> word_bits);
  }
  static Mod omega() {
    return Mod(root).pow((mod - 1) >> level);
  }

  Mod() = default;
  Mod(const word& n): x(init(n)) {};
  Mod& operator += (const Mod& rhs) {
    //this->x += rhs.x;
    if ((x += rhs.x) >= mod) x -= mod;
    return *this;
  }
  Mod& operator -= (const Mod& rhs) {
    //this->x += mod * 3 - rhs.x;
    if (sword(x -= rhs.x) < 0) x += mod;
    return *this;
  }
  Mod& operator *= (const Mod& rhs) {
    this->x = reduce(dword(this->x) * rhs.x);
    return *this;
  }
  Mod operator + (const Mod& rhs) const {
    return Mod(*this) += rhs;
  }
  Mod operator - (const Mod& rhs) const {
    return Mod(*this) -= rhs;
  }
  Mod operator * (const Mod& rhs) const {
    return Mod(*this) *= rhs;
  }
  word get() const {
    return reduce(this->x) % mod;
  }
  Mod inverse() const {
    return pow(mod - 2);
  }
  Mod pow(word e) const {
    Mod ret(1);
    for (Mod a = *this; e; e >>= 1) {
      if (e & 1) ret *= a;
      a *= a;
    }
    return ret;
  }
  word x;
};

template <class T>
inline void sum_diff(T& x, T &y) {
  auto a = x, b = y;
  x = a + b, y = a - b;
}

// transform with dif, itransform with dft, no need to use bit_rev
namespace ntt_fast {
template <typename mod_t>
void transform(mod_t* A, int n, const mod_t* roots, const mod_t* iroots) {
  const int logn = __builtin_ctz(n), nh = n >> 1, lv = mod_t::level;
  auto one = mod_t(1), im = roots[lv - 2];
  mod_t dw[lv - 1]; dw[0] = roots[lv - 3];
  for (int i = 1; i < lv - 2; ++i) {
    dw[i] = dw[i - 1] * iroots[lv - 1 - i] * roots[lv - 3 - i];
  }
  dw[lv - 2] = dw[lv - 3] * iroots[1];
  if (logn & 1) for (int i = 0; i < nh; ++i) {
    sum_diff(A[i], A[i + nh]);
  }
  for (int e = logn & ~1; e >= 2; e -= 2) {
    const int m = 1 << e, m4 = m >> 2;
    auto w2 = one;
    for (int i = 0; i < n; i += m) {
      auto w1 = w2 * w2, w3 = w1 * w2;
      for (int j = i; j < i + m4; ++j) {
        auto a0 = A[j + m4 * 0] * one, a1 = A[j + m4 * 1] * w2;
        auto a2 = A[j + m4 * 2] * w1,  a3 = A[j + m4 * 3] * w3;
        auto t02p = a0 + a2, t13p = a1 + a3;
        auto t02m = a0 - a2, t13m = (a1 - a3) * im;
        A[j + m4 * 0] = t02p + t13p; A[j + m4 * 1] = t02p - t13p;
        A[j + m4 * 2] = t02m + t13m; A[j + m4 * 3] = t02m - t13m;
      }
      w2 *= dw[__builtin_ctz(~(i >> e))];
    }
  }
}

template <typename mod_t>
void itransform(mod_t* A, int n, const mod_t* roots, const mod_t* iroots) {
  const int logn = __builtin_ctz(n), nh = n >> 1, lv = mod_t::level;
  const auto one = mod_t(1), im = iroots[lv - 2];
  mod_t dw[lv - 1]; dw[0] = iroots[lv - 3];
  for (int i = 1; i < lv - 2; ++i) {
    dw[i] = dw[i - 1] * roots[lv - 1 - i] * iroots[lv - 3 - i];
  }
  dw[lv - 2] = dw[lv - 3] * roots[1];
  for (int e = 2; e <= logn; e += 2) {
    const int m = 1 << e, m4 = m >> 2;
    auto w2 = one;
    for (int i = 0; i < n; i += m) {
      const auto w1 = w2 * w2, w3 = w1 * w2;
      for (int j = i; j < i + m4; ++j) {
        auto a0 = A[j + m4 * 0], a1 = A[j + m4 * 1];
        auto a2 = A[j + m4 * 2], a3 = A[j + m4 * 3];
        auto t01p = a0 + a1, t23p = a2 + a3;
        auto t01m = a0 - a1, t23m = (a2 - a3) * im;
        A[j + m4 * 0] = (t01p + t23p) * one; A[j + m4 * 2] = (t01p - t23p) * w1;
        A[j + m4 * 1] = (t01m + t23m) * w2;  A[j + m4 * 3] = (t01m - t23m) * w3;
      }
      w2 *= dw[__builtin_ctz(~(i >> e))];
    }
  }
  if (logn & 1) for (int i = 0; i < nh; ++i) {
    sum_diff(A[i], A[i + nh]);
  }
}

template <typename mod_t>
void convolute(mod_t* A, int n, mod_t* B, int m, bool cyclic=false) {
  const int s = cyclic ? std::max(n, m) : n + m - 1;
  const int size = 1 << (31 - __builtin_clz(2 * s - 1));
  mod_t roots[mod_t::level], iroots[mod_t::level];
  roots[0] = mod_t::omega();
  for (int i = 1; i < mod_t::level; ++i) {
    roots[i] = roots[i - 1] * roots[i - 1];
  }
  iroots[0] = roots[0].inverse();
  for (int i = 1; i < mod_t::level; ++i) {
    iroots[i] = iroots[i - 1] * iroots[i - 1];
  }
  std::fill(A + n, A + size, 0); transform(A, size, roots, iroots);
  const auto inv = mod_t(size).inverse();
  if (A == B && n == m) {
    for (int i = 0; i < size; ++i) A[i] *= A[i] * inv;
  } else {
    std::fill(B + m, B + size, 0); transform(B, size, roots, iroots);
    for (int i = 0; i < size; ++i) A[i] *= B[i] * inv;
  }
  itransform(A, size, roots, iroots);
}
}

using mod1_t = Mod<u32, u64, int, 2113929217, 5>;
using mod2_t = Mod<u32, u64, int, 2013265921, 31>;

const int N = 2e6 + 10;

int sn0[N], fac[N], ifac[N], mod;

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

// return x, where ax = 1 (mod mod)
i64 mod_inv(i64 a, i64 mod) {
  if (gcd(a, mod) != 1) return -1;
  i64 b = mod, s = 1, t = 0;
  while (b) {
    i64 q = a / b;
    std::swap(a -= q * b, b);
    std::swap(s -= q * t, t);
  }
  return s < 0 ? s + mod : s;
}

i64 crt(i64 r1, i64 r2) {
  i64 m1 = mod1_t::modulus(), m2 = mod2_t::modulus();
  i64 inv = mod_inv(m1, m2);
  return ((r2 + m2 - r1) * inv % m2 * m1 + r1 + m1 * m2) % (m1 * m2);
}

void convolute(int *a, int n, int *b, int m) {
  static mod1_t A1[N], B1[N];
  static mod2_t A2[N], B2[N];
  for (int i = 0; i < n; ++i) A1[i] = a[i], A2[i] = a[i];
  for (int i = 0; i < n; ++i) B1[i] = b[i], B2[i] = b[i];
  ntt_fast::convolute(A1, n, B1, m);
  ntt_fast::convolute(A2, n, B2, m);
  for (int i = 0; i < n + m; ++i) {
    a[i] = crt(A1[i].get(), A2[i].get()) % mod;
    assert(a[i] >= 0 && a[i] < mod);
  }
}

void solve(int *x, int n) {
  if (n == 0) {
    x[0] = 1;
  } else if (n == 1) {
    x[0] = 0;
    x[1] =  1;
  } else if (n & 1) {
    solve(x, n - 1);
    x[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      x[i + 1] = ((i64)x[i + 1] * (n - 1) + x[i]) % mod;
    }
  } else {
    static int t1[N], t2[N];
    solve(x, n / 2);
    i64 p = 1, e = n / 2;
    for (int i = 0; i <= n / 2; ++i) {
      t1[i] = p * x[i] % mod * fac[i] % mod;
      p = p * e % mod;
      t2[i] = ifac[i];
    }
    std::reverse(t1, t1 + n / 2 + 1);
    convolute(t1, 1 + n / 2, t2, 1 + n / 2);
    std::reverse(t1, t1 + n / 2 + 1);
    e = mod_inv(e, mod);
    p = 1;
    for (int i = 0; i <= n / 2; ++i) {
      t1[i] = p * t1[i] % mod * ifac[i] % mod;
      p = p * e % mod;
    }
    convolute(x, 1 + n / 2, t1, 1 + n / 2);
  }
}

std::vector<int> bs[N];

i64 binom(int n, int m) {
  if (n < m) return 0;
  else return (i64)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

i64 lucas(int n, int m) {
  if (m == 0) return 1;
  return binom(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}

void prepare(int n) {
  assert(n < mod);
  bs[n].resize(n + 1);
  i64 sum = 0, p = 1;
  for (int i = 0; i <= n; ++i) {
    sum += binom(n, i) * p % mod;
    bs[n][i] = sum % mod;
    p = p * (mod - 1) % mod;
  }
}

// sum_{i=0}^{m} binom{n}{i} (-1)^i
i64 sum_binom(i64 n, i64 m) {
  if (m < 0) return 0;
  m = std::min(n, m);
  int nn = n % mod, mm = m % mod;
  if (bs[nn].empty()) prepare(nn);
  i64 ret = mm < (int)bs[nn].size() ? bs[nn][mm] : bs[nn].back();
  if (n < mod) return ret;
  ret = ret * lucas(n / mod, m / mod) % mod * (m / mod % 2 == 0 ? 1 : (mod - 1)) % mod;
  ret += bs[nn].back() * sum_binom(n / mod, m / mod - 1) % mod;
  return ret % mod;
}

i64 sum(i64 n, i64 m) {
  if (m <= 0) return 0;
  i64 n0 = n % mod, n1 = n / mod;
  int li = 0, ri = mod - 1;
  if (n0) ++li, ++ri;
  i64 ret = 0;
  for (int i = li; i < ri && i <= n0; ++i) if (m - i >= n1) {
    ret += sn0[i] * sum_binom(n1, (m - i - n1) / (mod - 1)) % mod;
  }
  ret %= mod;
  if (n1 & 1) ret = mod - ret;
  return ret % mod;
}

int main() {
  i64 n, l, r;
  scanf("%lld%lld%lld%d", &n, &l, &r, &mod);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < mod; ++i) {
    fac[i] = (i64)fac[i - 1] * i % mod;
    ifac[i] = mod_inv(fac[i], mod);
  }
  for (int i = 0; i <= mod; ++i) bs[i].clear();
  solve(sn0, n % mod);
  printf("%lld\n", (sum(n, r) - sum(n, l - 1) + mod) % mod);
  return 0;
}
