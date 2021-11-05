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
/* Author                Vitaliy Aksenov                          */
/******************************************************************/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * User: Aksenov Vitaly
 * Date: 16.18.14
 * Time: 19:35
 */
public class knockout_va_re {
    public static void main(String[] args) {
        new knockout_va_re().run();
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        int[] l = new int[n];
        int[] r = new int[n];
        for (int i = 0; i < n; i++) {
            l[i] = nextInt();
            r[i] = nextInt();
        }

        for (int i = 0; i < m; i++) {
            int x = nextInt();
            int y = nextInt();
            int t = nextInt();
            int total = 0;
            for (int j = 0; j < n; j++) {
                if (l[j] == r[j] && x <= l[j] && l[j] <= y) {
                    total++;
                    continue;
                }
                int tt = t % (2 * (r[j] - l[j]));
                int z = tt < r[j] - l[j] ? l[j] + tt : r[j] - (tt - (r[j] - l[j]));
                if (x <= z && z <= y) {
                    total++;
                }
            }
            out.println(total);
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("knockout.in"));
            out = new PrintWriter("knockout.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}

