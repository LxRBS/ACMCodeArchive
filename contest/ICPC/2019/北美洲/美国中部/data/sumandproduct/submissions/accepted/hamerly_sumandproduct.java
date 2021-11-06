import java.io.*;
import java.util.*;

public class hamerly_sumandproduct {

    public static void main(String args[]) throws Exception {
        int numbers[] = new int[200001];
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        String tokens[] = in.readLine().split(" ");
        for (int i = 0; i < n; ++i)
            numbers[i] = Integer.parseInt(tokens[i]);

        // precompute the runs of "1"s in the numbers, which we know does not change the
        // product
        numbers[n] = 0;
        int end_ones[] = new int[n];
        for (int i = 1; i <= n; ++i) {
            if (numbers[i-1] == 1 && numbers[i] != 1) {
                int j = i - 1;
                while (0 < j && numbers[j] == 1) {
                    end_ones[j] = i;
                    j -= 1;
                }
            }
        }

        // if the product gets larger than this, it never gets smaller, so we can break
        // out of the current inner loop
        final long LARGEST_SUM = 100000000000000L;

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            long s = numbers[i], p = numbers[i];
            int j = i + 1;
            while (j < n) {
                int y = numbers[j];

                // treat each run of "1"s specially, skipping ahead to the end
                if (y == 1) {
                    long endsum = s + end_ones[j] - j;
                    // Is there a match somewhere in this range? If so, there can be at
                    // most one.
                    if (s + 1 <= p && p <= endsum)
                        ans++;
                    // skip ahead to the end of the run of 1s
                    j = end_ones[j];
                    s = endsum;
                } else {
                    // the normal case
                    s += y;
                    p *= y;
                    if (LARGEST_SUM < p)
                        break;
                    if (s == p)
                        ans++;
                    j++;
                }
            }
        }

        System.out.println(ans);
    }
}
