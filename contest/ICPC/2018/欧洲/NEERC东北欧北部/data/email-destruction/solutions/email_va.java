import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.StringTokenizer;

/**
 * Created by Meepo on 9/30/2018.
 */
public class email_va {
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
        int k = nextInt();

        HashMap<String, Integer> maxSubject = new HashMap<>();
        for (int i = 0; i < k; i++) {
            String subject = br.readLine();
            int len = subject.lastIndexOf(" ") + 1;
            subject = subject.substring(len);
            final int total = len / 4 + 1;
            maxSubject.compute(subject, (sub, curr) -> curr == null ? total : Math.max(curr, total));
        }

        int atleast = 0;
        int maxChain = 0;
        for (int v : maxSubject.values()) {
            atleast += v;
            maxChain = Math.max(maxChain, v);
        }
        if (atleast <= n) {
            out.println("YES");
        } else {
            out.println("NO");
        }
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

    public static void main(String[] args) {
        new email_va().run();
    }
}
