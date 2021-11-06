#include "jngen.h"
//#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void error(string s) {
    cerr << s << endl;
    exit(1);
};

struct Test {
    int n, k;
    vector<pair<int, int>> ed;
    vector<int> a;

    Test() {
        n = k = 0;
    }

    Test shuffled() {
        auto t = *this;
        vector<int> p(t.n);
        iota(p.begin(), p.end(), 0);
        shuffle(p.begin(), p.end());
        for (auto &e : t.ed) {
            e.first = p[e.first];
            e.second = p[e.second];
            if (rnd.next(2) == 0) {
                swap(e.first, e.second);
            }
        }
        for (int i = 0; i < n; i++) {
            t.a[p[i]] = a[i];
        }
        shuffle(t.ed.begin(), t.ed.end());
        return t;
    }

    void print() {
        cout << n << " " << k << endl;
        for (int i = 0; i < n; i++) cout << a[i] + 1 << " \n"[i + 1 == n];
        for (auto e : ed) {
            cout << e.first + 1 << " " << e.second + 1 << endl;
        }
    }
};

ll strtoll(string s) {
    if (s == "") return 0;
    stringstream ss;
    ll x;
    ss << s;
    ss >> x;
    return x;
}

double strtodbl(string s) {
    if (s == "") return 0;
    stringstream ss;
    double x;
    ss << s;
    ss >> x;
    return x;
}

map<string, function<Test(map<string, string>)>> genTree;
void initTree() {
    genTree["random"] = [&](map<string, string> arg) {
        Test t = Test();
        t.n = strtoll(arg["n"]);
        int w = strtoll(arg["w"]);
        for (int i = 1; i < t.n; i++) {
            t.ed.push_back({i, rnd.wnext(i, w)});
        }
        return t;
    };
    genTree["bamboo"] = [&](map<string, string> arg) {
        Test t = Test();
        t.n = strtoll(arg["n"]);
        for (int i = 1; i < t.n; i++) {
            t.ed.push_back({i, i - 1});
        }
        return t;
    };
    genTree["LStar"] = [&](map<string, string> arg) {
        Test t = Test();
        t.n = strtoll(arg["n"]);
        int l = strtoll(arg["l"]);
        for (int i = 1; i < t.n; i++) {
            int u = i;
            int v = i % l == 0 ? i - 1 : 0;
            t.ed.push_back({u, v});
        }
        return t;
    };
    genTree["JNGen"] = [&](map<string, string> arg) {
        Test t = Test();
        int n = strtoll(arg["n"]);
        int f = strtoll(arg["many-leafs"]);
        Tree tr;
        string subtype = arg["subtype"];
        if (f) n /= 2;
        if (subtype == "random") {
            tr = Tree::random(n);
        } else if (subtype == "randomPrim") {
            tr = Tree::randomPrim(n);
        } else if (subtype == "randomKruskal") {
            tr = Tree::randomKruskal(n);
        } else if (subtype == "caterpillar") {
            tr = Tree::caterpillar(n, strtoll(arg["len"]));
        } else if (subtype == "binary") {
            tr = Tree::binary(n);
        } else if (subtype == "kary") {
            tr = Tree::kary(n, strtoll(arg["kary"]));
        } else assert(0);
        if (f) n *= 2;
        t.n = n;
        for (auto ed : tr.edges()) {
            t.ed.push_back(ed);
        }
        if (f) {
            for (int i = n / 2; i < n; i++) {
                int u = rnd.next(n / 2);
                int v = i;
                t.ed.push_back({u, v});
            }
        }
        return t;
    };
}

map<string, function<Test(map<string, string>, Test)>> colorTree;
void initColorings() {
    colorTree["random"] = [&](map<string, string> arg, Test t) {
        t.k = strtoll(arg["k"]);
        t.a.resize(t.n);
        int mask = strtoll(arg["mask"]);
        if (!mask) mask = (1 << t.k) - 1;
        for (int i = 0; i < t.n; i++) {
            do {
                t.a[i] = rnd.next(t.k);
            } while (!(mask & (1 << t.a[i])));
        }
        return t;
    };
    colorTree["exp"] = [&](map<string, string> arg, Test t) {
        t.k = strtoll(arg["k"]);
        t.a.resize(t.n);
        double p = strtodbl(arg["p"]);
        for (int i = 0; i < t.n; i++) {
            for (int j = 0; j < t.k; j++) {
                if (j == t.k - 1 || rnd.next(1.0) < p) {
                    t.a[i] = j;
                    break;
                }
            }
        }
        return t;
    };
    colorTree["thue-morse"] = [&](map<string, string> arg, Test t) {
        t.k = strtoll(arg["k"]);
        t.a.resize(t.n);
        for (int i = 0; i < t.n; i++) {
            t.a[i] = __builtin_popcount(i) % t.k;
        }
        return t;
    };
};


int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    initTree();
    initColorings();

    map<string, string> args;
    for (int i = 1; i < argc; i++) {
        string cur = argv[i];
        int j = cur.find('=');
        if (j != -1) {
            string left = cur.substr(0, j);
            string right = cur.substr(j + 1);
            args[left] = right;
        }
    }
    string tp = args["type"];
    string colorMode = args["coloring"];
    if (colorMode == "") colorMode = "default";

    if (genTree.count(tp) && colorTree.count(colorMode)) {
        auto tree = genTree[tp](args);
        if (tree.k == 0 && colorMode == "default") {
            colorMode = "random";
        }
        if (colorMode != "default") {
            tree = colorTree[colorMode](args, tree);
        }
        if (args["shuffle"] != "false") {
            tree = tree.shuffled();
        }
        tree.print();
    }
    else {
        error(format("<type>=%s or <coloring>=%s were not expected", tp, colorMode));
    }

    return 0;
}
