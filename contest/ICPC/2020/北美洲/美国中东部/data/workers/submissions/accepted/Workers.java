import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;
import java.util.Scanner;

public class Workers {

	public static final int MAX = 100;
	
	public static int[][] workToGates = new int[MAX][2*MAX];
	public static int[][] gatesToStas = new int[2*MAX][MAX];
	
	public static void main(String[] args) {
		
		int n;
		BiGraph g;
		Scanner in = new Scanner(System.in);
		n = in.nextInt();
		
		for(int i=0; i<n; i++) {
			for(int j=0; j<2*n; j++)
				workToGates[i][j] = in.nextInt();
		}
		for(int j=0; j<n; j++) {
			for(int i=0; i<2*n; i++)
				gatesToStas[i][j] = in.nextInt();
		}
								// calculate optimal for every possible assignment of gates
		int minCost = 10000000;
		int [] m1 = null, m2 = null;
		int savb = -1;
		for(int bgate = n; bgate >=0; bgate--) {	// bgate = first B gate used
			g = new BiGraph(n, n);
			for(int a = 0; a<bgate; a++) {
				for(int w=0; w<n; w++) {
					g.addEdge(w, n+a, workToGates[w][2*a]);
				}
			}
			for(int b = bgate; b<n; b++) {
				for(int w=0; w<n; w++) {
					g.addEdge(w, n+b, workToGates[w][2*b+1]);
				}
			}
			int [] matching1 = g.findMinCostMatching();
			g = new BiGraph(n, n);
			for(int a = 0; a<bgate; a++) {
				for(int s=0; s<n; s++) {
					g.addEdge(a, n+s, gatesToStas[2*a][s]);
				}
			}
			for(int b = bgate; b<n; b++) {
				for(int s=0; s<n; s++) {
					g.addEdge(b, n+s, gatesToStas[2*b+1][s]);
				}
			}
			int [] matching2 = g.findMinCostMatching();
			int cost = 0;
			for(int i=0; i<n; i++) {			// costs from workers to gates
				int j = 2*(matching1[i]-n);
				if (matching1[i]-n >= bgate)
					j++;
				cost += workToGates[i][j];
			}
			for(int i=0; i<bgate; i++) {			// costs from gates to stations
				cost += gatesToStas[2*i][matching2[i]-n];
			}
			for(int i=bgate; i<n; i++) {			// costs from gates to stations
				cost += gatesToStas[2*i+1][matching2[i]-n];
			}
//System.out.println("First B at " + bgate + ", cost = " + cost);
//printMatching(matching1, matching2, bgate);
			if (cost < minCost) {
				minCost = cost;
				m1 = matching1;
				m2 = matching2;
				savb = bgate;
			}
		}
		System.out.println(minCost);
		printMatching(m1, m2, savb);
	}
	
	public static void printMatching(int [] m1, int [] m2, int bstart)
	{
		int n = m1.length;
		for(int i=0; i<n; i++) {
			int g = m1[i]-n;
			if (g < bstart)
				System.out.println((i+1) + " " + (g+1) + "A " + (m2[g]+1-n));
			else
				System.out.println((i+1) + " " + (g+1) + "B " + (m2[g]+1-n));
		}
	}

}

class BiGraph
{
	private static final int INF = 100000000;

	private ArrayList<Node> vertices = new ArrayList<Node>();
	private int n, m;

	public BiGraph(int nn, int mm)
	{
		n=nn; m = mm;
		vertices = new ArrayList<Node>();
		for(int i=0; i<n+m; i++)
			vertices.add(new Node("", i));
	}

	public void addEdge(int v, int w, int cost)
	{
		vertices.get(v).addEdge(new Edge(v, w, cost));
	}
	
	public void printGraph()
	{
		for(int i=0; i<n; i++) {
			Node node = vertices.get(i);
			for(int j=n; j<2*n; j++) {
				for(Edge e : node.edges) {
					if (e.w == j)
						System.out.print(e.cost + " ");
				}
			}
			System.out.println();
		}
	}

	public int[] findMinCostMatching()
	{
		Node s = new Node("s", n+m);
		vertices.add(s);
		Iterator<Node> itr = vertices.iterator();
		for(int i=0; i<n; i++)
			s.addEdge(new Edge(n+m, i, 0));
		vertices.add(new Node("t", n+m+1));
		for(int i=n; i<n+m; i++)
			vertices.get(i).addEdge(new Edge(i, n+m+1, 0));
		for(int i=0; i<n+m+2; i++) {
			ArrayList<Edge> path = findMinCostPath();
			if (path == null)
				break;
			addPath(path);
		}
		int [] matching = new int[n];
		itr = vertices.iterator();
		for(int i=0; i<n; i++)
			itr.next();
		for(int i=0; i<m; i++) {
			Edge e = itr.next().edges.get(0);
			matching[e.w] = e.v;
		}
		return matching;
	}

	private void addPath(ArrayList<Edge> path)
	{
		for(Iterator<Edge> itr = path.iterator() ; itr.hasNext() ; ) {
			Edge e = itr.next();
			vertices.get(e.v).edges.remove(e);
			vertices.get(e.w).edges.add(new Edge(e.w, e.v, -e.cost));
		}
	}

	private ArrayList<Edge> findMinCostPath()
	{
		int nVert = n + m + 2;
		TableEntry [][] table = new TableEntry[nVert][nVert];
		for(int i=0; i<nVert; i++) {
			table[0][i] = new TableEntry(INF, null);
		}
		table[0][n+m] = new TableEntry(0, null);
		int pass;
		for(pass=1; pass < nVert; pass++) {
			if (vertices.get(n+m).edges.size() == 0)
				break;					// no more edges leaving s
			//System.out.println("Pass = " + pass);
			for(int i=0; i<nVert; i++) {
				//System.out.println("  i = " + i + ", cost = " + table[pass-1][i].cost);
				table[pass][i] = new TableEntry(table[pass-1][i].cost, table[pass-1][i].prev);
			}
			for(int i=0; i<nVert; i++) {
				for(Iterator<Edge> itr = vertices.get(i).edges.iterator(); itr.hasNext(); ) {
					Edge e = itr.next();
					if (table[pass-1][i].cost != INF && table[pass-1][i].cost + e.cost < table[pass][e.w].cost) {
						table[pass][e.w].cost = table[pass-1][i].cost+e.cost;
						table[pass][e.w].prev = e;
					}
				}
			}
		}
		return buildPath(table, pass, n+m+1);
	}

	private ArrayList<Edge> buildPath(TableEntry [][] table, int size, int dest)
	{
		if (table[size-1][dest].prev == null)
			return new ArrayList<Edge>();
		else {
			ArrayList<Edge> ans = buildPath(table, size, table[size-1][dest].prev.v);
			ans.add(table[size-1][dest].prev);
			return ans;
		}
	}
}

class TableEntry
{
	int cost;
	Edge prev;

	public TableEntry(int c, Edge p)
	{
		cost = c;
		prev = p;
	}
}

class Node
{
	String name;
	int num;
	ArrayList<Edge> edges;

	public Node(String n, int nm)
	{
		name = n;
		num = nm;
		edges = new ArrayList<Edge>();
	}

	public void addEdge(Edge e)
	{
		edges.add(e);
	}
}

class Edge
{
	int v, w;
	int cost;

	public Edge(int vv, int ww, int c)
	{
		v = vv;
		w = ww;
		cost = c;
	}
}