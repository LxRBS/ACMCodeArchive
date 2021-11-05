/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem F. Filter                                              */
/*                                                                */
/* Original idea         Roman Elizarov                           */
/* Problem statement     Roman Elizarov                           */
/* Test set              Roman Elizarov                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Petr Mitrichev                           */
/******************************************************************/

import java.io.InputStreamReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.util.StringTokenizer;
import java.math.BigInteger;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class filter_petr {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("filter.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("filter.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		Filter solver = new Filter();
		solver.solve(1, in, out);
		out.close();
	}
}

class Filter {
    public void solve(int testNumber, InputReader in, PrintWriter out) {
        int m = in.nextInt();
        int f = in.nextInt();
        long[] a = new long[f];
        for (int i = 0; i < f; ++i) a[i] = in.nextLong();
        int n = in.nextInt();
        BigInteger[] data = new BigInteger[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new BigInteger(reverse(in.next()), 16);
        }
        int q = in.nextInt();
        boolean[] res = new boolean[n];
        for (int i = 0; i < q; ++i) {
            long u = in.nextLong();
            BigInteger cur = BigInteger.ZERO;
            for (int j = 0; j < f; ++j) {
                cur = cur.setBit((int) (u * a[j] % m));
            }
            for (int j = 0; j < n; ++j) {
                if (data[j].and(cur).equals(cur)) {
                    res[j] = true;
                }
            }
        }
        int cnt = 0;
        for (boolean tmp : res) if (tmp) ++cnt;
        out.print(cnt);
        for (int i = 0; i < n; ++i) if (res[i]) out.print(" " + i);
        out.println();
    }

    private String reverse(String a) {
        StringBuilder b = new StringBuilder(a);
        b.reverse();
        return b.toString();
    }
}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

    public long nextLong() {
        return Long.parseLong(next());
    }

}


