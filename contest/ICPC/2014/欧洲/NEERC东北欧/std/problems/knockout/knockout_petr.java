/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem K. Knockout Racing                                     */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
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
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class knockout_petr {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("knockout.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("knockout.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		Knockout solver = new Knockout();
		solver.solve(1, in, out);
		out.close();
	}
}

class Knockout {
    public void solve(int testNumber, InputReader in, PrintWriter out) {
        int n = in.nextInt();
        int m = in.nextInt();
        int[] a = new int[n];
        int[] b = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = in.nextInt();
            b[i] = in.nextInt();
        }
        for (int i = 0; i < m; ++i) {
            int x = in.nextInt();
            int y = in.nextInt();
            int t = in.nextInt();
            int res = 0;
            for (int j = 0; j < n; ++j) {
                if (a[j] == b[j]) {
                    if (x <= a[j] && a[j] <= y)
                        ++res;
                } else {
                    int per = t % (2 * Math.abs(a[j] - b[j]));
                    if (per > Math.abs(a[j] - b[j])) per = 2 * Math.abs(a[j] - b[j]) - per;
                    int pos = a[j] + sign(b[j] - a[j]) * per;
                    if (x <= pos && pos <= y)
                        ++res;
                }
            }
            out.println(res);
        }
    }

    private int sign(int i) {
        if (i > 0) return 1; else return -1;
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

}


