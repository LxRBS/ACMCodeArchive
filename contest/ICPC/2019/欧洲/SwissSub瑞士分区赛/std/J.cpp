#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N;
vector< vector<int> > G;
vector<bool> visited;
vector< vector<int> > solution;
bool OK;

bool dfs(int v) {
    visited[v] = true;
    vector<int> unmatched_children;
    for (int x : G[v]) if (!visited[x]) if (!dfs(x)) unmatched_children.push_back(x);
    while (unmatched_children.size() >= 2u) {
        int a = unmatched_children.back();
        unmatched_children.pop_back();
        int b = unmatched_children.back();
        unmatched_children.pop_back();
        solution.push_back( {a,b,v} );
    }
    if (unmatched_children.empty()) return false;
    solution.push_back( {unmatched_children[0], v, -1} );
    return true;
}

int main() {
    cin >> N;
    G.resize(2*N);
    int F;
    cin >> F;
    while (F--) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    OK = true;
    visited.resize(2*N,false);
    for (int n=0; n<2*N; ++n) if (!visited[n]) if (!dfs(n)) OK = false;
    cout << (OK ? "POSSIBLE\n" : "IMPOSSIBLE\n");
    if (OK) for (auto row : solution) cout << row[0] << " " << row[1] << " " << row[2] << "\n";
}