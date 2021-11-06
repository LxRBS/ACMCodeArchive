#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t, p;
    cin >> t >> p; 
    double v;
    double res;
    if (p > 20)
    {
        v = (1.0 - 0.01 * p) / t;
        res = (0.01 * p - 0.2) / v + 0.2 * 2 / v;
    }
    else
    {
        v = 0.8 / t + 2 * (0.2 - 0.01 * p) / t;
        res = 0.01 * p * 2 / v;
    }
    cout.precision(17);
    cout << fixed;
    cout << res << endl;
    return 0;    
}