#include <bits/stdc++.h>

using namespace std;

template <typename T>
T power(T a, long long b) {
  T r = 1;
  while (b) {
    if (b & 1) {
      r *= a;
    }
    a *= a;
    b >>= 1;
  }
  return r;
}

int inverse(int a, int m) {
  a %= m;
  if (a < 0) {
    a += m;
  }
  int b = m, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= a * t;
    swap(a, b);
    u -= v * t;
    swap(u, v);
  }
  if (u < 0) {
    u += m;
  }
  return u;
}

template <int _P>
struct modnum {
  static constexpr int P = _P;

 private:
  int v;

 public:
  modnum() : v(0) {
  }

  modnum(long long _v) {
    v = _v % P;
    if (v < 0) {
      v += P;
    }
  }

  explicit operator int() const {
    return v;
  }

  bool operator==(const modnum& o) const {
    return v == o.v;
  }

  bool operator!=(const modnum& o) const {
    return v != o.v;
  }

  modnum inverse() const {
    return modnum(::inverse(v, P));
  }

  modnum operator-() const {
    return modnum(v ? P - v : 0);
  }
  
  modnum operator+() const {
    return *this;
  }

  modnum& operator++() {
    v++;
    if (v == P) {
      v = 0;
    }
    return *this;
  }
  
  modnum& operator--() {
    if (v == 0) {
      v = P;
    }
    v--;
    return *this;
  }

  modnum operator++(int) {
    modnum r = *this;
    ++*this;
    return r;
  }
  
  modnum operator--(int) {
    modnum r = *this;
    --*this;
    return r;
  }

  modnum& operator+=(const modnum& o) {
    v += o.v;
    if (v >= P) {
      v -= P;
    }
    return *this;
  }

  modnum operator+(const modnum& o) const {
    return modnum(*this) += o;
  }

  modnum& operator-=(const modnum& o) {
    v -= o.v;
    if (v < 0) {
      v += P;
    }
    return *this;
  }

  modnum operator-(const modnum& o) const {
    return modnum(*this) -= o;
  }

  modnum& operator*=(const modnum& o) {
    v = (int) ((long long) v * o.v % P);
    return *this;
  }

  modnum operator*(const modnum& o) const {
    return modnum(*this) *= o;
  }
  
  modnum& operator/=(const modnum& o) {
    return *this *= o.inverse();
  }

  modnum operator/(const modnum& o) const {
    return modnum(*this) /= o;
  }
};

template <int _P>
ostream& operator<<(ostream& out, const modnum<_P>& n) {
  return out << int(n);
}

template <int _P>
istream& operator>>(istream& in, modnum<_P>& n) {
  long long _v;
  in >> _v;
  n = modnum<_P>(_v);
  return in;
}

using num = modnum<998244353>;

template <typename T>
struct ntt {
  using num = T;

  const int P = num::P;

  int base = 1, max_base = -1;
  vector<num> roots = {0, 1};
  vector<int> rev = {0, 1};
  num root = num(0);
  
  void init() {
    int tmp = P - 1;
    max_base = 0;
    while (tmp % 2 == 0) {
      tmp /= 2;
      ++max_base;
    }
    root = 2;
    while (true) {
      if (power(root, 1 << max_base) == 1 && power(root, 1 << (max_base - 1)) != 1) {
        break;
      }
      ++root;
    }
  }

  void ensure_base(int nbase) {
    if (max_base == -1) {
      init();
    }
    if (nbase <= base) {
      return;
    }
    assert(nbase <= max_base);
    rev.resize(1 << nbase);
    for (int i = 0; i < 1 << nbase; ++i) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nbase - 1));
    }
    roots.resize(1 << nbase);
    while (base < nbase) {
      num z = power(root, 1 << (max_base - base - 1));
      for (int i = 1 << (base - 1); i < 1 << base; ++i) {
        roots[i << 1] = roots[i];
        roots[i << 1 | 1] = roots[i] * z;
      }
      ++base;
    }
  }

  void dft(vector<num>& a) {
    int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for (int i = 0; i < n; ++i) {
      if (i < rev[i] >> shift) {
        swap(a[i], a[rev[i] >> shift]);
      }
    }
    for (int i = 1; i < n; i <<= 1) {
      for (int j = 0; j < n; j += i << 1) {
        for (int k = 0; k < i; ++k) {
          num x = a[j + k];
          num y = a[j + k + i] * roots[i + k];
          a[j + k] = x + y;
          a[j + k + i] = x - y;
        }
      }
    }
  }

  vector<num> multiply(vector<num> a, vector<num> b) {
    if (a.empty() || b.empty()) {
      return vector<num>();
    }
    int need = a.size() + b.size() - 1;
    int nbase = 0;
    while (1 << nbase < need) {
      ++nbase;
    }
    ensure_base(nbase);
    int sz = 1 << nbase;
    a.resize(sz);
    b.resize(sz);
    bool eq = a == b;
    dft(a);
    if (eq) {
      b = a;
    } else {
      dft(b);
    }
    int isz = num(1) / sz;
    for (int i = 0; i < sz; ++i) {
      a[i] *= b[i] * isz;
    }
    reverse(a.begin() + 1, a.end());
    dft(a);
    a.resize(need);
    return a;
  }
};

