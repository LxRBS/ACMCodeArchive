import java.util.*;
import java.io.*;

public class tobi_adjmatrix {
	public static int N, from, to, channel[][] = new int[10005][2];
	public static boolean adj[][] = new boolean[10005][10005];
	public static LinkedList<Integer> nodeQ = new LinkedList<>();
	public static LinkedList<Integer> freqQ = new LinkedList<>();
	public static int numChan = 42;
	public static boolean visited[] = new boolean[10005];

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		if (N == 2) {
			System.out.println("0 1\n0 1");
			return;
		}
		
		for (int i = 0; i < N - 1; i++) {
			from = sc.nextInt() - 1;
			to = sc.nextInt() - 1;
			adj[from][to] = adj[to][from] = true;
		}
		for (int i = 0; i < N; i++) {
			int cnt = 0;
			for (int j = 0; j < N; j++) {
				if (adj[i][j]) cnt++;
			}
			if (cnt == 1) {
				nodeQ.add(i);
				freqQ.add(numChan++);
				break;
			}
		}
		while (nodeQ.size() > 0) {
			int node = nodeQ.poll(), freq = freqQ.poll();
			if (visited[node]) continue;
			visited[node] = true;
			channel[node][0] = freq;
			channel[node][1] = numChan++;
			for (int i = 0; i < N; i++) if (adj[node][i] && !visited[i]) {
				freqQ.add(channel[node][1]);
				nodeQ.add(i);
			}
		}
		for (int i = 0; i < N; i++) System.out.println(channel[i][0] + " " + channel[i][1]);
	}
}
