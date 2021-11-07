#include <bits/stdc++.h>
#include "testlib.h"

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

const int N = 305, K = 3e5 + 5;

int tms, cnt[K], vis[N][N];
bool wa, v[4][N][N];
std::vector<std::pair<int, int>> va[K], vb[K];

void dfs(int i, int j, int ban) {
    if (vis[i][j] == tms) { wa = true; return; }
    vis[i][j] = tms;
    for (int d = 0; d < 4; d++) {
        if (d == ban || !v[d][i][j]) { continue; }
        dfs(i + dx[d], j + dy[d], d ^ 1);
    }
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    
    int T = inf.readInt(1, 100, "T");
    for (int t = 1; t <= T; t++) {
        int n = inf.readInt(1, 300, "n");
        int k = inf.readInt(1, 2 * (n + 1) * n, "k");
        bool ansable = true;
        if (n == 1 || k == 1 || 2 * (n + 1) * n % k != 0) { ansable = false; }
        if (!ansable) {
            ouf.readInt(-1, -1, "no solution");
        } else {
            for (int x = 1; x <= k; x++) {
                va[x].clear(); vb[x].clear();
                cnt[x] = 0;
            }
            for (int i = 0; i <= n; i++) {
                int min = 1e9, max = -1e9;
                for (int j = 0; j < n; j++) {
                    int a = ouf.readInt(1, k, "a");
                    va[a].push_back({i, j});
                    cnt[a]++;
                    min = std::min(min, a);
                    max = std::max(max, a);
                }
                ensuref(min != max, "some horizontal line only contains one color");
            }
            for (int j = 0; j <= n; j++) {
                int min = 1e9, max = -1e9;
                for (int i = 0; i < n; i++) {
                    int b = ouf.readInt(1, k, "b");
                    vb[b].push_back({i, j});
                    cnt[b]++;
                    min = std::min(min, b);
                    max = std::max(max, b);
                }
                ensuref(min != max, "some vertical line only contains one color");
            }
            for (int x = 1; x <= k; x++) {
                if (cnt[x] != 2 * (n + 1) * n / k) {
                    quitf(_wa, "colors appear of different times on test %d", t);
                }
            }
            wa = false;
            for (int x = 1; x <= k; x++) {
                for (auto p : va[x]) {
                    int i = p.first, j = p.second;
                    v[0][i][j] = v[1][i][j + 1] = true;
                }
                for (auto p : vb[x]) {
                    int i = p.first, j = p.second;
                    v[2][i][j] = v[3][i + 1][j] = true;
                }
                tms++;
                for (auto p : va[x]) {
                    int i = p.first, j = p.second;
                    if (vis[i][j] != tms) {
                        dfs(i, j, 5);
                        if (wa) {
                            quitf(_wa, "cycle of the same color is found on test %d", t);
                        }
                    }
                }
                for (auto p : vb[x]) {
                    int i = p.first, j = p.second;
                    if (vis[i][j] != tms) {
                        dfs(i, j, 5);
                        if (wa) {
                            quitf(_wa, "cycle of the same color is found on test %d", t);
                        }
                    }
                }
                for (auto p : va[x]) {
                    int i = p.first, j = p.second;
                    v[0][i][j] = v[1][i][j + 1] = false;
                }
                for (auto p : vb[x]) {
                    int i = p.first, j = p.second;
                    v[2][i][j] = v[3][i + 1][j] = false;
                }
            }
        }
    }

    quitf(_ok, "answers exist");

    return 0;
}