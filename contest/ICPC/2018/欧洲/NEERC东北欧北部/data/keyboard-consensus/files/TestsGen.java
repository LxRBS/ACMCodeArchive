import java.io.*;
import java.util.*;

public class TestsGen implements Runnable {
    public static void main(String[] args) {
        new Thread(new TestsGen()).start();
    }

    PrintWriter out;

    Random rand = new Random(6439586L);

    static int I = 1;

    static String getName(int i) {
        return "" + i;
    }

    void open() {
        try {
            System.out.println("Generating test " + I);
            out = new PrintWriter(getName(I));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    void close() {
        out.close();
        I++;
    }

    void printTest(int[] a, int[] b) {
        open();
        out.println(a.length);
        for (int i = 0; i < a.length; i++) {
            if (i > 0) out.print(" ");
            out.print(a[i] + 1);
        }
        out.println();
        for (int i = 0; i < b.length; i++) {
            if (i > 0) out.print(" ");
            out.print(b[i] + 1);
        }
        out.println();
        close();
    }

    long rand(long l, long r) {
        return l + (rand.nextLong() >>> 1) % (r - l + 1);
    }

    int rand(int l, int r) {
        return l + rand.nextInt(r - l + 1);
    }

    final int MAXN = 100;

    public void gen(int i, int[] p, boolean[] z) {
        int n = z.length;
        if (i == n) {
            int[] a = new int[n];
            for (int x = 0; x < n; x++) {
                int y = rand(0, x);
                a[x] = a[y];
                a[y] = x;
            }
            int[] b = new int[n];
            for (int x = 0; x < n; x++) {
                b[x] = a[p[x]];
            }
            printTest(a, b);
        }
        for (int x = 0; x < n; x++) {
            if (!z[x]) {
                z[x] = true;
                p[i] = x;
                gen(i + 1, p, z);
                z[x] = false;
            }
        }
    }

    public void gen() throws IOException {
        printTest(new int[]{0, 1, 2, 3, 4}, new int[]{4, 3, 2, 1, 0});
        printTest(new int[]{0, 1, 2, 3}, new int[]{0, 2, 1, 3});
        printTest(new int[]{2, 0, 1}, new int[]{0, 2, 1});
        printTest(new int[]{3, 0, 2, 1}, new int[]{0, 2, 3, 1});

        for (int n = 2; n <= 4; n++) {
            int[] p = new int[n];
            boolean[] z = new boolean[n];
            gen(0, p, z);
        }
        for (int i = 2; i < 10; ++i) {
            genRandomTest(i + 1);
        }
        for (int i = 0; i < 10; ++i) {
            genRandomTest(rand(10, MAXN));
            genRandomAntigreedyTest(rand(10, MAXN));
        }
        genRandomTest(MAXN);
        genRandomTest(MAXN - 1);
        genRandomAntigreedyTest(MAXN - 1);
    }

    private void genRandomAntigreedyTest(int n) {
        if (n % 2 == 0) n--;
        int[] pa, pb;
        do {
            pa = perm(n);
            pb = perm(n);
        } while (solve1(pa, pb) == solve2(pa, pb));
        printTest(pa, pb);
    }

    private int solve1(int[] pa, int[] pb) {
        boolean[] z = new boolean[pa.length];
        return solve(pa, pb, z);
    }

    private int solve2(int[] pa, int[] pb) {
        boolean[] z = new boolean[pa.length];
        int res1 = solve(pa, pb, z);
        Arrays.fill(z, false);
        z[res1] = true;
        int res2 = solve(pb, pa, z);
        for (int i = 0; i < pa.length; i++) {
            if (pa[i] == res1 || pa[i] == res2) {
                return pa[i];
            }
        }
        return -1;
    }

    private int solve(int[] pa, int[] pb, boolean[] z) {
        int ia = pa.length - 1;
        int ib = pb.length - 1;
        int n = 0;
        for (int i = 0; i < z.length; i++) if (!z[i]) n++;
        for (int i = 0; i < n - 1; i++) {
            if (i % 2 == 0) {
                while (z[pa[ia]]) ia--;
                z[pa[ia]] = true;
            } else {
                while (z[pb[ib]]) ib--;
                z[pb[ib]] = true;
            }
        }
        for (int i = 0; i < z.length; i++) {
            if (!z[i]) return i;
        }
        return -1;
    }


    private void genRandomTest(int n) {
        printTest(perm(n), perm(n));
    }

    private int[] perm(int n) {
        int[] res = new int[n];
        for (int i = 0; i < n; i++) {
            int j = rand(0, i);
            res[i] = res[j];
            res[j] = i;
        }
        return res;
    }

    void myAssert(boolean e) {
        if (!e) {
            throw new Error("Assertion failed");
        }
    }

    public void run() {
        try {
            gen();
        } catch (Throwable e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
}