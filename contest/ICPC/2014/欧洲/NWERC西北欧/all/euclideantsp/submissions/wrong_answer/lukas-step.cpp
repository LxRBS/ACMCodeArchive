//Solution by lukasP (Lukáš Poláček)
//Golden section search
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int n; double p, s, v;
double ff(double c)
{
    double first = n * pow(log(n) / log(2), sqrt(2) * c) / p;
    double second = s / (c * v);
    return first + second;
}
int main()
{
    cin >> n >> p >> s >> v;
    p *= 1e9;

    double res = ff(3), val = 3;
    for (double q = 1.22; q <= 38.16; q += 1e-5)
    {
        double tmp = ff(q);
        if (tmp < res)
        {
            res = tmp;
            val = q;
        }
    }
    printf("%.11lf %.11lf\n", res + s / v, val);
}
