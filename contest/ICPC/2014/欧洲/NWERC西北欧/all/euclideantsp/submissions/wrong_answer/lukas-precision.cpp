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
double gss(double a, double b, double (*f)(double), double e = 5e-6) {
    double r = (sqrt(5)-1)/2; //=.618...=golden ratio-1
    double x1 = b-r*(b-a), x2 = a+r*(b-a);
    double f1 = f(x1), f2 = f(x2);
    while (b-a > e) {
        if (f1 < f2) { //change to > to find maximum
            b = x2; x2 = x1; f2 = f1;
            x1 = b-r*(b-a); f1 = f(x1);
        } else {
            a = x1; x1 = x2; f1 = f2;
            x2 = a+r*(b-a); f2 = f(x2);
        }
    }
    return (b + a) / 2;
}
int main()
{
    cin >> n >> p >> s >> v;
    p *= 1e9;

    double res = gss(1.2, 40, ff);
    printf("%.11lf %.11lf\n", ff(res) + s / v, res);
}
