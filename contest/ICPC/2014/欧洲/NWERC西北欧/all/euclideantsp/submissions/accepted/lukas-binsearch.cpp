//Solution by lukasP (Lukáš Poláček)
//Find the minimum analytically by differentiation and then try to find the minimal point with
//binary search
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int n; double p, s, v;
int main()
{
    cin >> n >> p >> s >> v;
    p *= 1e9;

    double a = pow(log(n) / log(2), sqrt(2));
    double b = s * p / v / n;

    double down = 1e-8, up = 1e9;
    rep(iter,0,90)
    {
        double m = (up + down) / 2;
        double res = pow(a, m) * m * m;
        if (res < b / log(a))
            down = m;
        else
            up = m;
    }

    double comput = n * pow(log(n) / log(2), sqrt(2) * down) / p;
    double travel = s * (1 + 1 / down) / v;
    printf("%.11lf %.11lf\n", comput + travel, down);
}
