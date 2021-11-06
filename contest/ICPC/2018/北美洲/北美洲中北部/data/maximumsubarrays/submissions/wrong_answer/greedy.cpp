#include <bits/stdc++.h>

#define ll long long

using namespace std;

struct SubArray {
    ll sum;
    int start, end;

    SubArray(ll sum, int start, int end) : sum(sum), start(start), end(end) {}
};

int main() {
    int n, k;
    cin >> n >> k;

    vector<ll> a(n + 1, 0), cummulative(n + 1, 0);;
    vector<int> negatives(n + 1, 0);


    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cummulative[i] += cummulative[i - 1] + a[i];
    }

    auto comp = [](const SubArray &x, const SubArray &y) { return x.sum < y.sum; };
    priority_queue<SubArray, vector<SubArray>, decltype(comp)> pq(comp);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            pq.emplace(cummulative[j] - cummulative[i - 1], i, j);
        }
    }
    int totalUsed = 0, disjoint = 0;
    ll ans = 0;

    vector<bool> used(n + 1, false);

    while (disjoint < k && !pq.empty()) {
        const auto cur = pq.top();
        pq.pop();
        if (cur.sum < 0 && totalUsed >= k) {
            break;
        }
        bool valid = true;
        for (int i = cur.start; i <= cur.end; ++i) {
            if (used[i]) {
                valid = false;
            }
        }
        if (valid) {
            ans += cur.sum;
//            cerr << cur.sum << ' ' << cur.start << ' ' << cur.end << '\n';
            ++disjoint;
            totalUsed += cur.end - cur.start + 1;
            for (int i = cur.start; i <= cur.end; ++i) {
                used[i] = true;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}