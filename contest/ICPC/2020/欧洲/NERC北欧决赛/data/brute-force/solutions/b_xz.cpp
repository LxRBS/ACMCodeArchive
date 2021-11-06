#define NDEBUG
NDEBUG


#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <queue>
#include <random>


#define forn(t, i, n) for (t i = 0; i < (n); ++i)


using namespace std;

// TC_REMOVE_BEGIN
/// caide keep
bool __hack = std::ios::sync_with_stdio(false);
/// caide keep
auto __hack1 = cin.tie(nullptr);
// TC_REMOVE_END


// Section with adoption of array and vector algorithms.


namespace template_util {
    

    constexpr int bytecount(uint64_t x) {
        return x ? 1 + bytecount(x >> 8) : 0;
    }

    template<int N>
    struct bytetype {
        
    };

    
    /// caide keep
    template<uint64_t N>
    struct minimal_uint : bytetype<bytecount(N)> {
    };
}


template<class T>
T next(istream& in) {
    T ret;
    in >> ret;
    return ret;
}


#define dbg(...) ;


//TODO migrate iterators into iterator_utils
namespace graph_impl {

    template<class T, class G, T next(const G&, T)>
    struct GenListIterator {
        GenListIterator(const G& g_, T t_): g(g_), t(t_) {}

        T operator*() const {
            return t;
        }

        GenListIterator& operator++() {
            t = next(g, t);
            return *this;
        }

        
        bool operator!=(const GenListIterator& o) const {
            assert(&g == &o.g);
            return t != o.t;
        }
    private:
        const G& g;
        T t;
    };

    template<class T, class G, T next(const G&, T)>
    struct GenListIterable {
        GenListIterable(const G& g_, T from_, T to_): g(g_), from(from_), to(to_) {}

        GenListIterator<T, G, next> begin() {
            return {g, from};
        };

        GenListIterator<T, G, next> end() {
            return {g, to};
        };
    private:
        const G& g;
        T from, to;
    };

    template<class T>
    struct GenRangeIterator {
        explicit GenRangeIterator(int at_): at(at_) {}

        T operator*() const {
            return T{at};
        }

        GenRangeIterator& operator++() {
            at++;
            return *this;
        }

        
        bool operator!=(const GenRangeIterator& o) const {
            return at != o.at;
        }
    private:
        int at;
    };

    template<class T>
    struct GenRangeIterable {
        GenRangeIterable(int from_, int to_):  from(from_), to(to_) {}

        GenRangeIterator<T> begin() {
            return GenRangeIterator<T>{from};
        };

        GenRangeIterator<T> end() {
            return GenRangeIterator<T>{to};
        };
    private:
        int from, to;
    };

    template<class K, class V>
    struct GenMap {
        using Value = V;

        explicit GenMap(V v_ = V{}): v(v_) {
        }

        GenMap& reserve(int n) {
            impl_.reserve(n);
            return *this;
        }

        GenMap& clear() {
            impl_.clear();
            return *this;
        }

        V& operator()(K k) {
            if (impl_.size() <= k.id) {
                impl_.resize(k.id + 1, v);
            }
            return impl_[k.id];
        }

        const V& operator()(K k) const {
            if (impl_.size() <= k.id) {
                return v;
            }
            return impl_[k.id];
        }
        vector<V> impl_;
    private:
        V v;
    };


    struct NodeT {
        int firstOut = -1;
        int degree = 0;
    };

    struct ArcT {
        int to, nextOut;
    };
}

struct Graph {
    struct Node {
        int id;
        explicit Node(int id_ = -1): id(id_) {}
        bool operator==(const Node o) const {return id == o.id;}
        bool operator!=(const Node o) const {return id != o.id;}
        

    };

    struct Arc {
        int id;
        explicit Arc(int id_ = -1): id(id_) {}
        bool operator==(const Arc o) const {return id == o.id;}
        bool operator!=(const Arc o) const {return id != o.id;}

        
    };

    struct Edge {
        int id;
        explicit Edge(int id_ = -1): id(id_) {}
        
        
        template<class C>
        Edge& withUV(C& c, typename C::Value v) {
            c(Arc{2 * id}) = v;
            return *this;
        };

        
    };

    template<class V>
    using NodeMap = graph_impl::GenMap<Node, V>;

