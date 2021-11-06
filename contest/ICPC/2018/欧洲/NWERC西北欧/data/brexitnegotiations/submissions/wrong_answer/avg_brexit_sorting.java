import java.util.ArrayList;
import java.util.Scanner;
import java.util.TreeMap;

//O(V log V + E)
public class avg_brexit_sorting {
    public static void main(String[] args) {

        //read Input
        Scanner sc = new Scanner (System.in);
        int nrNodes = sc.nextInt();
        int[] weights = new int [nrNodes];
        int[] indegrees = new int [nrNodes];
        int[] outdegrees = new int [nrNodes];
        ArrayList<Integer>[] outgoing = new ArrayList[nrNodes];

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

        int limit = 0;

        //O(V log V)
        TreeMap<Integer,Integer> openSet = new TreeMap();
        for (int i = 0; i < indegrees.length; i++) {
            if (indegrees[i] == 0) {
                openSet.put(weights[i],i);
            }
        }

        //Topo order
        //O(V log V + E)
        int remain = nrNodes - 1;
        //always select the cheapest node that is in the open set.
        while (!openSet.isEmpty()) {
            int index = openSet.pollFirstEntry().getValue();

            //reduce indegrees for outgoing edges
            for (int node : outgoing[index]) {
                indegrees[node]--;
                if (indegrees[node] == 0) {
                    openSet.put(weights[node],node);
                }
            }

            //update limit
            limit = Math.max(limit, weights[index] + remain);
            remain--;
        }
        System.out.println(limit);
    }
}
