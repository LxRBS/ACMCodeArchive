#include <iostream>
#include <set>
#include <utility>
#include <vector>
#define ll long long
using namespace std;

const int MAXN = 751;
const int MAXM = 1251;

// notation: i=number of red tracks covered, j=number of blue tracks covered
ll n, m, k1, k2;
vector < pair < ll, pair < long long, ll > > > adj[MAXM]; // adj[u] ~ (v, (x, c))
ll s, t;
set < pair < ll, ll > > vis[MAXN]; // vis[i] ~ (i,j)
set < pair < long long, pair < ll, pair < ll, ll > > > > nb_set; // nb_set ~ (time, (node, (i, j)))
long long ans = -1;

void input() {
    cin >> n >> m >> k1 >> k2;
    ll u, v, c;
    long long x;
    for(ll i=0; i<m; i++) {
        cin >> u >> v >> x >> c;
        u -= 1;
        v -= 1;
        adj[u].push_back(make_pair(v, make_pair(x, c)));
        adj[v].push_back(make_pair(u, make_pair(x, c)));
    }
    cin >> s >> t;
    s -= 1;
    t -= 1;
    // cout << "input done\n";
}

void populateFirstNode() {
    nb_set.insert(make_pair(0, make_pair(s, make_pair(0, 0))));
    // cout << 0 << ", " << s+1 << ", " << 0 << ", " << 0 << "\n";
    if(s == t && k1 == 0 && k2 == 0) {
        ans = 0;
    }
}

void exploreNextBestNode() {
    // cout << "";
    // for(set < pair < long long, pair < ll, pair < ll, ll > > > > :: iterator itr = nb_set.begin(); itr != nb_set.end(); itr++) {
    //     cout << "(" << itr->first << ", " << itr->second.first+1 << ", " << itr->second.second.first << ", " << itr->second.second.second << "), ";
    // }
    // cout << " : ";
    pair < long long, pair < ll, pair < ll, ll > > > bestNode = *nb_set.begin();
    nb_set.erase(nb_set.begin());
    if((vis[bestNode.second.first].find(make_pair(bestNode.second.second.first, bestNode.second.second.second))) != vis[bestNode.second.first].end()) {
        return;
    }
    vis[bestNode.second.first].insert(make_pair(bestNode.second.second.first, bestNode.second.second.second));
    // cout << "bestNode: (" << bestNode.first << ", " << bestNode.second.first+1 << ", "
    //      << bestNode.second.second.first << ", " << bestNode.second.second.second << ")\n";
    // cout << bestNode.first << ", " << bestNode.second.first+1 << ", " << bestNode.second.second.first << ", "
    //      << bestNode.second.second.second << "\n";
    ll nextIndex = bestNode.second.first;
    for(vector < pair < ll, pair < long long, ll > > > :: iterator itr = adj[nextIndex].begin(); itr != adj[nextIndex].end(); itr++) {
        pair < ll, pair < long long, ll > > nb = *itr;
        ll red = bestNode.second.second.first, blue = bestNode.second.second.second;
        if(nb.second.second == 1) {
            red+=1;
        }
        if(nb.second.second == 2) {
            blue+=1;
        }
        if((vis[nb.first].find(make_pair(red, blue)) == vis[nb.first].end()) && (red <= k1 && blue <= k2)) { // not visited
            nb_set.insert(make_pair(bestNode.first+nb.second.first, make_pair(nb.first,make_pair(red, blue))));
            // cout << "    " <<(bestNode.first+nb.second.first) << ", " << nb.first+1 << ", " << red << ", " << blue << "\n";
            if(nb.first == t && k1 == red && k2 == blue) {
                ans = (bestNode.first+nb.second.first);
                break;
            }
        }
    }
}

int main() {
    input();
    populateFirstNode();
    while(nb_set.size() > 0 && ans == -1) {
        exploreNextBestNode();
    }
    cout << ans << endl;
}
