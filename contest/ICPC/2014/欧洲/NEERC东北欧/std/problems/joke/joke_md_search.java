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

public class joke_md_search {
	static final int MAX_DIGITS = 2;

    static int callCount = 0;
    public static int fitness(String s) {
        callCount = 0;
        int[] v = solve(s);
        StringBuilder answer = new StringBuilder();
        for (int i : v) answer.append(i);
        if (!s.equals(answer.toString())) {
            return Integer.MAX_VALUE;
        } else {
            return callCount;
        }
    }

	static int[] solve(String s) {
		StringBuilder sb = new StringBuilder();
		int n = 0;
		while (sb.length() < s.length()) {
			n++;
			sb.append(n);
		}
		return search(s, 0, 0, new boolean[n], new int[n]);
	}

	static int[] search(String s, int index, int set, boolean[] mark, int[] p) {
		if (index == s.length()) {
			return p;
		}
		if (s.charAt(index) == '0') {
			return null;
		}
		++callCount;
		for (int i = Math.min(MAX_DIGITS, s.length() - index); i >= 1; i--) {
			int x = Integer.parseInt(s.substring(index, index + i));
			if (x > mark.length) {
				continue;
			}
			if (mark[x - 1]) {
				continue;
			}
			mark[x - 1] = true;
			p[set] = x;
			int[] found = search(s, index + i, set + 1, mark, p);
			if (found != null) {
				return found;
			}
			mark[x - 1] = false;
		}
		return null;
	}

	private static String fileName = joke_md_search.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
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

