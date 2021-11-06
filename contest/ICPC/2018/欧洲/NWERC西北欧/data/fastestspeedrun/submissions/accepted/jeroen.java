// An O(n^2) solution for speedrunning
import java.util.*;
import java.io.*;

public class jeroen
{
	static int n;
	static int[] x, root;
	static boolean[] done;
	static long[][] a, c;
	static boolean[][] done2;

	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.valueOf(in.readLine());
		x = new int[n];
		long[] s = new long[n];
		a = new long[n][n+1];
		for(int i = 0; i < n; i++) {
			String[] ps = in.readLine().split(" ");
			x[i] = Integer.valueOf(ps[0]) - 1;
			s[i] = Long.valueOf(ps[1]);
			for(int j = 0; j <= n; j++)
				a[i][j] = Long.valueOf(ps[j+2]);
		}

		// For each level, find out it's root, where a
		// root of the cycle is an arbitrary element of
		// the cycle.
		done = new boolean[n];
		root = new int[n];
		for(int i = 0; i < n; i++)
			findRoot(i);

		// Preprocess so that special item has cost 0,
		// and we can just solve all levels depending
		// on it for free.
		long baseline = 0;
		for(int i = 0; i < n; i++) {
			baseline += s[i];
			for(int j = 0; j <= n; j++) {
				a[i][j] -= s[i];
			}
		}

		// For each cycle, we need to solve at least
		// one level in it, which at the least costs
		// the minimum a[i][n] for all i in the cycle.
		// Thus, we add that value to the baseline and
		// subtract it from all other values in the cycle,
		// so that if we finally obtain the highest item
		// we can solve all the rest for free.
		for(int i = 0; i < n; i++) {
			if(root[i] != i) continue; // start at root
			if(x[i] == -1) continue; // not needed when we get the level for free anyway

			// Find the minimum
			long min = a[i][n];
			int j = i;
			do {
				min = Math.min(min, a[j][n]);
				j = x[j];
			} while(j != i);

			// Add to baseline and subtract from cycle.
			// Note that this is still O(n^2) since the
			// inner loop is triggered for each level only
			// once.
			baseline += min;
			j = i;
			do {
				for(int k = 0; k <= n; k++)
					a[j][k] -= min;
				j = x[j];
			} while(j != i);
		}

		// Now the cheapest way to solve level i with item j
		// c[i][j] is the minimum of a[i][j] and c[x[i]][j],
		// where we should be careful with cycles.
		c = new long[n][n+1];
		done2 = new boolean[n][n+1];
		for(int i = 0; i < n; i++) {
			if(root[i] != i) continue; // start at root
			if(x[i] == -1) continue;

			for(int j = 0; j <= n; j++) {
				// Find the minimum
				long min = a[i][j];
				int k = i;
				do {
					min = Math.min(min, a[k][j]);
					k = x[k];
				} while(k != i);

				// We only set it for the root, the rest
				// will be done with the recursive calls.
				done2[i][j] = true;
				c[i][j] = min;
			}
		}
		for(int i = 0; i < n; i++)
			for(int j = 0; j <= n; j++)
				cheapest(i,j);

		// dp[j] is the the cheapest way of reaching level
		// n when j is the best item we have so far.
		long[] dp = new long[n+1];
		dp[n] = 0;
		for(int j = n - 1; j >= 0; j--) {
			dp[j] = Long.MAX_VALUE / 3;
			for(int i = j; i < n; i++)
				dp[j] = Math.min(dp[j], c[i][j] + dp[i+1]);
		}

		// Finally print the answer
		System.out.println(baseline + dp[0]);
	}

	static int findRoot(int i) {
		if(done[i]) return root[i];
		done[i] = true;
		root[i] = i;
		return root[i] = (x[i] == -1 ? i : findRoot(x[i]));
	}

	static long cheapest(int i, int j) {
		if(done2[i][j]) return c[i][j];
		done2[i][j] = true;
		c[i][j] = a[i][j];
		return c[i][j] = (x[i] == -1 ? 0 : Math.min(c[i][j], cheapest(x[i], j)));
	}
}
