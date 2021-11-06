import java.util.*;
import java.io.*;

public class jeroen
{
	static int[] d, e;
	static int[][] b;
	static boolean[] done;
	static int ans;
	static int idx;

	static void dfs(int i) {
		if(done[i]) return;
		done[i] = true;
		for(int j = 0; j < d[i]; j++)
			dfs(b[i][j]);
		ans = Math.max(ans, e[i] + idx++);
	}
	
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.valueOf(in.readLine());
		e = new int[n];
		d = new int[n];
		b = new int[n][];
		for(int i = 0; i < n; i++) {
			String[] ps = in.readLine().split(" ");
			e[i] = Integer.valueOf(ps[0]);
			d[i] = Integer.valueOf(ps[1]);
			b[i] = new int[d[i]];
			for(int j = 0; j < d[i]; j++)
				b[i][j] = Integer.valueOf(ps[j+2]) - 1;
		}

		// Do longest topics first
		Topic[] topics = new Topic[n];
		for(int i = 0; i < n; i++)
			topics[i] = new Topic(i, e[i]);
		Arrays.sort(topics);
		done = new boolean[n];
		ans = 0;
		idx = 0;
		for(int i = 0; i < n; i++) {
			if(done[topics[i].i]) continue;
			dfs(topics[i].i);
		}
		System.out.println(ans);
	}
}

class Topic implements Comparable<Topic> {
	public int i, e;

	public Topic(int i, int e) {
		this.i = i;
		this.e = e;
	}

	public int compareTo(Topic other) {
		return other.e - e;
	}
}
