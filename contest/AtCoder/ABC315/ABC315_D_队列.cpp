/**
 * 给定一个矩阵，作如下操作：
 * 1. 看每一行是否数量大于等于1个，且字母全相同
 * 2. 看每一列是否数量大于等于1个，且字母全相同
 * 3. 如果没有满足条件的1和2，则退出；否则将满足条件的行列全删除，循环
 * 首先记录每一行每一列字母的数量，然后将只有单一字母的行列入队
 * 当队列不为空时：
 *    取出头结点，假设头结点对应的是行，字母是ch
 *    将剩余每一列的对应ch数量减一，如果减到0，再看该列还剩几个字母，如果只剩一个字母则入队
 * 出循环后，统计一下即可
 * 队列最多有(H+W)个元素，对每一个元素需要对每一列减一，假设H和W同阶，复杂度为
 * O(2H^2log(26))
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

int H, W;
vector<string> A;

int proc(){
    vector<pair<int, map<char, int>>> rmap(H), cmap(W);
    for(int i=0;i<H;++i){
        rmap[i].first = i;
        for(int j=0;j<W;++j){
            ++rmap[i].second[A[i][j]];
        }
    }
    for(int i=0;i<W;++i){
        cmap[i].first = i;
        for(int j=0;j<H;++j){
            ++cmap[i].second[A[j][i]];
        }
    }

    set<pair<char, int>> flag;
    queue<pair<char, int>> q;
    for(auto i=rmap.begin(),e=rmap.end();i!=e;++i){
        if(i->second.size() == 1){
            q.push({'r', i->first});
            flag.insert({'r', i->first});
        }
    }
    for(auto i=cmap.begin(),e=cmap.end();i!=e;++i){
        if(i->second.size() == 1){
            q.push({'c', i->first});
            flag.insert({'c', i->first});
        }
    }

    while(1){
        auto sz = q.size();
        if(0 == sz) break;
        while(sz--){
            auto h = q.front(); q.pop();
            vector<pair<int, map<char, int>>> * vec = nullptr;
            pair<int, map<char, int>> * p = nullptr;
            if(h.first == 'r') p = &rmap[h.second], vec = &cmap;
            else if(h.first == 'c') p = &cmap[h.second], vec = &rmap;
            else assert(0);

            if(p->second.empty()) continue;
            auto ch = p->second.begin()->first;
            p->second.clear();

            for(auto & [idx, m] : *vec){
                auto tt = flag.find({'r' ^ 'c' ^ h.first, idx});
                if(tt != flag.end()) continue;

                auto it = m.find(ch);
                if(it != m.end()){
                    if(0 == --it->second){
                        m.erase(it);
                        if(1 == m.size() and m.begin()->second >= 2){
                            q.push({'r' ^ 'c' ^ h.first, idx});
                            flag.insert({'r' ^ 'c' ^ h.first, idx});
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for(const auto & [_, m] : rmap){
        for(const auto & p : m){
            ans += p.second;
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> H >> W;
    A.assign(H, "");
    for(auto & s : A) cin >> s;
    cout << proc() << endl;
    return 0;
}
