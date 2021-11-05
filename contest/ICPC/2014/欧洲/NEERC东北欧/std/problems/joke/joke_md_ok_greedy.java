/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem J. Jokewithpermutation                                 */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Maxim Babenko                            */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Mikhail Dvorkin                          */
/******************************************************************/

import java.awt.Point;
import java.io.*;
import java.util.*;

public class joke_md_ok_greedy {
    public static int fitness(String s) {
        for (int seed = 1; ; ++seed) {
            int[] rv = solve(s, new Random(seed));
            if (rv != null) {
                return seed;
            }
        }
    }
	static int[] solve(String s, Random r) {
		StringBuilder sb = new StringBuilder();
		int n = 0;
		while (sb.length() < s.length()) {
			n++;
			sb.append(n);
		}
		boolean[] used = new boolean[s.length()];
		boolean[] mark = new boolean[n + 1];
		int[] starts = new int[s.length()];
		Arrays.fill(starts, -1);
		for (int iter = 0; iter < n; iter++) {
			int bestVar = s.length() + 1;
			List<Point> best = new ArrayList<>();
			for (int i = 1; i <= n; i++) {
				if (mark[i]) {
					continue;
				}
				int var = 0;
				String t = "" + i;
				List<Point> points = new ArrayList<>();
				jLoop:
				for (int j = 0; j + t.length() <= s.length(); j++) {
					for (int k = 0; k < t.length(); k++) {
						if (used[j + k]) {
							continue jLoop;
						}
					}
					if (s.substring(j, j + t.length()).equals(t)) {
						var++;
						points.add(new Point(i, j));
					}
				}
				if (var < bestVar) {
					bestVar = var;
					best = points;
				} else if (var == bestVar) {
					best.addAll(points);
				}
			}
			if (best.isEmpty()) {
				return null;
			}
			Point selected = best.get(r.nextInt(best.size()));
			int i = selected.x;
			int j = selected.y;
			mark[i] = true;
			starts[j] = i;
			for (int k = 0; k < ("" + i).length(); k++) {
				used[j + k] = true;
			}
		}
		int[] ans = new int[n];
		int j = 0;
		for (int i : starts) {
			if (i == -1) {
				continue;
			}
			ans[j++] = i;
		}
		return ans;
	}
	
	private static String fileName = joke_md_ok_greedy.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;
	
	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new File(inputFileName));
		out = new PrintWriter(outputFileName);
		String s = in.next();
		int[] p = null;
		for (int seed = 0; p == null; seed++) {
			p = solve(s, new Random(seed));
		}
		out.println(Arrays.toString(p).replaceAll("[^\\d\\s]", ""));
		in.close();
		out.close();
	}
}

