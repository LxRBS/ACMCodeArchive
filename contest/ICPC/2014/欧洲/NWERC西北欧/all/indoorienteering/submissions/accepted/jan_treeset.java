import java.util.*;
import java.io.*;

public class jan_treeset {
	static int N;
	static long L;
	static long[][] d;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		L = sc.nextLong();
		d = new long[N][N];
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				d[i][j] = sc.nextLong();

		boolean possible = false;
		for (int center=1; center<N; center++) {
			for (int mask_left=0; mask_left<(1<<N); mask_left++) {
				if ((mask_left & (1<<0)) > 0) continue;
				if ((mask_left & (1<<center)) > 0) continue;
				if (bit_count(mask_left) != (N-2)/2)  continue;
				int mask_right = (1<<N) - 1 - mask_left - (1<<0) - (1<<center);
				Set<Long> distances_left = get_distances(0, mask_left, center);
				Set<Long> distances_right = get_distances(center, mask_right, 0);
				for (long it : distances_left) {
					if (distances_right.contains(L - it)) {
						possible = true;
					}
				}
			}
		}
		System.out.println(possible ? "possible" : "impossible");
	}

	public static int bit_count(int msk) {
		int cnt=0;
		while (msk > 0) {
			if ((msk & 1) > 0) cnt++;
			msk >>= 1;
		}
		return cnt;
	}

	public static Set<Long> get_distances(int start, int mask, int end) {
		Vector<Integer> x = new Vector<Integer>();
		Set<Long> distances = new TreeSet<Long>();
		if (mask == 0) {
			distances.add((long)d[start][end]);
			return distances;
		}
		for (int i=0; i<N; i++) {
			if ((mask & (1<<i)) > 0) x.add(i);
		}
		do {
			long dist = d[start][x.get(0)];
			for (int i=0; i+1<x.size(); i++) {
				dist += d[x.get(i)][x.get(i+1)];
			}
			dist += d[x.get(x.size()-1)][end];
			distances.add(dist);
		} while (next_permutation(x));
		return distances;
	}


	// Stolen and adapted http://codeforces.com/blog/entry/3980
	static boolean next_permutation(Vector<Integer> p) {
		for (int a = p.size() - 2; a >= 0; --a)
			if (p.get(a) < p.get(a + 1))
				for (int b = p.size() - 1;; --b)
					if (p.get(b) > p.get(a)) {
						int t = p.get(a);
						p.set(a, p.get(b));
						p.set(b, t);
						for (++a, b = p.size() - 1; a < b; ++a, --b) {
							t = p.get(a);
							p.set(a, p.get(b));
							p.set(b, t);
						}
						return true;
					}
		return false;
	}
}