ntt<num> ntt_default;

template <int P>
vector<modnum<P>> inverse(vector<modnum<P>> a) {
  int n = a.size();
  int m = (n + 1) >> 1;
  if (n == 1) {
    return {modnum<P>(1) / a[0]};
  } else {
    vector<modnum<P>> b = inverse(vector<modnum<P>>(a.begin(), a.begin() + m));
    int need = n * 2;
    int nbase = 0;
    while (1 << nbase < need) {
      ++nbase;
    }
    ntt_default.ensure_base(nbase);
    int sz = 1 << nbase;
    a.resize(sz);
    b.resize(sz);
    ntt_default.dft(a);
    ntt_default.dft(b);
    int isz = modnum<P>(1) / sz;
    for (int i = 0; i < sz; ++i) {
      a[i] = (modnum<P>(2) - a[i] * b[i]) * b[i] * isz;
    }
    reverse(a.begin() + 1, a.end());
    ntt_default.dft(a);
    a.resize(n);
    return a;
  }
}

template <int P>
vector<modnum<P>>& operator*=(vector<modnum<P>>& a, const vector<modnum<P>>& b) {
  if (a.empty() || b.empty()) {
    a.clear();
  } else {
    if (min(a.size(), b.size()) < 128) {
      vector<modnum<P>> c = a;
      a.assign(a.size() + b.size() - 1, 0);
      for (int i = 0; i < (int) c.size(); i++) {
        for (int j = 0; j < (int) b.size(); j++) {
          a[i + j] += c[i] * b[j];
        }
      }
    } else {
      a = ntt_default.multiply(a, b);
    }
  }
  return a;
}

template <int P>
vector<modnum<P>> operator*(const vector<modnum<P>>& a, const vector<modnum<P>>& b) {
  vector<modnum<P>> c = a;
  return c *= b;
}

template <typename T>
vector<T>& operator+=(vector<T>& a, const vector<T>& b) {
  if (a.size() < b.size()) {
    a.resize(b.size());
  }
  for (int i = 0; i < (int) b.size(); i++) {
    a[i] += b[i];
  }
  return a;
}

template <typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c += b;
}

template <typename T>
vector<T>& operator-=(vector<T>& a, const vector<T>& b) {
  if (a.size() < b.size()) {
    a.resize(b.size());
  }
  for (int i = 0; i < (int) b.size(); i++) {
    a[i] -= b[i];
  }
  return a;
}

template <typename T>
vector<T> operator-(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c -= b;
}

template <typename T>
vector<T>& operator*=(vector<T>& a, const vector<T>& b) {
  if (a.empty() || b.empty()) {
    a.clear();
  } else {
    vector<T> c = a;
    a.assign(a.size() + b.size() - 1, 0);
    for (int i = 0; i < (int) c.size(); i++) {
      for (int j = 0; j < (int) b.size(); j++) {
        a[i + j] += c[i] * b[j];
      }
    }
  }
  return a;
}

template <typename T>
vector<T> operator*(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c *= b;
}

template <typename T>
vector<T> inverse(const vector<T>& a) {
  assert(!a.empty());
  int n = a.size();
  vector<T> b = {T(1) / a[0]};
  while ((int) b.size() < n) {
    vector<T> a_cut(a.begin(), a.begin() + min(a.size(), b.size() << 1));
    vector<T> x = b * b * a_cut;
    b.resize(b.size() << 1);
    for (int i = b.size() >> 1; i < (int) min(x.size(), b.size()); ++i) {
      b[i] = -x[i];
    }
  }
  b.resize(n);
  return b;
}

template <typename T>
vector<T>& operator/=(vector<T>& a, const vector<T>& b) {
  int n = a.size();
  int m = b.size();
  if (n < m) {
    a.clear();
  } else {
    vector<T> d = b;
    reverse(a.begin(), a.end());
    reverse(d.begin(), d.end());
    d.resize(n - m + 1);
    a *= inverse(d);
    a.erase(a.begin() + n - m + 1, a.end());
    reverse(a.begin(), a.end());
  }
  return a;
}

template <typename T>
vector<T> operator/(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c /= b;
}

template <typename T>
vector<T>& operator%=(vector<T>& a, const vector<T>& b) {
  int n = a.size();
  int m = b.size();
  if (n >= m) {
    vector<T> c = (a / b) * b;
    a.resize(m - 1);
    for (int i = 0; i < m - 1; i++) {
      a[i] -= c[i];
    }
  }
  return a;
}

