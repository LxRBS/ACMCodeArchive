import java.util.*;
import java.io.*;

class Edge {
	int t = 0;
	Edge next = null;
}

public class jeroen_tobi {
	public static final int MAXN = 10000;
	public static Edge edges[] = new Edge[MAXN];

	public static void add(int a, int b) {
		Edge n = new Edge();
		n.t = b;
		n.next = edges[a];
		edges[a] = n;
	}

	public static int nextf;
	public static int f1[] = new int[MAXN], f2[] = new int[MAXN];

	public static void dfs(int i, int uf1, int uf2, int p) {
		Edge next;
		f1[i] = uf1 > -1 ? uf1 : nextf++;
		f2[i] = uf2 > -1 ? uf2 : nextf++;

		for(next = edges[i]; next != null; next = next.next)
			if(next.t != p)
				dfs(next.t, f2[i], uf1 > -1 ? -1 : f1[i], i);
	}

	public static void main(String args[]) {
		int n, i, a, b;
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		for(i = 0; i < n - 1; i++) {
			a = sc.nextInt();
			b = sc.nextInt();
			add(a-1,b-1);
			add(b-1,a-1);
		}
		i = 0;
		while(edges[i].next != null) i++;
		nextf = 0;
		dfs(i, -1, -1, -1);
		for(i = 0; i < n; i++)
			System.out.println(f1[i] + " " + f2[i]);
	}
}
