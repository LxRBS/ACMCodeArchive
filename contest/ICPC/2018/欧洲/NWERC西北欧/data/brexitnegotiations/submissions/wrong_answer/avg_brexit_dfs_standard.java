import java.util.ArrayList;
import java.util.Scanner;


//O(V+E+W)
public class avg_brexit_dfs_standard {
    static boolean[] visited;
    static ArrayList<Integer>[] outgoing;
    static int limit = 0;
    static int fromEnd = 0;
    static int[] weights;

    public static void main(String[] args) {

        //read Input
        Scanner sc = new Scanner (System.in);
        int nrNodes = sc.nextInt();
        weights = new int [nrNodes];
        int[] indegrees = new int [nrNodes];
        int[] outdegrees = new int [nrNodes];
        outgoing = new ArrayList[nrNodes];

        //O(V)
        for (int j = 0; j < nrNodes; j++) {
            outgoing[j] = new ArrayList();
        }

        //O(V)
        for (int i = 0; i < nrNodes; i++) {
            weights[i] = sc.nextInt();
            outdegrees[i] = sc.nextInt();
            //O(E) total
            for (int j = 0; j < outdegrees[i]; j++) {
                int v = sc.nextInt();
                --v;
                outgoing[i].add(v);
                indegrees[v]++;
            }
        }

        //Topo order
        //O(V+E)
        visited  = new boolean[nrNodes];

        //start at arbitrary vertex and run DFS to determine topo order.
        for (int i = 0; i < nrNodes; i++) {
            visit(i);
        }

        System.out.println(limit);
    }

    public static void visit(int index) {
        if (visited[index]) {
            return;
        }

        visited[index] = true;
        for (int node : outgoing[index]) {
            visit(node);
        }

        limit = Math.max(limit, weights[index] + fromEnd++);
    }
}
