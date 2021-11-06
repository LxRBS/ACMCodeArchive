import java.io.*;
import java.util.*;

public class Pokegene_xiaowuc1_trie {
	private static BufferedReader br;
	private static StringTokenizer st;
	private static PrintWriter pw;

	public static void main(String[] args) throws IOException {
		br = new BufferedReader(new InputStreamReader(System.in));
		pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		root = new Node();
		int n = readInt();
		int qq = readInt();
		mapping = new int[n];
		l = new State[n];
		for(int i = 0; i < n; i++) {
			String s = readToken();
			l[i] = new State(s, i, insert(s));
		}
		Arrays.sort(l);
		for(int i = 0; i < n; i++) {
			mapping[l[i].i] = i;
		}
		initLCA();
		while(qq-- > 0) {
			pw.println(solve());
		}
		exitImmediately();
	}

	static int[] mapping;
	static State[] l;
	static int[] depth;
	
	static final int MAX_D = 18;
	static int[][] lca;
	public static int lca(int a, int b) {
		if(depth[a] < depth[b]) {
			a ^= b;
			b ^= a;
			a ^= b;
		}
		for(int d = MAX_D-1; d >= 0; d--) {
			while(depth[a] - (1<<d) >= depth[b]) {
				a = lca[d][a];
			}
		}
		for(int d = MAX_D-1; d > 0; d--) {
			while(lca[d][a] != lca[d][b]) {
				a = lca[d][a];
				b = lca[d][b];
			}
		}
		while(a != b) {
			a = lca[0][a];
			b = lca[0][b];
		}
		return a;
	}
	public static void initLCA() {
		lca = new int[MAX_D][numNodes];
		depth = new int[numNodes];
		LinkedList<Node> q = new LinkedList<>();
		q.add(root);
		while(!q.isEmpty()) {
			Node curr = q.removeFirst();
			for(int i = 0; i < 26; i++) {
				if(curr.child[i] != null) {
					lca[0][curr.child[i].id] = curr.id;
					depth[curr.child[i].id] = depth[curr.id] + 1;
					q.add(curr.child[i]);
				}
			}
		}
		for(int d = 1; d < MAX_D; d++) {
			for(int i = 0; i < lca[d].length; i++) {
				lca[d][i] = lca[d-1][lca[d-1][i]];
			}
		}
	}
	
	public static long solve() throws IOException {
		int n = readInt();
		int k = readInt();
		int[] have = new int[n];
		for(int i = 0; i < n; i++) {
			have[i] = mapping[readInt()-1];
		}
		Arrays.sort(have);
		long ret = 0;
		for(int i = 0; i + k <= n; i++) {
			int match = lca(l[have[i]].leaf, l[have[i+k-1]].leaf);
			int border = 0;
			if(i > 0) {
				border = Math.max(border, depth[lca(l[have[i-1]].leaf, l[have[i]].leaf)]);
			}
			if(i+k < n) {
				border = Math.max(border, depth[lca(l[have[i+k-1]].leaf, l[have[i+k]].leaf)]);
			}
			ret += Math.max(0, depth[match] - border);
		}
		return ret;
	}
	
	static int numNodes;
	static Node root;
	public static int insert(String s) {
		Node curr = root;
		for(int i = 0; i < s.length(); i++) {
			if(curr.child[s.charAt(i) - 'a'] == null) {
				curr.child[s.charAt(i) - 'a'] = new Node();
			}
			curr = curr.child[s.charAt(i) - 'a'];
		}
		return curr.id;
	}
	static class Node {
		int id;
		Node[] child;
		public Node() {
			id = numNodes++;
			child = new Node[26];
		}
	}
	
	static class State implements Comparable<State> {
		public String s;
		public int i;
		public int leaf;
		public State(String s, int i, int leaf) {
			super();
			this.s = s;
			this.i = i;
			this.leaf = leaf;
		}
		public int compareTo(State state) {
			return s.compareTo(state.s);
		}
	}
	
	private static void exitImmediately() {
		pw.close();
		System.exit(0);
	}

	private static int readInt() throws IOException {
		return Integer.parseInt(readToken());
	}

	private static String readLine() throws IOException  {
		String s = br.readLine();
		if(s == null) {
			exitImmediately();
		}
		st = null;
		return s;
	}

	private static String readToken() throws IOException  {
		while(st == null || !st.hasMoreTokens())  {
			st = new StringTokenizer(readLine().trim());
		}
		return st.nextToken();
	}
}
