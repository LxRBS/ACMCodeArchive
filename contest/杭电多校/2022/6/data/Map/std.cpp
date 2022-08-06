#include<bits/stdc++.h>
using namespace std;

#define int long long

int X[4], Y[4];
int x[4], y[4];

int cross(int a1, int a2, int a3, int a4) {
  return a1 * a4 - a2 * a3;
}

signed main() {
  #ifdef Sakuyalove
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
  #endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    for (int i = 0; i < 4; i++) cin >> X[i] >> Y[i];
    for (int i = 0; i < 4; i++) cin >> x[i] >> y[i];
    int Ux = X[3] - X[0], Uy = Y[3] - Y[0];
    int Vx = X[1] - X[0], Vy = Y[1] - Y[0];
    int ux = x[3] - x[0], uy = y[3] - y[0];
    int vx = x[1] - x[0], vy = y[1] - y[0];
    double p = cross(X[0] - x[0], vx - Vx, Y[0] - y[0], vy - Vy) / (double)cross(ux - Ux, vx - Vx, uy - Uy, vy - Vy);
    double q = cross(ux - Ux, X[0] - x[0], uy - Uy, Y[0] - y[0]) / (double)cross(ux - Ux, vx - Vx, uy - Uy, vy - Vy);
    cout << fixed << setprecision(6) << x[0] + p * ux + q * vx << ' ' << y[0] + p * uy + q * vy << endl; 
  } 
  return 0;
}