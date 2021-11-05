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

import java.io.*;
import java.util.*;

public class joke_md {
	static int[] a;
	static int n;
	static boolean[] single;
	static int[] ans;
	static int[] temp;
	static int callCount;
	
	static int[] solve(String s) {
		a = new int[s.length()];
		for (int i = 0; i < s.length(); i++) {
			a[i] = s.charAt(i) - '0';
		}
		StringBuilder sb = new StringBuilder();
		n = 0;
		while (sb.length() < a.length) {
			n++;
			sb.append(n);
		}
		single = new boolean[a.length];
		ans = new int[n];
		temp = new int[n];
		return search(9);
	}

    public static int fitness(String s) {
        callCount = 0;
        solve(s);
        return callCount;
    }

	static int[] search(int d) {
	    ++callCount;
		if (d == 0) {
			for (int i = 0, j = 0; i < a.length; i++) {
				if (single[i]) {
					ans[j++] = a[i];
					continue;
				}
				if (i + 1 == a.length || single[i + 1]) {
					return null;
				}
				ans[j++] = 10 * a[i] + a[i + 1];
				i++;
			}
			System.arraycopy(ans, 0, temp, 0, n);
			Arrays.sort(temp);
			for (int i = 0; i < n; i++) {
				if (temp[i] != i + 1) {
					return null;
				}
			}
			return ans;
		}
		if (d > n) {
			return search(d - 1);
		}
		if (10 * d + 1 > n) { // d is never first digit except "d0"
			int[] count = new int[10];
			for (int i = 0; i < a.length; i++) {
				if (a[i] != d) {
					continue;
				}
				if (i + 1 < a.length && a[i + 1] == 0) {
					continue;
				}
				if (i == 0) {
					single[i] = true;
					int[] found = search(d - 1);
					if (found != null) {
						return found;
					}
					single[i] = false;
					return null;
				}
				count[a[i - 1]]++;
			}
			for (int i = 1; i < 10; i++) {
				if (10 * i + d <= n) {
					count[i]--;
				}
			}
			for (int i = 0; i < a.length; i++) {
				if (a[i] != d) {
					continue;
				}
				if (i + 1 < a.length && a[i + 1] == 0) {
					continue;
				}
				if (count[a[i - 1]] > 0) {
					single[i] = true;
					int[] found = search(d - 1);
					if (found != null) {
						return found;
					}
					single[i] = false;
				}
			}
			return null;
		}
		for (int i = 0; i < a.length; i++) {
			if (a[i] != d) {
				continue;
			}
			single[i] = true;
			int[] found = search(d - 1);
			if (found != null) {
				return found;
			}
			single[i] = false;
		}
		return null;
	}

	private static String fileName = joke_md.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;
	
	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new File(inputFileName));
		out = new PrintWriter(outputFileName);
		String s = in.next();
		int[] p = solve(s);
		out.println(Arrays.toString(p).replaceAll("[^\\d\\s]", ""));
		in.close();
		out.close();
	}
}

