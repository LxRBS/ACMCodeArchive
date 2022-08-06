#include <bits/stdc++.h>
using i64 = long long;
using pii = std::pair<int,int>;

namespace SegT {

int n;

struct Node {
    Node *l,*r;
    i64 val,lz;
    Node() : l(nullptr), r(nullptr), val(0), lz(0) {}
};

std::vector<Node> ns(100006 * 32);

void pull(Node *&p) {
    p->val = std::max(p->l == nullptr ? 0 : p->l->val, p->r == nullptr ? 0 : p->r->val);
}

void kill_lazy(Node *&t) {
    i64 &lazy = t->lz;

    Node *&ls = t->l, *&rs = t->r;
    if(ls == nullptr) ns[n] = Node(), ls = &ns[n], ++n;
    if(rs == nullptr) ns[n] = Node(), rs = &ns[n], ++n;

    ls->val += lazy;
    ls->lz += lazy;

    rs->val += lazy;
    rs->lz += lazy;

    lazy = 0;
}

i64 query(Node *t, int l, int r, int x) {
    if(t == nullptr) {
        return 0;
    }
    if(r - l == 1) {
        return t->val;
    }
    kill_lazy(t);
    int mid = l + r >> 1;
    if(x < mid) return query(t->l, l, mid, x);
    else return query(t->r, mid, r, x);
}

void add(Node *&t, int l, int r, int le, int ri, i64 v) {
    if(ri <= l || r <= le) {
        return;
    }
    if(t == nullptr) {
        ns[n] = Node(), t = &ns[n], ++n;
    }

    if(le <= l && r <= ri) {
        t->val += v;
        t->lz += v;
        return;
    }
    kill_lazy(t);
    int mid = l + r >> 1;
    add(t->l, l, mid, le, ri, v);
    add(t->r, mid, r, le, ri, v);
    pull(t);
}

}

void sol() {
    int n,Q;
    std::cin >> n >> Q;
    assert(3 <= n && n <= 1e8);
    assert(1 <= Q && Q <= 1e5);
    std::vector<i64> tag(Q + 1);
    std::map<int,int> att;
    SegT::ns[SegT::n] = SegT::Node();
    SegT::Node *t = &SegT::ns[SegT::n];
    ++SegT::n;
    att[0] = -2;
    att[1] = 0;
    att[n + 1] = -1;

    auto find = [&](int p) {
        return std::prev(att.upper_bound(p));
    };
    auto split = [&](int p) {
        auto it = find(p);
        att[p] = it->second;
    };

    int lastans = 0, n2 = (n - 1) / 2;
    for(int q = 1; q <= Q; ++q) {
        int op;
        std::cin >> op;
        assert(1 <= op && op <= 4);
        if(op == 1) {
            int x,c;
            std::cin >> x >> c;
            assert(1 <= x && x <= n);
            assert(1 <= c && c <= n2);
            x = (x - 1 ^ lastans) % n + 1;
            c = (c - 1 ^ lastans) % n2 + 1;
            int l = std::max(1, x - c), r = l + 2 * c;
            // [l, r]
            if(r > n) {
                l = n - 2 * c;
                r = n;
            }
            ++r;
            // [l,r)

            split(l); split(r);
            auto it = att.find(l);
            while(it->first != r) {
                SegT::add(t, 1, n + 1, it->first, std::next(it)->first, tag[it->second] - tag[q]);
                it = att.erase(it);
            }
            att[l] = q;
        }else if(op == 2) {
            int x,y;
            std::cin >> x >> y;
            assert(1 <= x && x <= n);
            assert(1 <= y && y <= n);
            x = (x - 1 ^ lastans) % n + 1;
            y = (y - 1 ^ lastans) % n + 1;
            auto it = find(x), jt = find(y);
            int attx = it->second;
            if(attx != jt->second) {
                SegT::add(t, 1, n + 1, jt->first, std::next(jt)->first, tag[jt->second] - tag[attx]);
                jt->second = attx;
                while(jt->second == std::next(jt)->second) att.erase(std::next(jt));
                auto kt = std::prev(jt);
                while(jt->second == kt->second) {
                    att.erase(jt);
                    jt = kt;
                    kt = std::prev(jt);
                }
            }
        }else if(op == 3) {
            int x;
            i64 v;
            std::cin >> x >> v;
            assert(1 <= x && x <= n);
            assert(1 <= v && v <= 1e9);
            x = (x - 1 ^ lastans) % n + 1;
            auto it = find(x);
            tag[it->second] += v;
        }else {
            int x;
            std::cin >> x;
            x = (x - 1 ^ lastans) % n + 1;
            assert(1 <= x && x <= n);
            auto it = find(x);
            i64 ans = SegT::query(t,1,n+1,x) + tag[it->second];
            std::cout << ans << '\n';
            lastans = ans & 1073741823;
        }
    }
}

int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while(t --> 0) {
        SegT::n = 0;
        sol();
    }

    return 0;
}