#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

// count all the maximum-length paths
// for each node, identify how many max-length paths go through it
// identify all edges that touch two nodes that both are used for *all* max-length paths
// identify the earliest such edge find out the longest path if it is removed

typedef std::vector<unsigned long long> vll;
typedef std::vector<int> vi;
typedef std::vector<vi> graph;
typedef std::vector<bool> vb;

const int UNVISITED = 0;
const int BEING_VISITED = 1;
const int VISITED = 2;

void dfs(graph const &edges, int current, vi *state, vi *finish) {
    if (state->at(current) != UNVISITED)
        return;
    state->at(current) = BEING_VISITED;
    for (auto const dest : edges[current])
        dfs(edges, dest, state, finish);
    finish->push_back(current);
    state->at(current) = VISITED;
}

void dfs_nonrec(graph const &edges, int current, vi *state, vi *finish) {
    if (state->at(current) != UNVISITED)
        return;

    state->at(current) = BEING_VISITED;
    std::vector<std::pair<int, bool>> stack = { {current, false} };

    while (stack.size()) {
        auto [current, done] = stack.back();
        stack.pop_back();

        if (state->at(current) == VISITED)
            continue;

        if (done) {
            state->at(current) = VISITED;
            finish->push_back(current);
        } else {
            stack.push_back({current, true});
            for (auto const dest : edges[current]) {
                if (state->at(dest) != VISITED) {
                    state->at(dest) = BEING_VISITED;
                    stack.push_back({dest, false});
                }
            }
        }
    }
}

// find the longest paths, starting only from the given starting nodes
//
// parameters:
//   g: the directed acyclic graph
//  path_length: gets the length of the longest path, for each node reachable
//  multiplicity: gets the count of how many times the longest path for that
//      node goes through the node
//  finish: gets the DFS finish time (postorder)
void longest_paths(graph const &g, vi *path_length, vll *multiplicity, vi *finish) {
    // prepare the out-parameters
    path_length->clear();
    path_length->resize(g.size(), 0);
    multiplicity->clear();
    multiplicity->resize(g.size(), 1);
    finish->clear();

    // DFS-visit everything to get a finishing order
    vi state(g.size(), UNVISITED);
    for (size_t start = 0; start < g.size(); start++)
        dfs_nonrec(g, start, &state, finish);

    // compute the longest paths for each node and their multiplicity, going in
    // topological order from the starting points of the DAG to the leaves
    for (auto u = finish->rbegin(); u != finish->rend(); ++u) {
        for (auto v : g[*u]) {
            auto l = path_length->at(*u) + 1;
            if (path_length->at(v) < l) {
                path_length->at(v) = l;
                multiplicity->at(v) = multiplicity->at(*u);
            } else if (path_length->at(v) == l) {
                multiplicity->at(v) += multiplicity->at(*u);
            }
        }
    }
}

int main(int argc, char **argv) {
    int n, m;
    std::cin >> n >> m;

    // load the data and construct the graph
    graph fwd_edges(n), rev_edges(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        fwd_edges[u-1].push_back(v-1);
        rev_edges[v-1].push_back(u-1);
    }

    // find all the longest paths in forward/reverse graphs starting from the
    // starting/ending nodes
    vi fwd_path_length, fwd_finish, rev_path_length, rev_finish;
    vll fwd_multiplicity, rev_multiplicity;
    longest_paths(fwd_edges, &fwd_path_length, &fwd_multiplicity, &fwd_finish);
    longest_paths(rev_edges, &rev_path_length, &rev_multiplicity, &rev_finish);
    auto longest_path_length = *std::max_element(fwd_path_length.begin(), fwd_path_length.end());
    //std::cerr << "longest path: " << longest_path_length << "\n";

    // How many total longest paths are there?
    // Also precompute the per-node multiplicity and path length.
    unsigned long long longest_path_multiplicity = 0;
    vll multiplicity(n, 0);
    vi path_length(n, 0);
    for (int u = 0; u < n; ++u) {
        multiplicity[u] = fwd_multiplicity[u] * rev_multiplicity[u];
        path_length[u] = fwd_path_length[u] + rev_path_length[u];
        if (rev_path_length[u] == longest_path_length) {
            longest_path_multiplicity += rev_multiplicity[u];
        }
    }
    //std::cerr << "longest_path_multiplicity: " << longest_path_multiplicity << "\n";

    // Identify critical edges, in reverse topological finish order. For each
    // critical edge, find out what the longest path length would be to end
    // here, or alternatively to continue on a different path from here.
    auto answer = longest_path_length;
    for (auto u = fwd_finish.rbegin(); u != fwd_finish.rend(); ++u) {
        // u is a critical node if it has the longest path length and
        // multiplicity
        if (path_length[*u] != longest_path_length or multiplicity[*u] != longest_path_multiplicity)
            continue;

        // now identify if there is some (u,v) that is a critical edge
        auto critical_v = -1;
        for (auto v : fwd_edges[*u]) {
            // there may be multiple paths from u->v; we want the longest one
            if (path_length[v] == longest_path_length and multiplicity[v] == longest_path_multiplicity and fwd_path_length[*u] + 1 == fwd_path_length[v]) {
                critical_v = v;
                break;
            }
        }
        if (critical_v == -1)
            continue;

        auto max_length_through_u = fwd_path_length[*u]; // not going any further
        for (auto v : fwd_edges[*u])
            if (v != critical_v)
                max_length_through_u = std::max(max_length_through_u, fwd_path_length[*u] + rev_path_length[v] + 1);
        answer = std::min(answer, max_length_through_u);
    }

    std::cout << answer << "\n";

    return 0;
}

