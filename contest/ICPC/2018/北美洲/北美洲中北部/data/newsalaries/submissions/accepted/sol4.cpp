#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/stack:16777216")
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <cassert>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <stack>
#include <deque>
#include <cmath>
#include <memory.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <utility>
#include <time.h>
#include <complex>
using namespace std;

#define FOR(i, a, b) for(int i=(a);i<(b);i++)
#define RFOR(i, b, a) for(int i=(b)-1;i>=(a);--i)
#define FILL(A,value) memset(A,value,sizeof(A))

#define ALL(V) V.begin(), V.end()
#define SZ(V) (int)V.size()
#define PB push_back
#define MP make_pair
#define Pi 3.14159265358979
#define x0 ikjnrmthklmnt
#define y0 lkrjhkltr
#define y1 ewrgrg

typedef long long Int;
typedef unsigned long long UInt;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef pair<Int, Int> PLL;
typedef pair<double, double> PDD;
typedef complex<double> base;

const int INF = 1000000000;
const int BASE = 1000000007;
const int MAX = 100007;
const int MAX2 = 7777;
const int MAXE = 100000;
const int ADD = 1000000;
const int MOD = 1008691207;
const int CNT = 800;

#define LD __float128

LD L[MAX];
LD R[MAX];

LD S[4][MAX];

int main()
{
//    freopen("in.txt", "r", stdin);
    //freopen("distance.in",  "r", stdin);
    //freopen("distance.out", "w", stdout);
    //freopen("out.txt" , "w" , stdout);
    
    int n;
    cin >> n;
    FOR(i,0,n)
    {
        double l , r;
        cin >> l >> r;
        L[i] = l;
        R[i] = r;
    }
    
    double res = 0;
    
    FOR(i,0,n)
    {
        res += (i - (n - 1 - i)) * (R[i] + L[i]) / 2;
    }
    
    FOR(i,0,4)
    {
        S[i][0] = 0;
    }
    
    FOR(i,0,n)
    {
        if (R[i] > L[i])
        {
            S[0][i + 1] = S[0][i] + R[i] * R[i] * R[i] / (R[i] - L[i]);
            S[1][i + 1] = S[1][i] - 3 * R[i] * R[i] / (R[i] - L[i]);
            S[2][i + 1] = S[2][i] + 3 * R[i] / (R[i] - L[i]);
            S[3][i + 1] = S[3][i] - 1 / (R[i] - L[i]);
        }
        else
        {
            FOR(j,0,4)
            {
                S[j][i + 1] = S[j][i];
            }
        }
    }
    
    int ptr = 0;
    
    FOR(i,0,n)
    {
        while (ptr < n && R[ptr] < L[i]) ++ ptr;
        
        if (R[i] == L[i]) continue;
        
        double a3 = S[3][i] - S[3][ptr];
        double a2 = S[2][i] - S[2][ptr];
        double a1 = S[1][i] - S[1][ptr];
        double a0 = S[0][i] - S[0][ptr];
        
        res += 1. / (3 * (R[i] - L[i])) * (a3 * L[i] * L[i] * L[i] + a2 * L[i] * L[i] + a1 * L[i] + a0);
        
    }
    
    
    
    res /= 1.0 * n * n;
    
    printf("%.10f\n" , (double)res);
    
    
    return 0;
}




