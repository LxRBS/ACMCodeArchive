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

    // Returns random string of length $len$, consists of letters from $alpha$.
    String randString(int len, String alpha) {
        StringBuilder ans = new StringBuilder();
        int k = alpha.length();
        for (int i = 0; i < len; i++) {
            ans.append(alpha.charAt(rand.nextInt(k)));
        }
        return ans.toString();
    }

    long rand(long l, long r) {
        return l + (rand.nextLong() >>> 1) % (r - l + 1);
    }

    int rand(int l, int r) {
        return l + rand.nextInt(r - l + 1);
    }

    final int MAXN = 1000;
    final int MAXK = 1000000000;

    // Generates random test with string of length $n$,
    // $as$ different letters, and given $k$.
    void genTest(int n, int as, int k) {
        String alph = genAlpha(as);
        printTest(k, randString(n, alph));
    }

    final String ALPHA = "abcdefghijklmnopqrstuvwxyz";

    // Returns random set of $as$ letters.
    private String genAlpha(int as) {
        ArrayList<Character> al = new ArrayList<Character>();
        for (char c : ALPHA.toCharArray()) {
            al.add(c);
        }
        Collections.shuffle(al, rand);
        String alph = "";
        for (int i = 0; i < as; ++i) {
            alph += al.get(i);
        }
        return alph;
    }


    public void gen() throws IOException {
        printTest(7, "abba");
        printTest(42, "a");
        genTest(1, rand(1, 5), rand(1, 100));
        for (int i = 0; i < 10; ++i) {
            genTest(rand(2, 10), rand(1, 5), rand(1, 100));
            genTest2(rand(2, 10), rand(2, 10), rand(1, 5), rand(1, 100));
        }
        for (int i = 0; i < 10; ++i) {
            genTest(rand(1, MAXN), rand(1, 26), rand(1, MAXK));
            genTest2(rand(1, MAXN), MAXN / rand(1, MAXN), rand(1, 26), rand(1, MAXK));
        }
        genTest(MAXN, 1, MAXK);
        genTest(MAXN, 26, MAXK);
        genTest2(MAXN, 2, 2, MAXK);
        genTest2(MAXN, 5, 3, MAXK);
        genTest2(MAXN, MAXN, 26, MAXK);
        genTest3(MAXN, 26, MAXK);
        printTest(42, "aa");
    }

    private void genTest2(int maxn, int maxp, int maxc, int k) {
        maxp = Math.min(maxp, maxn);
        String alph = genAlpha(maxc);
        int q = 0;
        String s = "" + alph.charAt(q);
        while (true) {
            q = (q + 1) % maxc;
            int d = 1;
            while ((s.length() + 1) * (d + 1) <= maxp && rand.nextBoolean()) d++;
            String ss = "";
            for (int i = 0; i < d; i++) {
                ss += s + alph.charAt(q);
            }
            if (ss.length() > maxp) {
                break;
            } else {
                s = ss;
            }
        }
        String ss = "";
        while ((ss + s).length() <= maxn) ss += s;
        s = ss;
        printTest(k, s);
    }

    private void printTest(int k, String s) {
        if (s.length() > k) s = s.substring(0, k);
//        int n = s.length();
//        int[] p = new int[n + 1];
//        p[0] = -1;
//        for (int i = 1; i <= n; i++) {
//            int q = p[i - 1];
//            while (q >= 0 && s.charAt(q) != s.charAt(i - 1)) q = p[q];
//            p[i] = q + 1;
//        }
//        int pp = n % (n - p[n]) == 0 ? (n - p[n]) : n;
//        System.out.println(n + " " + p[n] + " " + pp);
        open();
        out.println(s);
        out.println(k);
        close();
    }

    private void genTest3(int maxn, int maxc, int k) {
        String alph = genAlpha(maxc);
        int q = 0;
        String s = "" + alph.charAt(q);
        while (true) {
            q = (q + 1) % maxc;
            int d = 1;
            while ((s.length() + 1) * (d + 1) <= maxn && rand.nextBoolean()) d++;
            String ss = "";
            for (int i = 0; i < d; i++) {
                ss += s + alph.charAt(q);
            }
            if (ss.length() > maxn) {
                s = ss.substring(0, maxn);
                break;
            } else {
                s = ss;
            }
        }
        printTest(k, s);
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