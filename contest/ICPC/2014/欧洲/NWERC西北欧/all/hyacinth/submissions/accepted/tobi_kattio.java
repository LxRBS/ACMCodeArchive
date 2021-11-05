import java.util.*;
import java.io.*;

public class tobi_kattio {
	public static int N, from, to, channel[][] = new int[10005][2];
	public static ArrayList<Integer> adj[] = new ArrayList[10005];
	public static int q[][] = new int[2][20005];
	public static int numChan = 42;
	public static boolean visited[] = new boolean[10005];

	public static void main(String args[]) {
		Kattio io = new Kattio(System.in, System.out);
		N = io.getInt();
		if (N == 2) {
			System.out.println("0 1\n0 1");
			return;
		}
		
		for (int i = 0; i < N; i++) adj[i] = new ArrayList<>();
		for (int i = 0; i < N - 1; i++) {
			from = io.getInt() - 1;
			to = io.getInt() - 1;
			adj[from].add(to);
			adj[to].add(from);
		}
		int qEnd = 0, qCur = 0;
		for (int i = 0; i < N; i++) if (adj[i].size() == 1) {
			q[0][qEnd] = i;
			q[1][qEnd++] = numChan++;
			break;
		}
		while (qCur < qEnd) {
			int node = q[0][qCur], freq = q[1][qCur++];
			if (visited[node]) continue;
			visited[node] = true;
			channel[node][0] = freq;
			channel[node][1] = numChan++;
			for (Integer i : adj[node]) if (!visited[i]) {
				q[0][qEnd] = i;
				q[1][qEnd++] = channel[node][1];
			}
		}
		for (int i = 0; i < N; i++) io.println(channel[i][0] + " " + channel[i][1]);
		io.close();
	}
}

class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
	super(new BufferedOutputStream(System.out));
	r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
	super(new BufferedOutputStream(o));
	r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
	return peekToken() != null;
    }

    public int getInt() {
	return Integer.parseInt(nextToken());
    }

    public double getDouble() { 
	return Double.parseDouble(nextToken());
    }

    public long getLong() {
	return Long.parseLong(nextToken());
    }

    public String getWord() {
	return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
	if (token == null) 
	    try {
		while (st == null || !st.hasMoreTokens()) {
		    line = r.readLine();
		    if (line == null) return null;
		    st = new StringTokenizer(line);
		}
		token = st.nextToken();
	    } catch (IOException e) { }
	return token;
    }

    private String nextToken() {
	String ans = peekToken();
	token = null;
	return ans;
    }
}
