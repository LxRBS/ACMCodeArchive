#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200500;

int n;
double x, y;
string s;
const double eps = 1e-8;

long long square(int x1, int y1, int x2, int y2, int x3, int y3) {
    return abs((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3));
}

pair<long long, long long> center(int x1, int y1, int x2, int y2, int x3, int y3) {
    return make_pair(x1 + x2 + x3, y1 + y2 + y3);
}

void add_triangle(long long &sumx, long long &sumy, long long &sum, int x1, int y1, int x2, int y2, int x3, int y3) {
    long long s = square(x1, y1, x2, y2, x3, y3);
    auto p = center(x1, y1, x2, y2, x3, y3);
    sumx += s * p.first;
    sumy += s * p.second;
    sum += s;
}

void rec(int pos, int open, int close, long long sumx, long long sumy, long long sum) {
    if (pos == n) {
        double xx = sumx / (double)sum / 3.0;
        double yy = sumy / (double)sum / 3.0;
        //cout << sumx << " " << sumy << " " << sum << " " << xx << " " << yy << " " << s << endl;
        if (fabs(xx - x) + fabs(yy - y) < eps) {
            cout << s;
            exit(0);
        }
    }
    int balance = open - close;
    if (open < n / 2) {
        long long new_sumx = sumx;
        long long new_sumy = sumy;
        long long new_sum = sum;
        add_triangle(new_sumx, new_sumy, new_sum, pos, balance, pos + 1, balance + 1, pos + 1, balance);
        add_triangle(new_sumx, new_sumy, new_sum, pos, 0, pos, balance, pos + 1, 0);
        add_triangle(new_sumx, new_sumy, new_sum, pos, balance, pos + 1, balance, pos + 1, 0);
        s.push_back('(');
        rec(pos + 1, open + 1, close, new_sumx, new_sumy, new_sum);
        s.pop_back();
    }
    if (open > close) {
        long long new_sumx = sumx;
        long long new_sumy = sumy;
        long long new_sum = sum;
        add_triangle(new_sumx, new_sumy, new_sum, pos, balance, pos + 1, balance - 1, pos, balance - 1);
        add_triangle(new_sumx, new_sumy, new_sum, pos, 0, pos, balance - 1, pos + 1, 0);
        add_triangle(new_sumx, new_sumy, new_sum, pos, balance - 1, pos + 1, balance - 1, pos + 1, 0);
        s.push_back(')');
        rec(pos + 1, open, close + 1, new_sumx, new_sumy, new_sum);
        s.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    cin >> x >> y;
    rec(0, 0, 0, 0, 0, 0);
}

/**
   6 3.4 0.6
 */