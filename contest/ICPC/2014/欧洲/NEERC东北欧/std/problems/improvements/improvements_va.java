/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem I. Improvements                                        */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Vitaliy Aksenov                          */
/******************************************************************/

import java.io.*;
import java.util.*;

public class improvements_va {
    public static void main(String[] args) {
        new improvements_va().run();
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public class Tree {
        int[] tree;

        public Tree(int n) {
            int k = 1;
            while (k < n)
                k *= 2;
            tree = new int[2 * k];
        }

        public void update(int v, int x) {
            v += tree.length / 2;
            tree[v] = Math.max(x, tree[v]);
            v /= 2;
            while (v > 0) {
                tree[v] = Math.max(tree[2 * v], tree[2 * v + 1]);
                v /= 2;
            }
        }

        public int get(int l, int r) {
            l += tree.length / 2;
            r += tree.length / 2;
            int max = 0;
            while (l <= r) {
                if (l % 2 == 1) {
                    max = Math.max(max, tree[l]);
                    l++;
                }
                if (r % 2 == 0) {
                    max = Math.max(max, tree[r]);
                    r--;
                }
                l /= 2;
                r /= 2;
            }
            return max;
        }

        public int get(int v) {
            return tree[v + tree.length / 2];
        }

        public String toString() {
            return Arrays.toString(Arrays.copyOfRange(tree, tree.length / 2,
                    tree.length));
        }
    }

    public int[] increasing(int[] a) {
        Tree tree = new Tree(a.length);
        int[] inc = new int[a.length];

        for (int i = 0; i < a.length; i++) {
            inc[i] = tree.get(0, a[i]) + 1;
            tree.update(a[i], inc[i]);
        }                       

        for (int i = 1; i < a.length; i++) {
            inc[i] = Math.max(inc[i], inc[i - 1]);
        }

        return inc;
    }

    public int[] decreasing(int[] a) {
        int[] b = new int[a.length];

        for (int i = 0; i < a.length; i++) {
            b[a.length - i - 1] = a[i];
        }

        int[] inc = increasing(b);
        int[] dec = new int[inc.length];
        for (int i = 0; i < inc.length; i++) {
            dec[inc.length - i - 1] = inc[i];
        }
        return dec;
    }

    public void solve() throws IOException {
        int n = nextInt();

        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[nextInt() - 1] = i;
        }

        int[] inc = increasing(a);
        int[] dec = decreasing(a);

        int ans = Math.max(dec[0], inc[a.length - 1]);
        for (int i = 0; i < a.length - 1; i++) {
            ans = Math.max(ans, inc[i] + dec[i + 1]);
        }

        out.println(ans);
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("improvements.in"));
            out = new PrintWriter("improvements.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}

