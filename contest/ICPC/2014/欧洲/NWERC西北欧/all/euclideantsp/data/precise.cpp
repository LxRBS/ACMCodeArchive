//Solution by lukasP (Lukáš Poláček)
//Golden section search
#include <iostream>
#include <cstdio>
#include <cmath>
#include <NTL/RR.h>
using namespace std;

NTL_CLIENT

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int n; RR p, s, v;
RR base, sqrt2;
RR ff(RR c)
{
    RR first = pow(base, sqrt2 * c) / p * n;
    RR second = s / (c * v);
    return first + second;
}
RR gss(RR a, RR b, RR (*f)(RR)) {
    RR r;
    r = (sqrt(5)-1)/2; //=.618...=golden ratio-1
    RR x1 = b-r*(b-a), x2 = a+r*(b-a);
    RR f1 = f(x1), f2 = f(x2);
    rep(i,0,2000) {
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
    RR::SetPrecision(300);

    RR two; two = 2;
    RR rn; rn = n;
    base = log(rn) / log(two);
    sqrt2 = sqrt(two);
    p *= 1e9;

    RR low; low = 1.2;
    RR::SetOutputPrecision(50);
    RR res = gss(low, low * 100, ff);
    cout << ff(res) + s / v << " " << res << endl;
}
