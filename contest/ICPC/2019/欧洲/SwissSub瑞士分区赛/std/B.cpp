#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

int main() {
    int N;
    cin >> N;
    vector<int> S(N);
    for (int &s : S) cin >> s;

    vector<int> cycle_count(N+1,0);
    vector<bool> seen(N,false);

    for (int n=0; n<N; ++n) if (!seen[n]) {
        seen[n] = true;
        int clen = 1, where = n;
        while (true) {
            where = S[where];
            if (seen[where]) break;
            seen[where] = true;
            ++clen;
        }
        ++cycle_count[clen];
    }

    long long answer = 1;

    for (int len=1; len<=N; ++len) if (cycle_count[len]>0) {
        int cnt = cycle_count[len];
        vector<int> groups;
        if (len%2) groups = {1,2,4}; else groups = {4};
        vector<long long> dp(cnt+1,0);
        dp[0] = 1;
        for (int c=1; c<=cnt; ++c) {
            for (int g : groups) if (g <= c) {
                long long curr = 1;
                for (int j=0; j<g-1; ++j) curr = (curr * (c-1-j)) % MOD;
                for (int j=0; j<g-1; ++j) curr = (curr * len) % MOD;
                dp[c] = (dp[c] + curr * dp[c-g]) % MOD;
            }
        }
        answer = (answer * dp[cnt]) % MOD;
    }
    cout << answer << endl;
}