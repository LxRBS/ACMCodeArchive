#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

#define x first
#define y second
typedef std::pair<int,int> pii; typedef long long ll; typedef unsigned int ui; 

template <typename T, typename U> std::istream&operator>>(std::istream&i, pair<T,U>&p) {i >> p.x >> p.y; return i;}
template<typename T>std::istream&operator>>(std::istream&i,vector<T>&t) {for(auto&v:t){i>>v;}return i;}


constexpr double PI = 3.14159265358979323846;
template <typename T> struct Segment;

template <typename T> struct Point : public pair<T,T> {
    using pair<T,T>::x;
    using pair<T,T>::y;

    Point(T a=0,T b=0) : pair<T,T>(a,b) {}
    Point(const pair<T,T> &p) : pair<T,T>(p.x,p.y) {}
    Point(const Point<T>&p) = default;
    Point<T>& operator=(const Point<T>&p) = default;

    Point<T>& operator-=(const Point<T>&p) { x -= p.x; y -= p.y; return *this; }
    Point<T>& operator+=(const Point<T>&p) { x += p.x; y += p.y; return *this; }
    Point<T>& operator*=(T f) { x *= f; y *= f; return *this; }
    Point<T> operator-(const Point<T>&p) const { Point<T> t(*this); t -= p; return t; }
    Point<T> operator+(const Point<T>&p) const { Point<T> t(*this); t += p; return t; }
    Point<T> operator*(T f) const { Point<T> t(*this); t *= f; return t; }

    T squaredDistance(const Point<T>&o) const { return Segment<T>{*this,o}.squaredLength(); }
    long double distance(const Point<T>&o) const { return Segment<T>{*this,o}.length(); }
};

// >0 left turn, <0 right turn, =0 straight
template <typename T> T ccw(const Point<T>&a, const Point<T>&b, const Point<T>&c) { return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x); }
template <typename T> double cosangle(const Point<T>&a, const Point<T> &b, const Point<T> &c) {
    return (double)((b.x-a.x)*(c.x-a.x) + (b.y-a.y)*(c.y-a.y)) / a.distance(b) / a.distance(c);
}

template <typename T> double angle(const Point<T>&a, const Point<T> &b, const Point<T> &c) {
    return acos(cosangle(a,b,c));
}
template <typename T> int orientation(const Point<T>&a, const Point<T>&b, const Point<T>&c) { auto o = ccw(a,b,c); return (o>1e-6)-(o<-1e-6); }

template <typename T> struct Segment : public pair<Point<T>,Point<T>> {
    using pair<Point<T>,Point<T>>::x;
    using pair<Point<T>,Point<T>>::y;
    explicit Segment(Point<T> a={0,0}, Point<T> b={0,0}) : pair<Point<T>,Point<T>>(a,b) {}
    Segment(const Segment<T>&) = default;
    Segment<T>& operator=(const Segment<T>&) = default;
    inline T dx() const { return x.x - y.x; }
    inline T dy() const { return x.y - y.y; }
    T squaredLength() const { return dx()*dx()+dy()*dy(); }
    long double length() const { return sqrtl(squaredLength()); }
};

template <typename T> struct Polygon : public vector<Point<T>> {
    using vector<Point<T>>::vector;
    using vector<Point<T>>::at;
    using vector<Point<T>>::front;
    using vector<Point<T>>::back;

    T doubleSignedArea() const {
        if (this->empty()) return T(0);
        T area = back().x*front().y - back().y*front().x;
        for (int i = 0; i < this->size()-1; ++i) area += (at(i).x * at(i+1).y - at(i+1).x * at(i).y);
        return area;
    }

    double circumference() const {
        if (this->empty()) return T(0);
        T res = back().distance(front());
        for (int i = 0; i < this->size()-1; ++i) res += at(i).distance(at(i+1));
        return res;
    }
};

template <typename T> Polygon<T> convexhull(const vector<Point<T>> &v) {
    ui N = (ui)v.size(); vector<Point<T>> w(N+1); int lo = 0;
    for (int i = 0; i<N; ++i) if (v[i].y < v[lo].y || (v[i].y == v[lo].y && v[i].x < v[lo].x)) lo = i;
    Point<T> o = v[lo];
    for (int i = 0; i<N; ++i) w[i+1] = {v[i].x-o.x,v[i].y-o.y};
    swap(w[1],w[lo+1]);

    sort(w.begin()+2,w.end(),[](Point<T>&a,Point<T>&b) {
        if (a.y==0) return b.y != 0 || a.x < b.x;
        if (b.y==0) return false;
        auto disc = (a.x*b.y-a.y*b.x);
        return disc > 0 || (disc == 0 && a.y < b.y);
    });
    w[0] = w[N];
    ui M=1;
    for (int i=2;i<=N;++i) {
        while(ccw(w[M-1],w[M],w[i]) <= 0) if (M>1) --M; else if (i == N) break; else ++i;
        ++M; swap(w[M],w[i]);
    }
    Polygon<T> res(M);
    for (int i=0;i<M;++i) res[i] = {w[i+1].x+o.x,w[i+1].y+o.y};
    return res;
}



#define next(x) (x==M-1?0:x+1)

class Inexact {
public:

    void solve(istream& cin, ostream& cout) {
        int N, W, H; cin >> N >> W >> H;
        vector<Point<ll>> A(N); cin >> A;
        auto Poly = convexhull(A);
        if (Poly.size() <= 2) {
            cout << 0 << '\n';
            return;
        }
        int M = Poly.size();

        vector<Point<double>> DPoly;
        for (int i = 0; i < M; ++i) DPoly.emplace_back(Poly[i].x, Poly[i].y);

        double ans = PI;

        Point<ll> Orig{0,0};
        for (int flip = 0; flip < 2; ++flip) {
            for (int rot = 0; rot < 4; ++rot) {
                int L = 0, R = 0;
                for (int i = 0; i < M; ++i) {
                    if (ccw(Orig, Poly[L], Poly[i]) > 0) L = i;
                    if (ccw(Orig, Poly[R], Poly[i]) < 0) R = i;
                }

                ans = min(ans, angle(Orig, Poly[L], Poly[R]));

                while (true) {
                    if (Poly[L].y <= Poly[next(L)].y) break; // no x-intercept

                    ll num = Poly[L].y * Poly[next(L)].x - Poly[L].x * Poly[next(L)].y;
                    ll den = Poly[L].y - Poly[next(L)].y;

                    Point<double> intercept{double(num)/den, 0};
                    if (intercept.x >= W) break;

                    // find the right-most point from intercept
                    while (true) {
                        if (orientation(intercept, DPoly[R], DPoly[next(R)]) == -1) {
                            R = next(R);
                        } else {
                            break;
                        }
                    }

                    // find whether the angle L/Intercept/R is <= 45 degrees
                    ans = min(ans, angle(intercept, DPoly[L], DPoly[R]));
                    L = next(L);
                }

                swap(W, H);
                for (auto &a: Poly) { swap(a.x, a.y); a.y = H - a.y; }
                for (auto &a: DPoly) { swap(a.x, a.y); a.y = H - a.y; }
            }

            for (auto &a: Poly) a.x = W - a.x;
            for (auto &a: DPoly) a.x = W - a.x;
            reverse(Poly.begin(),Poly.end());
            reverse(DPoly.begin(),DPoly.end());
        }

        cout << fixed << setprecision(10) << ans * 180.0 / PI << '\n';
    }
};


int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	Inexact solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
    return 0;
}