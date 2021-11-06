#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t, p;
    cin >> t >> p; 
    double v = (1.0 - 0.01 * p) / t;
    double res = 0;
    if (p > 20)
    {
        res += (0.01 * p - 0.2) / v;
        p = 20;
    }
    res += 0.01 * p * 2 / v;
    cout.precision(4);
    cout << fixed;
    cout << res << endl;
    return 0;    
}