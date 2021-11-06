// Ported to Java by Per
import java.util.*;
import java.io.*;

class bjarki_bs {
    public static void main(String args[]) {
        Kattio io = new Kattio(System.in, System.out);
        int n = io.getInt();
        ArrayList<Integer> succ[] = new ArrayList[n], prec[] = new ArrayList[n];
        int len[] = new int[n];
        int lo = 0,
            hi = 0,
            res = -1;
        for (int i = 0; i < n; ++i) {
            succ[i] = new ArrayList<Integer>();
            prec[i] = new ArrayList<Integer>();
        }
        for (int i = 0; i < n; ++i) {
            len[i] = io.getInt();
            int cnt = io.getInt();
            lo = Math.max(lo, len[i]);
            hi = Math.max(hi, len[i]+n);
            for (int j = 0; j < cnt; ++j) {
                int x = io.getInt() - 1;
                succ[i].add(x);
                prec[x].add(i);
            }
        }

        while (lo <= hi) {
            int mx = (lo+hi)/2;
            ArrayList<Integer> pos[] = new ArrayList[n];
            int left[] = new int[n];
            for (int i = 0; i < n; ++i)
                pos[i] = new ArrayList<Integer>();
            for (int i = 0; i < n; ++i) {
                left[i] = prec[i].size();
                pos[Math.min(n-1, mx - len[i])].add(i);
            }

            TreeSet<Integer> waiting = new TreeSet<Integer>(), ready = new TreeSet<Integer>();
            boolean ok = true;
            for (int i = n-1; i >= 0; i--) {
                for (int x: pos[i]) {
                    if (left[x] == 0) {
                        ready.add(x);
                    } else {
                        waiting.add(x);
                    }
                }
                if (ready.isEmpty()) {
                    ok = false;
                    break;
                }
                int cur = ready.pollFirst();
                for (int x: succ[cur]) {
                    if (--left[x] == 0 && waiting.remove(x)) {
                        ready.add(x);
                    }
                }
            }
            if (ok) {
                res = mx;
                hi = mx-1;
            } else {
                lo = mx+1;
            }
        }

        io.println(res);
        io.flush();

    }
}

/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * Kattio io = new Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */

class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}
