import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Task solver = new Task();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();

            double[] l = new double[100005];
            double[] r = new double[100005];

            double ans = 0, x;
            double outside_expectation = 0;
            double[] psum = new double[4];

            for (int i = 0; i < n; i++) {
                l[i] = Double.parseDouble(in.next());
                r[i] = Double.parseDouble(in.next());
            }

            if (n <= 1) {
                out.println(0);
                return;
            }

            int idx = 0; // points to largest index that intersects with current range
            double n2 = 1.0 / n / n;

            outside_expectation += (l[0] + r[0]) / 2;
            if (r[0] - l[0] > 0) {
              psum[0] = r[0] * r[0] * r[0] / (r[0] - l[0]) / 3;
              psum[1] = r[0] * r[0] / (r[0] - l[0]);
              psum[2] = r[0] / (r[0] - l[0]);
              psum[3] = 1.0 / (r[0] - l[0]) / 3;
            }

            for (int i = 1; i < n; i++) {
              // Update idx value
              while (idx < i && r[idx] <= l[i]) {
                // Remove
                if (r[idx] - l[idx] > 0) {
                  psum[0] -= r[idx] * r[idx] * r[idx] / (r[idx] - l[idx]) / 3;
                  psum[1] -= r[idx] * r[idx] / (r[idx] - l[idx]);
                  psum[2] -= r[idx] / (r[idx] - l[idx]);
                  psum[3] -= 1.0 / (r[idx] - l[idx]) / 3;
                }

                idx++;
              }

              // Add answer for shit outside of the range
              ans += (i * (l[i] + r[i]) / 2 - outside_expectation) * n2;

              // Tough value
              if (r[i] - l[i] > 0) {
                ans += psum[0] / (r[i] - l[i]) * n2;
                ans -= psum[1] / (r[i] - l[i]) * l[i] * n2;
                ans += psum[2] / (r[i] - l[i]) * l[i] * l[i] * n2;
                ans -= psum[3] / (r[i] - l[i]) * l[i] * l[i] * l[i] * n2;
              }

              // Update
              outside_expectation += (l[i] + r[i]) / 2;
              if (r[i] - l[i] > 0) {
                psum[0] += r[i] * r[i] * r[i] / (r[i] - l[i]) / 3;
                psum[1] += r[i] * r[i] / (r[i] - l[i]);
                psum[2] += r[i] / (r[i] - l[i]);
                psum[3] += 1.0 / (r[i] - l[i]) / 3;
              }
            }

            out.println(ans);
        }
    }

    static class InputReader {
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

        public int nextInt() {
            return Integer.parseInt(next());
        }

    }
}