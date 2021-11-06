import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class jeroen
{
	static long INF = 100000000000000l;
	static long A;
	static int n;
	static long[] dist_to_janet;
	static ArrayList<Edge>[] next, prev;
	
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] ps = in.readLine().split(" ");
		A = Long.valueOf(ps[0]);
		long B = Long.valueOf(ps[1]);
		ps = in.readLine().split(" ");
		n = Integer.valueOf(ps[0]);
		int m = Integer.valueOf(ps[1]);
		int[] u = new int[m];
		int[] v = new int[m];
		long[] t = new long[m];
		for(int i = 0; i < m; i++) {
			ps = in.readLine().split(" ");
			u[i] = Integer.valueOf(ps[0]) - 1;
			v[i] = Integer.valueOf(ps[1]) - 1;
			t[i] = Long.valueOf(ps[2]);
		}

		// Preprocess the input into something nicer
		next = new ArrayList[n];
		prev = new ArrayList[n];
		for(int i = 0; i < n; i++) {
			next[i] = new ArrayList<Edge>();
			prev[i] = new ArrayList<Edge>();
		}
		for(int i = 0; i < m; i++) {
			next[u[i]].add(new Edge(v[i], t[i]));
			prev[v[i]].add(new Edge(u[i], t[i]));
		}
		
		// Compute distance from home (Dijkstra)
		long[] dist_from_home = Dijkstra(next, 0);

		// Compute distance to Janet for each intersection (Dijkstra on reversed graph)
		dist_to_janet = Dijkstra(prev, n-1);

		// Initialize some arrays
		done = new boolean[n];
		loop = new boolean[n];
		mem = new long[n];

		// Binary search over the answer
		long low = 0; // if we're lucky, Janet knows exactly when she's ready
		long up = dist_from_home[n-1]; // or we just wait at home until we get the call...
		while(low != up) {
			long t_test = (up + low) / 2;
			boolean possible = false;

			// Assuming the answer is t, see if we have a route where we are always within
			// t minutes driving from Janet between time A and B
			for(int i = 0; i < n; i++) done[i] = false;
			for(int i = 0; i < m; i++) {
				// For each edge as entrypoint, see if this could be the start of a long enough path
				if(dist_to_janet[v[i]] > t_test) continue;
				long fromThisEdge  = maxPathLen(v[i], t_test);
				long partOnTheEdge = Math.min(t[i], t_test - dist_to_janet[v[i]]);
				long startSegment  = Math.min(t[i], A - dist_from_home[u[i]]);

				if(startSegment + partOnTheEdge >= t[i] // we can get here on time
				   && fromThisEdge + partOnTheEdge >= B - A)
					possible = true;
			}

			// And continue the binary search
			if(possible) up  = t_test;
			else         low = t_test + 1;
		}

		System.out.println(low);
	}

	private static boolean[] done;
	private static boolean[] loop;
	private static long[] mem;
	public static long maxPathLen(int i, long t) {
		// Can we visit this node?
		if(dist_to_janet[i] > t) return -INF;

		// Are we in some loop?
		if(loop[i]) return INF;
		loop[i] = true;

		// Have we done this node already?
		if(!done[i]) {
			done[i] = true;
			mem[i] = 0;
		
			// Look at possible further nodes
			for(Edge e : next[i]) {
				if(dist_to_janet[e.i] + e.t > t) continue;
				mem[i] = Math.max(mem[i], maxPathLen(e.i, t) + e.t);
			}
		}

		// And return
		loop[i] = false;
		return mem[i];
	}

	private static long[] Dijkstra(ArrayList<Edge>[] edges, int start) {
		int n = edges.length;
		PriorityQueue<QItem> Q = new PriorityQueue<QItem>();
		long[] dist = new long[n];
		for(int i = 0; i < n; i++)
			dist[i] = INF;
		Q.add(new QItem(start, 0));
		while(!Q.isEmpty()) {
			QItem top = Q.poll();
			if(dist[top.i] != INF) continue;
			dist[top.i] = top.t;

			for(Edge e : edges[top.i])
				Q.add(new QItem(e.i, top.t + e.t));
		}
		return dist;
	}
}

class Edge {
	public int i;
	public long t;
	
	public Edge(int i, long t) {
		this.i = i;
		this.t = t;
	}
}

class QItem implements Comparable<QItem> {
	public int i;
	public long t;

	public QItem(int i, long t) {
		this.i = i;
		this.t = t;
	}

	public int compareTo(QItem other) {
		return Long.compare(t, other.t);
	}
}