    template<class V>
    using ArcMap = graph_impl::GenMap<Arc, V>;

    
    Node addNode() {
        int n = (int)nodes_.size();
        nodes_.push_back({});
        return Node{n};
    }

    vector<Node> addNodes(int count) {
        vector<Node> ret(count);
        forn (int, i, count) {
            ret[i] = addNode();
        }
        return ret;
    }

    Edge addEdge(Node u, Node v) {
        assert(valid(u));
        assert(valid(v));
        int n = (int)arcs_.size();
        arcs_.push_back({});
        arcs_[n].to = v.id;
        arcs_[n].nextOut = nodes_[u.id].firstOut;
        nodes_[u.id].firstOut = n;
        arcs_.push_back({});
        arcs_[n + 1].to = u.id;
        arcs_[n + 1].nextOut = nodes_[v.id].firstOut;
        nodes_[v.id].firstOut = n + 1;
        nodes_[u.id].degree++;
        nodes_[v.id].degree++;
        return Edge{n >> 1};
    }

    Edge toEdge(Arc a) const {
        assert(valid(a));
        return Edge{a.id >> 1};
    }

    Arc uv(Edge e) const {
        assert(valid(e));
        return Arc{e.id << 1};
    }

    Arc vu(Edge e) const {
        assert(valid(e));
        return dual(Arc{e.id << 1});
    }

    
    int nodesCount() const {
        return (int)nodes_.size();
    }

    
    Arc dual(Arc a) const {
        if (a.id == -1) {
            return a;
        }
        assert(valid(a));
        return Arc{a.id ^ 1};
    }

    
    Arc firstOutArc(Node a) const {
        assert(valid(a));
        return Arc{nodes_[a.id].firstOut};
    }

    
    Arc nextOutArc(Arc a) const {
        assert(valid(a));
        return Arc{arcs_[a.id].nextOut};
    }

    
    Node to(Arc a) const {
        assert(valid(a));
        return Node{arcs_[a.id].to};
    }

    
private:

    
    static Arc nextOutArc_(const Graph& g, Arc a) {
        return g.nextOutArc(a);
    }

public:

    
    graph_impl::GenListIterable<Arc, Graph, &Graph::nextOutArc_> outArcs(Node a) const {
        assert(valid(a));
        return graph_impl::GenListIterable<Arc, Graph, &Graph::nextOutArc_>(*this, firstOutArc(a), Arc{});
    }

    graph_impl::GenRangeIterable<Node> nodes() const {
        return graph_impl::GenRangeIterable<Node>(0, nodesCount());
    }

    
private:
    vector<graph_impl::NodeT> nodes_;
    vector<graph_impl::ArcT> arcs_;
};


template<class Cap = int32_t, class Cost = int32_t, class ResultFlow = int64_t, class ResultCost = int64_t>
struct MinCost {
  using Node = Graph::Node;
  using Arc = Graph::Arc;
  

  MinCost(
      const Graph& g_,
      const Graph::ArcMap<Cap>& cap_,
      const Graph::ArcMap<Cost>& cost_) : g(g_), cap(cap_), cost(cost_) {
    resultFlow = 0;
    resultCost = 0;
  }

  bool spfa(Node s, Node t) {
    dst.clear();
    dst.reserve(g.nodesCount());
    for (auto node : g.nodes()) dst(node) = numeric_limits<ResultCost>::max() / 2;
    visited.clear();
    visited.reserve(g.nodesCount());

    dst(s) = 0;
    curflow(s) = numeric_limits<ResultFlow>::max() / 2;
    queue<Node> que;
    que.push(s);
    while (!que.empty()) {
      Node u = que.front();
      que.pop();
      visited(u) = false;
      for (auto a : g.outArcs(u)) {
        auto to = g.to(a);
        if (cap(a) == flow(a) || dst(to) <= dst(u) + cost(a)) {
          continue;
        }
        dst(to) = dst(u) + cost(a);
        prevnode(to) = u;
        prevedge(to) = a;
        curflow(to) = min((ResultFlow)cap(a) - flow(a), curflow(u));
        if (!visited(to)) {
          visited(to) = true;
          que.push(to);
        }
      }
    }
    return dst(t) != numeric_limits<ResultCost>::max() / 2;
  }

