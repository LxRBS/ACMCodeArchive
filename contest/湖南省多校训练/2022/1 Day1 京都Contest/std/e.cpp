#include <bits/stdc++.h>

using namespace std;


// skew heap
struct Heap {
private:
    struct Node {
        unique_ptr<Node> l, r;
        int val;
        Node(int _val) : val(_val) {}
    };

    unique_ptr<Node>& meld(unique_ptr<Node>& s, unique_ptr<Node>& t) {
        if (!s) return t;
        if (!t) return s;

        if (s->val > t->val) s.swap(t);
        s->r = move(meld(s->r, t));
        s->l.swap(s->r);

        return s;
    }

    unique_ptr<Node> root;

public:
    Heap() : root(nullptr) {}

    void push(int x) {
        unique_ptr<Node> p(new Node(x));
        root = move(meld(root, p));
    }

    void pop() {
        root = move(meld(root->r, root->l));
    }

    int top() {
        if(!root) return -1;
        else return root->val;
    }

    void meld(Heap &r) {
        root = move(meld(root, r.root));
    }
};


vector<Heap> qs;
vector<vector<pair<int, int>>> tree;
vector<int> id;

void dfs(int x, int e = -1){
    for (auto nxp : tree[x]) {
        if (nxp.second == e) continue;
        dfs(nxp.first, nxp.second);
        qs[x].meld(qs[nxp.first]);
    }
    while(qs[x].top() != -1) {
        int m = qs[x].top();
        qs[x].pop();
        if(qs[x].top() == m){
            qs[x].pop();
        } else {
            qs[x].push(m);
            break;
        }
    }
    if (e != -1) {
        id[e] = qs[x].top();
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    qs = vector<Heap>(m);
    tree = vector<vector<pair<int, int>>>(n);
    id = vector<int>(m, -1);
    vector<int> u(m), v(m), c(m);

    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> c[i];
        u[i]--, v[i]--;
        if(c[i]){
            tree[u[i]].emplace_back(v[i], i);
            tree[v[i]].emplace_back(u[i], i);
        } else {
            qs[u[i]].push(i);
            qs[v[i]].push(i);
        }
    }

    dfs(0);

    vector<vector<int>> mem(m);
    for (int i = 0; i < m; i++) {
        if(id[i] != -1) {
            if(id[i] < i) {
                mem[id[i]].push_back(i);
            }
        }
    }

    int now = 1;
    vector<int> ans(m, -1);
    for (int i = 0; i < m; i++) {
        if (ans[i] == -1) {
            for (auto x : mem[i]) {
                ans[x] = now++;
            }
            ans[i] = now++;
        }
        
        cout << ans[i];
        if (i < m - 1) cout << " ";
        else cout << endl;
    }

    return 0;
}
