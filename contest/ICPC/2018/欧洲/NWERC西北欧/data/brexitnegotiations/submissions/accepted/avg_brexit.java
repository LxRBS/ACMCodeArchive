import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;

//O(V+E+W)
public class avg_brexit {
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

        //O(W)
        ArrayList[] buckets = new ArrayList[1000001];
        for (int j = 0; j < 1000001; j++) {
            buckets[j] = new ArrayList();
        }

        //O(V)
        for (int i = 0; i < nrNodes; i++) {
            weights[i] = sc.nextInt();
            buckets[weights[i]].add(i);
            outdegrees[i] = sc.nextInt();
            //O(E) total
            for (int j = 0; j < outdegrees[i]; j++) {
                int v = sc.nextInt();
                --v;
                outgoing[i].add(v);
                indegrees[v]++;
            }
        }

        //O(W)
        ArrayList<Integer> sorted = new ArrayList(nrNodes);
        for (int i = 0; i < buckets.length; i++) {
            sorted.addAll(buckets[i]);
        }

        int limit = 0;

        //Topo order
        //O(V+E)
        int remain = nrNodes - 1;
        LinkedList<Integer> safe = new LinkedList();
        //in order of weight find first node with 0 indegree
        for (int index : sorted) {
            if (indegrees[index] == 0) {
                safe.add(index);
            }
            while (safe.size() > 0) {
                limit = Math.max(limit, weights[safe.getFirst()] + remain);
                remain--;
                indegrees[safe.getFirst()] = -1; //mark as processed #ugly
                for (int outIndex : outgoing[safe.removeFirst()]) {
                    indegrees[outIndex]--;
                    //if an outgoing node joins the open set and does not increase the limit, process it
                    //note: all nodes we passed before cannot increase the limit and are thus processed.
                    if (indegrees[outIndex] == 0 && weights[outIndex] + remain <= limit) {
                        safe.add(outIndex);
                    }
                }
            }
        }
        System.out.println(limit);
    }
}
