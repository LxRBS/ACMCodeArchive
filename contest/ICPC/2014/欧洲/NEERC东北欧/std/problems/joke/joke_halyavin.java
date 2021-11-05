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
/* Author                Andrey Halyavin                          */
/******************************************************************/

import java.util.List;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.util.StringTokenizer;
import java.io.InputStream;
import java.io.ByteArrayInputStream;
import java.io.StringWriter;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class joke_halyavin {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("joke.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("joke.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		Joke solver = new Joke();
		solver.solve(1, in, out);
		out.close();
	}
	public static int fitness(String s) {
	    InputReader in = new InputReader(new ByteArrayInputStream(s.getBytes()));
	    PrintWriter out = new PrintWriter(new StringWriter());
	    Joke solver = new Joke();
	    solver.solve(1, in, out);
	    return solver.count;
	}
}

class Joke {
    String s;
    int count = 0;

    public boolean rec(int pos, boolean[] stat, List<Integer> ans) {
        ++count;
        if (pos == s.length()) {
            return true;
        }
        int x = s.charAt(pos) - '0';
        if (x == 0) return false;
        if (stat[x] == false) {
            ans.add(x);
            stat[x] = true;
            if (rec(pos + 1, stat, ans)) return true;
            stat[x] = false;
            ans.remove(ans.size() - 1);
        }
        pos++;
        if (pos == s.length()) return false;
        x = x * 10 + s.charAt(pos) - '0';
        if (x >= stat.length || stat[x]) return false;
        ans.add(x);
        stat[x] = true;
        if(rec(pos + 1, stat, ans)) return true;
        stat[x] = false;
        ans.remove(ans.size() - 1);
        return false;
    }

    public void solve(int testNumber, InputReader in, PrintWriter out) {
        s = in.next();
        int n = 0;
        if (s.length() <= 9) {
            n = s.length();
        } else {
            n = 9 + (s.length() - 9) / 2;
        }
        boolean[] stat = new boolean[n + 1];
        List<Integer> ans = new ArrayList<>();
        rec(0, stat, ans);
        for (Integer i : ans) {
            out.print(i + " ");
        }
        out.println();
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

}