template <typename T>
vector<T> operator%(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c %= b;
}

template <typename T>
vector<T> derivative(const vector<T>& a) {
  vector<T> c = a;
  for (int i = 0; i < (int) c.size(); i++) {
    c[i] *= i;       
  }
  if (!c.empty()) {
    c.erase(c.begin());
  }
  return c;
}
 
template <typename T>
vector<T> primitive(const vector<T>& a) {
  vector<T> c = a;
  c.insert(c.begin(), 0);
  for (int i = 1; i < (int) c.size(); i++) {
    c[i] /= i;
  }
  return c;
}

template <typename T>
vector<T> logarithm(const vector<T>& a) {
  assert(!a.empty() && a[0] == 1);
  vector<T> u = primitive(derivative(a) * inverse(a));
  u.resize(a.size());
  return u;
}
 
template <typename T>
vector<T> exponent(const vector<T>& a) {
  assert(!a.empty() && a[0] == 0);
  int n = a.size();
  vector<T> b = {1};
  while ((int) b.size() < n) {
    vector<T> x(a.begin(), a.begin() + min(a.size(), b.size() << 1));
    x[0] += 1;
    vector<T> old_b = b;
    b.resize(b.size() << 1);
    x -= logarithm(b);
    x *= old_b;
    for (int i = b.size() >> 1; i < (int) min(x.size(), b.size()); i++) {
      b[i] = x[i];
    }
  }
  b.resize(n);
  return b;
}

template <typename T>
vector<T> sqrt(const vector<T>& a) {
  assert(!a.empty() && a[0] == 1);
  int n = a.size();
  vector<T> b = {1};
  while ((int) b.size() < n) {
    vector<T> x(a.begin(), a.begin() + min(a.size(), b.size() << 1));
    b.resize(b.size() << 1);
    x *= inverse(b);
    T inv2 = T(1) / 2;
    for (int i = b.size() >> 1; i < (int) min(x.size(), b.size()); i++) {
      b[i] = x[i] * inv2;
    }
  }
  b.resize(n);
  return b;
}

template <typename T>
vector<T> evaluate(const vector<T>& f, const vector<T>& x) {
  int n = x.size();
  if (!n) {
    return vector<T>();
  }
  vector<vector<T>> up(n * 2);
  for (int i = 0; i < n; ++i) {
    up[i + n] = vector<T>{-x[i], 1};
  }
  for (int i = n - 1; i; --i) {
    up[i] = up[i << 1] * up[i << 1 | 1];
  }
  vector<vector<T>> down(n * 2);
  down[1] = f % up[1];
  for (int i = 2; i < n * 2; ++i) {
    down[i] = down[i >> 1] % up[i];
  }
  vector<T> y(n);
  for (int i = 0; i < n; ++i) {
    y[i] = down[i + n][0];
  }
  return y;
}

template <typename T>
vector<T> interpolate(const vector<T>& x, const vector<T>& y) {
  int n = x.size();
  vector<vector<T>> up(n * 2);
  for (int i = 0; i < n; ++i) {
    up[i + n] = vector<T>{-x[i], 1};
  }
  for (int i = n - 1; i; --i) {
    up[i] = up[i << 1] * up[i << 1 | 1];
  }
  vector<T> a = evaluate(derivative(up[1]), x);
  for (int i = 0; i < n; ++i) {
    a[i] = y[i] / a[i];
  }
  vector<vector<T>> down(n * 2);
  for (int i = 0; i < n; ++i) {
    down[i + n] = vector<T>{a[i]};
  }
  for (int i = n - 1; i; --i) {
    down[i] = down[i << 1] * up[i << 1 | 1] + down[i << 1 | 1] * up[i << 1];
  }
  return down[1];
}

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<num> a(n + 1);
    for (int i = 0; i <= n; ++i) {
      cin >> a[i];
    }
    vector<num> b(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      cin >> b[i];
    }
    vector<num> c(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      cin >> c[i];
    }
    vector<num> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
      fact[i] = fact[i - 1] * i;
    }
    function<vector<num>(int, int)> multiply_all = [&](int l, int r) {
      if (l == r) {
        return vector<num>{c[l], b[l]};
      } else {
        int y = (l + r) >> 1;
        return multiply_all(l, y) * multiply_all(y + 1, r);
      }
    };
    vector<num> d = multiply_all(0, n - 2);
    for (int i = 0; i <= n; ++i) {
      a[i] *= fact[i];
    }
    reverse(d.begin(), d.end());
    a *= d;
    for (int i = 0; i <= n; ++i) {
      if (i) {
        cout << " ";
      }
      cout << a[i + n - 1] / fact[i];
    }
    cout << "\n";
  }
  return 0;
}