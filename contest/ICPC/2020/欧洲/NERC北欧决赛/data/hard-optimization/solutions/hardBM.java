// by Borys Minaiev

import java.io.*;
import java.util.*;

public class hardBM {
    FastScanner in;
    PrintWriter out;

    void gen(List<Segment> res, int from, int to, Random rnd, int n) {
        if (n == 0 || from >= to) {
            return;
        }
        from = from + rnd.nextInt(to - from);
        to = from + rnd.nextInt(to - from);
        if (from >= to) {
            return;
        }

        res.add(new Segment(from, to, -1));
        from += 1;
        to -= 1;
        if (n > 1 && to > from) {
            int mid = from + rnd.nextInt(to - from);
            gen(res, from, mid, rnd, n / 2);
            gen(res, mid + 1, to, rnd, n - (n / 2) - 1);
        }
    }

    void solve() {
        int n = in.nextInt();
        List<Segment> segs = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            segs.add(new Segment(in.nextInt(), in.nextInt(), i));
        }
        solve123(segs);
    }

    void solve123() {
        final int MAX_C = 20000;
        Random rnd = new Random(123);
        for (int it = 0; it < 123123; it++) {
            System.err.println("it = " + it);
            int n = 1 + rnd.nextInt(20);
            List<Segment> segs = new ArrayList<>();
            gen(segs, 0, MAX_C, rnd, n);
            for (int i = 0; i < segs.size(); i++) {
                segs.get(i).id = i;
            }
            System.err.println("real n = " + segs.size());
            solve123(segs);
        }
    }

    void solve123(List<Segment> segments) {
        int n = segments.size();
//        Segment[] segments = new Segment[n];
//        for (int i = 0; i < n; i++) {
//            segments[i] = new Segment(in.nextInt(), in.nextInt(), i);
//        }
        Collections.sort(segments);
        List<Segment> stack = new ArrayList<>();
        List<Segment> roots = new ArrayList<>();
        for (Segment s : segments) {
            while (stack.size() > 0 && stack.get(stack.size() - 1).right < s.left) {
                stack.remove(stack.size() - 1);
            }
            if (stack.size() > 0) {
                stack.get(stack.size() - 1).children.add(s);
            } else {
                roots.add(s);
            }
            stack.add(s);
        }
        int expectedAns = 0;
        for (Segment s : roots) {
            int[] tmp = solve(s);
            expectedAns += tmp[0];
            recoverSolve(s, null, null);
        }
        int[] ansL = new int[n];
        int[] ansR = new int[n];
        int res = 0;
        for (Segment s : segments) {
            ansL[s.id] = s.ansLeft;
            ansR[s.id] = s.ansRight;
            res += ansR[s.id] - ansL[s.id];
            if (ansL[s.id] >= ansR[s.id]) {
                throw new AssertionError(ansL[s.id] + " " + ansR[s.id]);
            }
            if (s.ansLeft < s.left) {
                throw new AssertionError();
            }
            if (s.ansRight > s.right) {
                throw new AssertionError();
            }
        }
        if (res != expectedAns) {
            System.err.println("expectedAns = " + expectedAns);
            System.err.println("my sum = " + res);
            for (Segment s : segments) {
                System.err.println(s);
            }
            throw new AssertionError();
        }
        out.println(res);
        for (int i = 0; i < n; i++) {
            out.println(ansL[i] + " " + ansR[i]);
        }
    }

    void recoverSolve(Segment s, Segment fromLeft, Segment fromRight) {
        if (fromLeft != null) {
            fromLeft.ansRight = s.left;
        }
        if (fromRight != null) {
            fromRight.ansLeft = s.right;
        }
        if (s.children.size() == 0) {
            s.ansLeft = s.left;
            s.ansRight = s.right;
        } else {
            int mask = 0;
            if (fromLeft != null) {
                mask |= 1;
            }
            if (fromRight != null) {
                mask |= 2;
            }
            int myPos = s.cachedRes[mask + 4];
            s.ansLeft = s.left;
            s.ansRight = s.right;
            if (myPos < s.children.size()) {
                s.ansRight = s.children.get(myPos).left;
            }
            if (myPos > 0) {
                s.ansLeft = s.children.get(myPos - 1).right;
            }
            for (int i = 0; i < s.children.size(); i++) {
                Segment goLeft = null;
                Segment goRight = null;
                if (i == 0) {
                    goLeft = fromLeft;
                }
                if (i == s.children.size() - 1) {
                    goRight = fromRight;
                }
                if (myPos == i) {
                    goLeft = s;
                }
                if (myPos == i + 1) {
                    goRight = s;
                }
                recoverSolve(s.children.get(i), goLeft, goRight);
            }
        }
    }

    // {is somebody from left?; is somebody from right?}
    int[] solve(Segment s) {
        int[] res = new int[8];
        if (s.children.isEmpty()) {
            int len = s.right - s.left;
            res[0] = res[1] = res[2] = res[3] = len;
        } else {
            int[][] dps = new int[s.children.size()][];
            int[] nowMasks = new int[s.children.size()];
            int sum0 = 0;
            for (int i = 0; i < s.children.size(); i++) {
                dps[i] = solve(s.children.get(i));
                sum0 += dps[i][0];
            }
            for (int existLeft = 0; existLeft < 2; existLeft++) {
                for (int existRight = 0; existRight < 2; existRight++) {
                    int mask = existLeft | (existRight << 1);
                    int curSum = sum0;
                    Arrays.fill(nowMasks, 0);
                    if (s.children.size() == 1) {
                        curSum -= dps[0][0];
                        curSum += dps[0][mask];
                        nowMasks[0] = mask;
                    } else {
                        if (existLeft == 1) {
                            curSum -= dps[0][0];
                            curSum += dps[0][1];
                            nowMasks[0] = 1;
                        }
                        if (existRight == 1) {
                            curSum -= dps[dps.length - 1][0];
                            curSum += dps[dps.length - 1][2];
                            nowMasks[dps.length - 1] = 2;
                        }
                    }
                    for (int beforePos = 0; beforePos <= s.children.size(); beforePos++) {
                        int from = s.left, to = s.right;
                        if (beforePos > 0) {
                            from = s.children.get(beforePos - 1).right;
                        }
                        if (beforePos < s.children.size()) {
                            to = s.children.get(beforePos).left;
                        }
                        int nextSum = curSum + (to - from);
                        if (beforePos > 0) {
                            nextSum -= dps[beforePos - 1][nowMasks[beforePos - 1]];
                            nextSum += dps[beforePos - 1][nowMasks[beforePos - 1] | 2];
                        }
                        if (beforePos < s.children.size()) {
                            nextSum -= dps[beforePos][nowMasks[beforePos]];
                            nextSum += dps[beforePos][nowMasks[beforePos] | 1];
                        }
                        if (beforePos != 0 && existLeft == 1) {
                            nextSum += s.children.get(0).left - s.left;
                        }
                        if (beforePos != s.children.size() && existRight == 1) {
                            nextSum += s.right - s.children.get(s.children.size() - 1).right;
                        }
                        if (nextSum >= res[mask]) {
                            res[mask] = nextSum;
                            res[mask + 4] = beforePos;
                        }
                    }
                }
            }
        }
        s.cachedRes = res;
        return res;
    }

    class Segment implements Comparable<Segment> {
        int left, right;
        int ansLeft = -1, ansRight = -1;
        int id;
        List<Segment> children;
        int[] cachedRes;

        public Segment(int left, int right, int id) {
            this.left = left;
            this.right = right;
            this.id = id;
            children = new ArrayList<>();
        }

        @Override
        public String toString() {
            return "Segment{" +
                    "left=" + left +
                    ", right=" + right +
                    ", ansLeft=" + ansLeft +
                    ", ansRight=" + ansRight +
                    '}';
        }

        @Override
        public int compareTo(Segment o) {
            return Integer.compare(left, o.left);
        }
    }

    void run() {
        try {
            in = new FastScanner(new File("H.in"));
            out = new PrintWriter(new File("H.out"));

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
        new hardBM().runIO();
    }
}