  void run(Node s, Node t) {
    while (spfa(s, t)) {
      auto u = t;
      resultFlow += curflow(t);
      while (u != s) {
        auto a = prevedge(u);
        auto p = prevnode(u);
        resultCost += curflow(t) * cost(a);
        flow(a) += curflow(t);
        auto e = g.toEdge(a);
        auto ra = g.uv(e) == a ? g.vu(e) : g.uv(e);
        flow(ra) -= curflow(t);
        u = p;
      }
    }
  }

  // outputs
  ResultCost resultCost;
  ResultFlow resultFlow;
  Graph::ArcMap<Cap> flow;

// private:
  // inputs
  const Graph& g;
  const Graph::ArcMap<Cap>& cap;
  const Graph::ArcMap<Cost>& cost;

  // temp
  Graph::NodeMap<ResultCost> dst;
  Graph::NodeMap<int> visited;

  Graph::NodeMap<ResultFlow> curflow;
  Graph::NodeMap<Node> prevnode;
  Graph::NodeMap<Arc> prevedge;
};


const int inf = 1000000;

void solveFast(int n, vector<uint8_t> needed, std::ostream& out) {
    Graph g;
    Graph::Node s = g.addNode(), t = g.addNode();
    auto vIn = g.addNodes(1 << n);
    auto vOut = g.addNodes(1 << n);
    Graph::ArcMap<int> cap, cost, label(-2);
    forn (int, i, 1 << n) {
        g.addEdge(vIn[i], vOut[i]).withUV(cap, inf);
        if (needed[i]) {
            g.addEdge(s, vOut[i]).withUV(cap, 1);
            g.addEdge(vOut[i], t).withUV(cap, 1).withUV(cost, __builtin_popcount(i) + 1).withUV(label, -1);
            g.addEdge(vIn[i], t).withUV(cap, 1).withUV(label, i);
        }
        forn (int, bit, n) {
            if ((i & (1 << bit)) == 0) {
                g.addEdge(vOut[i], vIn[i | (1 << bit)]).withUV(cap, inf);
            }
        }
    }
    MinCost<> mcmf(g, cap, cost);
    mcmf.run(s, t);
    out << mcmf.resultCost - 1 << "\n";
    auto f = mcmf.flow;
    // dbg(s, t, vIn, vOut);
    // for (auto a : g.arcs()) {
    //     if (f(a) > 0) {
    //         dbg(g.from(a), "->", g.to(a), "@", f(a));
    //     }
    // }
    auto nextDfs = [&](int i) {
        Graph::Node cur = vOut[i];
        while (true) {
            bool found = false;
            for (auto a : g.outArcs(cur)) {
                if (f(a) > 0) {
                    // dbg(cur, "=>", g.to(a));
                    found = true;
                    f(a)--;
                    if (g.to(a) == t) {
                        return label(a);
                    } else {
                        cur = g.to(a);
                    }
                    break;
                }
            }
            if (!found) {
                dbg("wtf");
                throw 42;
            }
        }
    };
    bool first = true;
    forn (int, i, 1 << n) {
        if (!needed[i]) {
            continue;
        }
        if (first) {
            first = false;
        } else {
            out << "R ";
        }
        int u = i, prev = 0;
        while (u != -1) {
            needed[u] = false;
            forn (int, bit, n) {
                if ((u & (1 << bit)) && !(prev & (1 << bit))) {
                    out << bit << " ";
                }
            }
            prev = u;
            u = nextDfs(u);
            // dbg(prev, "->", u);
        }
    }
    out << "\n";
}

void solve(istream& in, ostream& out) {
    int n = next<int>(in);
    int m = next<int>(in);
    vector<uint8_t> needed(1 << n, 0);
    forn (int, i, m) {
        string s = next<string>(in);
        int v = 0;
        forn (int, j, n) {
            v = 2 * v + (s[n - j - 1] - '0');
        }
        needed[v] = 1;
    }
    solveFast(n, needed, out);
    // while (true) {
    //     vector<uint8_t> needed(1 << n, 0);
    //     forn (int, i, 1 << n) {
    //         needed[i] = rand() % 16 < 1;
    //     }
    //     std::cerr << "here ";
    //     forn (int, i, 1 << n) {
    //         if (needed[i]) {
    //             std::cerr << i << " ";
    //         }
    //     }
    //     std::cerr << endl;
    //     solveFast(n, needed, out);
    // }
}


int main() {
  solve(cin, cout);
  return 0;
}

