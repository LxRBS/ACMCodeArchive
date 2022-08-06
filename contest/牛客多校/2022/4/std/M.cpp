#include <bits/stdc++.h>
using namespace std;

using _T=long long;

constexpr _T eps=1e-8;

template<typename T> struct point
{
    T x,y;

    bool operator==(const point &a) const {return (abs(x-a.x)<=eps && abs(y-a.y)<=eps);}
    bool operator<(const point &a) const {if (abs(x-a.x)<=eps) return y<a.y-eps; return x<a.x-eps;}
    bool operator>(const point &a) const {return !(*this<a || *this==a);}
    point operator+(const point &a) const {return {x+a.x,y+a.y};}
    point operator-(const point &a) const {return {x-a.x,y-a.y};}
    point operator-() const {return {-x,-y};}
    point operator*(const T k) const {return {k*x,k*y};}
    point operator/(const T k) const {return {x/k,y/k};}
    T operator*(const point &a) const {return x*a.x+y*a.y;}
    T operator^(const point &a) const {return x*a.y-y*a.x;}
    int toleft(const point &a) const {const auto t=(*this)^a; return (t>eps)-(t<-eps);}
    T len2() const {return (*this)*(*this);}
    T dis2(const point &a) const {return (a-(*this)).len2();}
};

using Point=point<_T>;

struct argcmp
{
    bool operator()(const Point &a,const Point &b) const
    {
        const auto quad=[](const Point &a)
        {
            if (a.y<-eps) return 1;
            if (a.y>eps) return 4;
            if (a.x<-eps) return 5;
            if (a.x>eps) return 3;
            return 2;
        };
        const int qa=quad(a),qb=quad(b);
        if (qa!=qb) return qa<qb;
        const auto t=a^b;
        //if (abs(t)<=eps) return a*a<b*b-eps;
        return t>eps;
    }
};

pair<bool,Point> solve(const vector<Point> &vec)
{
    vector<Point> mp;
    for (size_t i=1;i<vec.size();i++)
    {
        if (vec[i]==vec[i-1]) continue;
        const Point vd=vec[i]-vec[i-1];
        const Point vl={vd.y,-vd.x},vr={-vd.y,vd.x};
        mp.push_back(vl);
        mp.push_back(vr);
    }
    if (mp.empty()) return {true,{1,0}};
    mp.push_back({-1,0});
    sort(mp.begin(),mp.end(),argcmp());
    const auto eq=[](const Point &u,const Point &v){return !argcmp()(u,v) && !argcmp()(v,u);};
    mp.erase(unique(mp.begin(),mp.end(),eq),mp.end());
    const auto id=[&](const Point &u){return lower_bound(mp.begin(),mp.end(),u,argcmp())-mp.begin();};
    vector<int> sum(mp.size());
    int cnt=0;
    for (size_t i=1;i<vec.size();i++)
    {
        if (vec[i]==vec[i-1]) continue;
        const Point vd=vec[i]-vec[i-1];
        const Point vl={vd.y,-vd.x},vr={-vd.y,vd.x};
        const size_t il=id(vl),ir=id(vr);
        if (il>ir) sum[il]++,sum[0]++,sum[ir+1]--;
        else if (ir==mp.size()-1) sum[il]++;
        else sum[il]++,sum[ir+1]--;
        cnt++;
    }
    partial_sum(sum.begin(),sum.end(),sum.begin());
    for (size_t i=0;i<mp.size();i++)
    {
        if (sum[i]==cnt) return {true,mp[i]};
    }
    return {false,{0,0}};
}

int main()
{
    int n;
    scanf("%d",&n);
    vector<Point> vec(n);
    for (int i=0;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        vec[i]={x,y};
    }
    auto [u,v]=solve(vec);
    if (!u) printf("NO\n");
    else printf("YES\n0 0 %lld %lld\n",v.x,v.y);
    return 0;
}