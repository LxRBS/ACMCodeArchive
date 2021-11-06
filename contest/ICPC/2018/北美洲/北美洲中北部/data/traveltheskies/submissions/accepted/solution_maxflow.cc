#include <iostream>
#include <vector>

using namespace std;

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )

// BEGIN
// Adjacency list implementation of Dinic's blocking flow algorithm.
// This is very fast in practice, and only loses to push-relabel flow.
//
// Running time:
//     O(|V|^2 |E|)
//
// INPUT:
//     - graph, constructed using AddEdge()
//     - source
//     - sink
//
// OUTPUT:
//     - maximum flow value
//     - To obtain the actual flow values, look at all edges with
//       capacity > 0 (zero capacity edges are residual edges).
// Taken from Stanford ACM: http://stanford.edu/~liszt90/acm/notebook.html#file1

const int INF = 2000000000;

struct Edge {
    int from, to, cap, flow, index;
    Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct Dinic {
    int N;
    vector<vector<Edge> > G;
    vector<Edge *> dad;
    vector<int> Q;
    
    Dinic(int N) : N(N), G(N), dad(N), Q(N) {}
    
    void AddEdge(int from, int to, int cap) {
        G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
        if (from == to) G[from].back().index++;
        G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
    }
    
    long long BlockingFlow(int s, int t) {
        fill(dad.begin(), dad.end(), (Edge *) NULL);
        dad[s] = &G[0][0] - 1;
        
        int head = 0, tail = 0;
        Q[tail++] = s;
        while (head < tail) {
            int x = Q[head++];
            for (int i = 0; i < G[x].size(); i++) {
                Edge &e = G[x][i];
                if (!dad[e.to] && e.cap - e.flow > 0) {
                    dad[e.to] = &G[x][i];
                    Q[tail++] = e.to;
                }
            }
        }
        if (!dad[t]) return 0;
        
        long long totflow = 0;
        for (int i = 0; i < G[t].size(); i++) {
            Edge *start = &G[G[t][i].to][G[t][i].index];
            int amt = INF;
            for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
                if (!e) { amt = 0; break; }
                amt = min(amt, e->cap - e->flow);
            }
            if (amt == 0) continue;
            for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
                e->flow += amt;
                G[e->to][e->index].flow -= amt;
            }
            totflow += amt;
        }
        return totflow;
    }
    
    long long GetMaxFlow(int s, int t) {
        long long totflow = 0;
        while (long long flow = BlockingFlow(s, t))
            totflow += flow;
        return totflow;
    }
};
// END

int main() {
  int k, n, m;
  cin >> k >> n >> m;
  int s = k * n, u = s + 1, t = u + 1;

  int num_nodes = n * k + 3;
  std::vector<std::vector<int>> adjacency_matrix(
      num_nodes, std::vector<int>(num_nodes, 0));
  auto airport_node = [k](int day, int airport) { return day * k + airport; };
  // People can stay at an airport overnight.
  for (int day = 0; day < n; ++day) {
    for (int airport = 0; airport < k; ++airport) {
      // On the last day, everyone goes to a virtual node 'u'.
      int dest_node = day + 1 < n ? airport_node(day + 1, airport) : u;
      adjacency_matrix[airport_node(day, airport)][dest_node] = INF;
    }
  }
  int total_flight_capacity = 0;
  for (int i = 0; i < m; ++i) {
    int start, end, day, capacity;
    cin >> start >> end >> day >> capacity;
    --start;
    --end;
    --day;
    adjacency_matrix[airport_node(day, start)][t] += capacity;
    // On the last day, everyone goes to a virtual node 'u'.
    int node = day + 1 < n ? airport_node(day + 1, end) : u;
    adjacency_matrix[s][node] += capacity;
    total_flight_capacity += capacity;
  }
  int total_num_people = 0;
  for (int i = 0; i < k * n; ++i) {
    int airport, day, num_people;
    cin >> airport >> day >> num_people;
    --airport;
    --day;
    adjacency_matrix[s][airport_node(day, airport)] += num_people;
    total_num_people += num_people;
  }
  // The total number of people in the airport on the last day must equal
  // total_num_people.
  adjacency_matrix[u][t] += total_num_people;

  Dinic graph(n * k + 3);
  for (int i = 0; i < num_nodes; ++i) {
    for (int j = 0; j < num_nodes; ++j) {
      if (adjacency_matrix[i][j] > 0) {
        graph.AddEdge(i, j, adjacency_matrix[i][j]);
      }
    }
  }
  long long max_flow = graph.GetMaxFlow(s, t);
  /*
  cerr << "flow: " << max_flow << endl;
  for (const auto& edges : graph.G) {
    for (const auto& edge : edges) {
      if (edge.cap > 0) {
        cerr << edge.from << " -> " << edge.to << ": " << edge.flow << " / "
             << edge.cap << endl;
      }
    }
  }*/
  if (max_flow == total_num_people + total_flight_capacity) {
    cout << "optimal" << endl;
  } else {
    cout << "suboptimal" << endl;
  }
  return 0;
}
