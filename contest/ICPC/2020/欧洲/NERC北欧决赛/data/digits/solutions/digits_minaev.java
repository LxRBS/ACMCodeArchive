import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class digits_minaev {
    FastScanner in;
    PrintWriter out;

    final int DIGITS = 10;

    List<Number>[] numbers;

    List<Integer> getNumbers(int[] use, int[] pos) {
        List<Integer> res = new ArrayList<>();
        for (int i = 0; i < use.length; i++) {
            List<Number> cur = numbers[use[i]];
            for (int j = pos[i]; j < cur.size(); j++) {
                res.add(cur.get(j).id + 1);
            }
        }
        return res;
    }

    int d;
    int[] a;

    List<Integer> slow(int[] a, int d) {
        int n = a.length;
        BigInteger best = BigInteger.ZERO;
        List<Integer> bestRes = null;
        for (int mask = 1; mask < 1 << a.length; mask++) {
            BigInteger cur = BigInteger.ONE;
            List<Integer> curRes = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if (((1 << i) & mask) != 0) {
                    cur = cur.multiply(BigInteger.valueOf(a[i]));
                    curRes.add(a[i]);
                }
            }
            String s = cur.toString();
            if (s.charAt(s.length() - 1) == d + '0') {
                if (cur.compareTo(best) > 0) {
                    best = cur;
                    bestRes = curRes;
                }
            }
        }
        return bestRes;
    }

    BigInteger mul(List<Integer> r) {
        BigInteger res = BigInteger.ONE;
        for (int x : r) {
            res = res.multiply(BigInteger.valueOf(x));
        }
        return res;
    }

    void solve() {
        int n = in.nextInt();
        int d = in.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
        }
        List<Integer> r = solveXX(a, d);
        if (r == null) {
            out.println(-1);
        } else {
            out.println(r.size());
            for (int x : r) {
                out.print(x + " ");
            }
        }
    }

    void solve3() {
        Random rnd = new Random(123123);
        for (int it = 0; it < 123123; it++) {
            System.err.println("it = " + it);
            int n = 1 + rnd.nextInt(17);
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = 1 + rnd.nextInt(1000);
            }
            int d = rnd.nextInt(10);
            List<Integer> slow = slow(a, d);
            List<Integer> my = solveXX(a, d);
            if (my == null && slow != null) {
                System.err.println("slow = " + slow);
                System.err.println("a = " + Arrays.toString(a));
                System.err.println("d = " + d);
                solveXX(a, d);
                throw new AssertionError();
            }
            if (my == null && slow == null) {
                continue;
            }
            BigInteger slowBI = mul(slow);
            BigInteger myBI = mul(my);
            if (slowBI.compareTo(myBI) != 0) {
                System.err.println("my = " + myBI);
                System.err.println("slow = " + slowBI);
                System.err.println("a = " + Arrays.toString(a));
                System.err.println("d = " + d);
                throw new AssertionError();
            }
        }
    }

    List<Integer> solveXX(int[] a, int d) {
        int n = a.length;
        this.a = a;
        this.d = d;
//        a = new int[n];
//        d = in.nextInt();
        numbers = new List[DIGITS];
        for (int i = 0; i < numbers.length; i++) {
            numbers[i] = new ArrayList<>();
        }
        for (int i = 0; i < n; i++) {
            Number num = new Number(i, a[i]);
//            a[i] = num.value;
            numbers[num.value % 10].add(num);
        }
        for (int i = 0; i < numbers.length; i++) {
            Collections.sort(numbers[i]);
        }
        lastDigit = new int[DIGITS][];
        sum = new long[DIGITS][];
        for (int i = 0; i < DIGITS; i++) {
            lastDigit[i] = new int[numbers[i].size() + 1];
            sum[i] = new long[numbers[i].size() + 1];
            lastDigit[i][lastDigit[i].length - 1] = 1;
            for (int j = lastDigit[i].length - 2; j >= 0; j--) {
                lastDigit[i][j] = (lastDigit[i][j + 1] * i) % 10;
            }
            sum[i][0] = 1;
            for (int j = 0; j < numbers[i].size(); j++) {
                sum[i][j + 1] = sum[i][j] * numbers[i].get(j).value;
            }
        }
        int[] allNumbers = new int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        if (d == 0) {
            int expected = getLastDigit(allNumbers);
            if (expected == 0) {
                List<Integer> res = new ArrayList<>();
                for (int x = 1; x <= n; x++) {
                    res.add(x);
                }
                return printAns(res);
            } else {
                return null;
            }
        }
        int[] oddNumbers = new int[]{1, 3, 5, 7, 9};
        if (d == 5) {
            int expected = getLastDigit(oddNumbers);
            if (expected == d) {
                List<Integer> res = getNumbers(new int[]{1, 3, 5, 7, 9}, new int[]{0, 0, 0, 0, 0});
                return printAns(res);
            } else {
                return null;
            }
        }
        if (d == 1 || d == 3 || d == 7 || d == 9) {
            return solve(new int[]{1, 3, 7, 9}, d);
        } else {
            return solve(new int[]{1, 2, 3, 4, 6, 7, 8, 9}, d);
        }
    }

    List<Integer> solve(int[] canUse, int needDigit) {
        int n = canUse.length;
        long bestAns = Long.MAX_VALUE;
        int bestMask = 0;
        for (int mask = 0; mask < (1 << (2 * n)); mask++) {
            long curAns = 1;
            int curDigit = 1;
            boolean ok = true;
            boolean atLeastOne = false;
            for (int i = 0; i < n; i++) {
                int d = canUse[i];
                int from = (mask >> (i * 2)) & 3;
                if (sum[d].length <= from) {
                    ok = false;
                    break;
                }
                if (curAns * 1.0 * sum[d][from] > 1.1e18) {
                    ok = false;
                    break;
                }
                if (from != sum[d].length - 1) {
                    atLeastOne = true;
                }
                curAns *= sum[d][from];
                curDigit = (curDigit * lastDigit[d][from]) % 10;
            }
            if (ok && atLeastOne) {
                if (curAns < bestAns && curDigit == needDigit) {
                    bestAns = curAns;
                    bestMask = mask;
                }
            }
        }
        if (bestAns == Long.MAX_VALUE) {
            return null;
        } else {
            List<Integer> res = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                int d = canUse[i];
                int from = (bestMask >> (i * 2)) & 3;
                for (int j = from; j < numbers[d].size(); j++) {
                    res.add(numbers[d].get(j).id + 1);
                }
            }
            return printAns(res);
        }
    }

    List<Integer> printAns(List<Integer> res) {
        int exp = 1;
//        out.println(res.size());
        List<Integer> ff = new ArrayList<>();
        for (int x : res) {
//            out.print(a[x - 1] + " ");
            ff.add(a[x - 1]);
            exp = (exp * a[x - 1]) % 10;
        }
        if (exp != d) {
            throw new AssertionError();
        }
        return ff;
//        out.println();
    }


    int getLastDigit(int[] use) {
        int r = 1;
        for (int x : use) {
            r = (r * lastDigit[x][0]) % 10;
        }
        return r;
    }

    int[][] lastDigit;
    long[][] sum;

    class Number implements Comparable<Number> {
        int id;
        int value;

        public Number(int id, int value) {
            this.id = id;
            this.value = value;
        }

        @Override
        public int compareTo(Number o) {
            return Integer.compare(value, o.value);
        }
    }

    void run() {
        try {
            in = new FastScanner(new File("D.in"));
            out = new PrintWriter(new File("D.out"));

            solve();

            out.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    void runIO() {

        in = new FastScanner(System.in);
        out = new PrintWriter(System.out);

        solve();

        out.close();
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public FastScanner(InputStream f) {
            br = new BufferedReader(new InputStreamReader(f));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                String s = null;
                try {
                    s = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (s == null)
                    return null;
                st = new StringTokenizer(s);
            }
            return st.nextToken();
        }

        boolean hasMoreTokens() {
            while (st == null || !st.hasMoreTokens()) {
                String s = null;
                try {
                    s = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (s == null)
                    return false;
                st = new StringTokenizer(s);
            }
            return true;
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }
    }

    public static void main(String[] args) {
        new digits_minaev().runIO();
    }
}