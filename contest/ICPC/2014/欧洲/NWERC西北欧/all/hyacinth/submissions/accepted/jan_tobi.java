// [NWERC'14] Double Edge, by Jan Kuipers (rewritten by Tobias Werth to java)

import java.util.*;
import java.io.*;

public class jan_tobi {

	public static ArrayList<ArrayList<Integer>> conn = new ArrayList<>();
	public static int next_freq;
	public static ArrayList<Integer> freq1 = new ArrayList<>();
	public static ArrayList<Integer> freq2 = new ArrayList<>();

	public static void solve(int n, int freq, int parent) {
		freq1.set(n, next_freq++);
		freq2.set(n, freq); 
		for (Integer j : conn.get(n)) {
			if (j == parent)
				continue;
			solve(j, freq1.get(n), n);
			int tmp = freq1.get(n);
			freq1.set(n, freq2.get(n));
			freq2.set(n, tmp);
		}
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		conn.ensureCapacity(N);
		freq1.ensureCapacity(N);
		freq2.ensureCapacity(N);
		for (int i = 0; i < N; i++) {
			conn.add(new ArrayList<Integer>());
			freq1.add(-1);
			freq2.add(-1);
		}
		for (int i=0; i<N-1; i++) {
			int a = sc.nextInt() - 1;
			int b = sc.nextInt() - 1;
			conn.get(a).add(b);
			conn.get(b).add(a);
		}
		if (N == 2) {
			System.out.println("0 1\n0 1");
		} else {
			next_freq = 1;
			solve(0, 0, -1);
			for (int i=0; i<N; i++) {
				System.out.println(freq1.get(i) + " " + freq2.get(i));
			}
		}
	}
}
