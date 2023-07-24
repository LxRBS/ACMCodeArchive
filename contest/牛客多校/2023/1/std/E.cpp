#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Data {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> q;
    double C = 0;
};
const double inf = 1e18;

int main() {
    int n;
    cin >> n;
    vector<double> a(n + 1);
    vector<vector<int>> G(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    function<Data(int, int)> dfs = [&](int u, int r) -> Data {
        Data ret;
        ret.C = 0;
        for (auto v: G[u]) {
            if (v == r) continue;
            auto cur = dfs(v, u);
            // 启发式合并拐点
            if (ret.q.size() < cur.q.size()) swap(ret, cur);
            while (!cur.q.empty()) {
                ret.q.push(cur.q.top());
                cur.q.pop();
            }
            ret.C += cur.C;
        }
        double x = -inf, y = 0, sum = 0;
        int slope = 0;
        while (true) {
            double x2 = ret.q.empty() ? inf : ret.q.top().first;
            double y2 = y + slope * (x2 - x);
            // 找到极小值点的位置nx
            if (x2 + y2 >= a[u]) {
                double nx = (a[u] + slope * x - y) / (slope + 1);
                ret.q.emplace(nx, slope + 1);
                ret.C += sum + (y * 2 + slope * (nx - x)) * (nx - x) + pow(nx - a[u], 2);
                break;
            }
            // 否则删去左侧的拐点
            sum += (y + y2) * (x2 - x);
            slope += ret.q.top().second, x = x2, y = y2;
            ret.q.pop();
        }
        return ret;
    };

    printf("%.9lf\n", dfs(1, 1).C);
    return 0;
}
