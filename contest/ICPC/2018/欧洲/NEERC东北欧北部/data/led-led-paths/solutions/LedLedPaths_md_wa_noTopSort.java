import java.io.*;
import java.util.*;

public class LedLedPaths_md_wa_noTopSort {
	private static final String COLORS = "RGB";
	
	ArrayList<Integer>[] nei;
	boolean[] mark;
	ArrayList<Integer> notTopSort = new ArrayList<>();
	
	void run() {
		int n = in.nextInt();
		int m = in.nextInt();
		nei = new ArrayList[n];
		for (int i = 0; i < n; i++) {
			nei[i] = new ArrayList<>();
		}
		int[] from = new int[m];
		int[] to = new int[m];
		for (int i = 0; i < m; i++) {
			from[i] = in.nextInt() - 1;
			to[i] = in.nextInt() - 1;
			nei[from[i]].add(to[i]);
		}
		mark = new boolean[n];
		for (int i = 0; i < n; i++) {
			notTopSort.add(i);
		}
		Collections.shuffle(notTopSort, new Random(566));
		int topSortIndex[] = new int[n];
		for (int i = 0; i < n; i++) {
			topSortIndex[notTopSort.get(i)] = i;
		}
		int p = (int) Math.ceil(Math.pow(n, 1.0 / COLORS.length()));
		for (int i = 0; i < m; i++) {
			int a = topSortIndex[from[i]];
			int b = topSortIndex[to[i]];
			int color = 0;
			while (a / p != b / p) {
				color++;
				a /= p;
				b /= p;
			}
			out.println(COLORS.charAt(color));
		}
	}
	
	static MyScanner in;
	static PrintWriter out;

	public static void main(String[] args) throws IOException {
		boolean stdStreams = true;
		String fileName = LedLedPaths_md_wa_noTopSort.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
		String inputFileName = fileName + ".in";
		String outputFileName = fileName + ".out";
		
		Locale.setDefault(Locale.US);
		BufferedReader br;
		if (stdStreams) {
			br = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);
		} else {
			br = new BufferedReader(new FileReader(inputFileName));
			out = new PrintWriter(outputFileName);
		}
		in = new MyScanner(br);
		int tests = 1;//in.nextInt();
		for (int test = 0; test < tests; test++) {
			//out.print("Case #" + (test + 1) + ": ");
			new LedLedPaths_md_wa_noTopSort().run();
		}
		br.close();
		out.close();
	}
	
	static class MyScanner {
		BufferedReader br;
		StringTokenizer st;

		MyScanner(BufferedReader br) {
			this.br = br;
		}
		
		void findToken() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
		}
		
		String next() {
			findToken();
			return st.nextToken();
		}
		
		int nextInt() {
			return Integer.parseInt(next());
		}
		
		long nextLong() {
			return Long.parseLong(next());
		}
		
		double nextDouble() {
			return Double.parseDouble(next());
		}
	}
}
