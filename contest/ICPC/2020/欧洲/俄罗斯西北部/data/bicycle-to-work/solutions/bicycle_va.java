import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * Created by vaksenov on 10.11.2020.
 */
public class bicycle_va {
    public static void main(String[] args) {
        new bicycle_va().run();
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
        int a = nextInt();
        int x = nextInt();
        int b = nextInt();
        int y = nextInt();
        int T = nextInt();

        int first = a + 21 * Math.max(T - 30, 0) * x;
        int second = b + 21 * Math.max(T - 45, 0) * y;
        out.println(first + " " + second);
    }

    public void run() {
        try {
            br = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
