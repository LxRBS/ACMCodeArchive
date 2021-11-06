#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
 
using namespace std;
 
typedef long long ll;
 
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
 
pair <double, double> split(double b, double x, double y)
{
    if (b <= x)
    {
        return {b / 2, b / 2};
    }
    else if (b < y)
    {
        return {x / 2, b - x / 2};
    }
    else
    {
        return {x / 2 + (b - y) / 2, y / 2 + (b - x) / 2};
    }
}
 
const int LIM = 20;
 
int main()
{
#ifdef ONPC
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 100;
    cin >> n;
    vector <int> a(n);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        //a[i] = rnd() % 100;
        cin >> a[i];
        sum += a[i];
    }
    int s = rnd() % (sum + 1);
    cin >> s;
    vector <double> p(n);
    for (int i = 0; i < n; i++)
    {
        p[i] = a[i] / (double) sum * s;
    }
    for (int it = 0; it < LIM; it++)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && a[i] <= a[j])
            {
                auto go = split(p[i] + p[j], a[i], a[j]);
                p[i] = go.first, p[j] = go.second;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(20) << p[i] << '\n';
    }
}
