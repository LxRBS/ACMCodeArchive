// translation from C++

import java.util.*;
import java.io.*;
import java.math.*;

public class comrace_hamerly {
    final static int UNVISITED = 0;
    final static int BEING_VISITED = 1;
    final static int VISITED = 2;

    final static int SHIFT = 21;
    final static int MASK = (1 << SHIFT);
    final static int UNMASK = (1 << SHIFT) - 1;

    static int stack[] = new int[200000];

    static void dfs_nonrec(int edges[][], int current, int [] state, ArrayList<Integer> finish) {
        if (state[current] != UNVISITED)
            return;

        state[current] = BEING_VISITED;
        int top = 0;
        stack[top++] = current;

        while (0 < top) {
            current = stack[--top];
            boolean done = (current & MASK) != 0;
            current &= UNMASK;

            if (state[current] == VISITED)
                continue;

            if (done) {
                state[current] = VISITED;
                finish.add(current);
            } else {
                stack[top++] = current | MASK;
                for (int dest : edges[current]) {
                    if (state[dest] != VISITED) {
                        state[dest] = BEING_VISITED;
                        stack[top++] = dest;
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
    static void longest_paths(int g[][], int path_length[], BigInteger multiplicity[], ArrayList<Integer> finish) {
        // prepare the out-parameters
        Arrays.fill(path_length, 0);
        Arrays.fill(multiplicity, BigInteger.ONE);

        finish.clear();

        // DFS-visit everything to get a finishing order
        int state[] = new int[g.length];
        Arrays.fill(state, UNVISITED);
        for (int start = 0; start < g.length; start++)
            dfs_nonrec(g, start, state, finish);

        // compute the longest paths for each node and their multiplicity, going in
        // topological order from the starting points of the DAG to the leaves
        for (int ui = finish.size() - 1; ui >= 0; ui--) {
            int u = finish.get(ui);
            for (int v : g[u]) {
                int l = path_length[u] + 1;
                if (path_length[v] < l) {
                    path_length[v] = l;
                    multiplicity[v] = multiplicity[u];
                } else if (path_length[v] == l) {
                    multiplicity[v] = multiplicity[v].add(multiplicity[u]);
                }
            }
        }
    }

    public static void main(String args[]) throws Exception {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

        String [] tokens = input.readLine().split(" ");
        int n = Integer.parseInt(tokens[0]),
            m = Integer.parseInt(tokens[1]);

        int u_edges[] = new int[m];
        int v_edges[] = new int[m];
        int num_fwd_edges[] = new int[n];
        int num_rev_edges[] = new int[n];

        // load all the edges into one array
        for (int i = 0; i < m; ++i) {
            tokens = input.readLine().split(" ");
            u_edges[i] = Integer.parseInt(tokens[0]) - 1;
            v_edges[i] = Integer.parseInt(tokens[1]) - 1;
            num_fwd_edges[u_edges[i]] += 1;
            num_rev_edges[v_edges[i]] += 1;
        }

        // make a ragged array representation
        int fwd_edges[][] = new int[n][];
        int rev_edges[][] = new int[n][];
        for (int i = 0; i < n; ++i) {
            fwd_edges[i] = new int[num_fwd_edges[i]];
            rev_edges[i] = new int[num_rev_edges[i]];
        }

        Arrays.fill(num_fwd_edges, 0);
        Arrays.fill(num_rev_edges, 0);
        for (int i = 0; i < m; ++i) {
            int u = u_edges[i];
            int v = v_edges[i];
            fwd_edges[u][num_fwd_edges[u]++] = v;
            rev_edges[v][num_rev_edges[v]++] = u;
        }

        // find all the longest paths in forward/reverse graphs starting from the
        // starting/ending nodes
        int fwd_path_length[] = new int[n];
        int rev_path_length[] = new int[n];
        BigInteger fwd_multiplicity[] = new BigInteger[n];
        BigInteger rev_multiplicity[] = new BigInteger[n];
        ArrayList<Integer> fwd_finish = new ArrayList<Integer>();
        ArrayList<Integer> rev_finish = new ArrayList<Integer>();
        longest_paths(fwd_edges, fwd_path_length, fwd_multiplicity, fwd_finish);
        longest_paths(rev_edges, rev_path_length, rev_multiplicity, rev_finish);

        int longest_path_length = 0;
        for (int p : fwd_path_length) {
            if (longest_path_length < p)
                longest_path_length = p;
        }

        // How many total longest paths are there?
        // Also precompute the per-node multiplicity and path length.
        BigInteger longest_path_multiplicity = BigInteger.ZERO;
        BigInteger multiplicity[] = new BigInteger[n];
        Arrays.fill(multiplicity, BigInteger.ZERO);
        int path_length[] = new int[n];

        for (int u = 0; u < n; ++u) {
            multiplicity[u] = fwd_multiplicity[u].multiply(rev_multiplicity[u]);
            path_length[u] = fwd_path_length[u] + rev_path_length[u];
            if (rev_path_length[u] == longest_path_length) {
                longest_path_multiplicity = longest_path_multiplicity.add(rev_multiplicity[u]);
            }
        }

        // Identify critical edges, in reverse topological finish order. For each
        // critical edge, find out what the longest path length would be to end
        // here, or alternatively to continue on a different path from here.
        int answer = longest_path_length;
        for (int ui = fwd_finish.size() - 1; 0 <= ui; --ui) {
            int u = fwd_finish.get(ui);

            // u is a critical node if it has the longest path length and
            // multiplicity
            if (path_length[u] != longest_path_length || !multiplicity[u].equals(longest_path_multiplicity))
                continue;

            // now identify if there is some (u,v) that is a critical edge
            int critical_v = -1;
            for (int v : fwd_edges[u]) {
                // there may be multiple paths from u->v; we want the longest one
                if (path_length[v] == longest_path_length && multiplicity[v].equals(longest_path_multiplicity) && fwd_path_length[u] + 1 == fwd_path_length[v]) {
                    critical_v = v;
                    break;
                }
            }

            if (critical_v == -1)
                continue;

            int max_length_through_u = fwd_path_length[u]; // not going any further
            for (int v : fwd_edges[u])
                if (v != critical_v && max_length_through_u < fwd_path_length[u] + rev_path_length[v] + 1)
                    max_length_through_u = fwd_path_length[u] + rev_path_length[v] + 1;

            if (max_length_through_u < answer)
                answer = max_length_through_u;
        }

        System.out.println(answer);
    }
}
