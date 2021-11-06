#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <random>
#include <iomanip>
#include <cmath>
#include <queue>
using namespace std;
 
vector<int> kek(int x, vector<int> blocks, vector<int> gaps) {
    vector<int> ans;
     
    auto processGap = [&](int gap) -> void {
        //cout << "gap " << gap << " " << x << "\n";
        if (gap == x + 1) return;
        gap -= x + 1;
        if (gap % 2 == 1) { ans.push_back(2); gap -= 2; }
        for (int i = 0; i < gap / 2; i++) ans.push_back(1);
    };
     
    for (int i = 0; i < (int)blocks.size(); i++) {
        processGap(gaps[i]);
        ans.push_back(blocks[i] + x);
    }
    processGap(gaps.back());
     
    return ans;
}
 
void solve() {
    string s;
    cin >> s;
    vector<int> gaps, blocks;
    int len = 0;
    char lst = '_';
    for (char ch : s) {
        if (ch == lst) len++;
        else {
            if (lst == '_') gaps.push_back(len);
            else blocks.push_back(len);
            len = 1;
            lst = ch;
        }
    }
    if (lst == '_') gaps.push_back(len);
    if (lst == '#') { blocks.push_back(len); gaps.push_back(0); }
     
    if (blocks.empty()) {
        if ((int)s.length() == 1) { cout << "0\n\n"; return; }
        else { cout << "1\n1\n"; return; }
    }
     
    gaps[0]++;
    gaps.back()++;
     
    bool isOdd = false, is4 = false, is5 = false;
    int minGap = 100500;
    int maxGap = 0;
    for (int gap : gaps) {
        if (gap % 2 == 1) isOdd = true;
        if (gap == 4) is4 = true;
        if (gap == 5) is5 = true;
        minGap = min(minGap, gap);
        maxGap = max(maxGap, gap);
    }

    std::cerr << "isOdd: " << isOdd << '\n';
    std::cerr << "is4: " << is4 << '\n';
    std::cerr << "is5: " << is5 << '\n';
    std::cerr << "minGap: " << minGap << '\n';
    std::cerr << "maxGap: " << minGap << '\n';

    vector<int> ans;
     
    if (maxGap == 1) {
        cout << blocks.size() << "\n";
        for (int x : blocks) cout << x << " ";
        cout << "\n";
        return;
    } else if (!isOdd) {
        for (int i = 0; i < (int)blocks.size(); i++) {
            for (int j = 0; j < gaps[i] / 2 - 1; j++)
                ans.push_back(1);
            ans.push_back(blocks[i] + 1);
        }
        for (int j = 0; j < gaps.back() / 2 - 1; j++)
            ans.push_back(1);
    } else if (minGap >= 3 && !is4) {
        ans = kek(2, blocks, gaps);
    } else if (minGap >= 4 && !is5) {
        ans = kek(3, blocks, gaps);
    } else {
        cout << "-1\n";
        return;
    }
         
         
    cout << ans.size() << "\n";
    for (int x : ans) {
        cout << x << " ";
    }
    cout << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
#ifdef SERT
    t += 2;
    freopen("/Users/sert/code/timus/tests.txt", "r", stdin);
#endif
    while (t--) solve();
}