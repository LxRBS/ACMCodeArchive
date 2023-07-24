#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> bubble(int n) {
    vector<pair<int, int>> ret;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ret.emplace_back(i, j);
        }
    }
    return ret;
}

void wk() {
    int n;
    string a;
    cin >> n >> a;
    vector<pair<int, int>> ans;

    // 第一部分：移动其他的01
    vector<int> p0, p1;
    for (int i = 1; i <= n; ++i) (a[i - 1] == '1' ? p1 : p0).push_back(i);
    reverse(p1.begin(), p1.end());
    int l = p1.back(), r = p0.back();

    for (auto x: p0) if (x != r) ans.emplace_back(x, r);
    for (auto x: p1) if (x != l) ans.emplace_back(x, l);

    // 第二部分：正常排序其他元素
    vector<int> id;
    for (int i = 1; i <= n; ++i) if (i != l && i != r) id.push_back(i);
    for (auto[x, y]: bubble(n - 2)) {
        ans.emplace_back(id[x], id[y]);
    }

    // 第三部分：校准
    int b = (int) p0.size();
    for (int i = b; i > l; --i) ans.emplace_back(l, i);
    for (int i = 1; i < l; ++i) ans.emplace_back(l, i);
    for (int i = b + 1; i < r; ++i) ans.emplace_back(i, r);
    for (int i = n; i > r; --i) ans.emplace_back(i, r);

    printf("%d\n", (int) ans.size());
    for (auto &[x, y]: ans) {
        if (x > y) swap(x, y);
        printf("%d %d\n", x, y);
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) wk();
    return 0;
}
