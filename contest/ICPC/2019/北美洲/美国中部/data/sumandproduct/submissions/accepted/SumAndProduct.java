import java.io.*;
import java.util.*;

public class SumAndProduct {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        StringTokenizer st = new StringTokenizer(br.readLine());
        int[] a = new int[n];

        long total = 0;
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(st.nextToken());
            total += a[i];
        }

        int[] hop = new int[n];
        hop[n - 1] = a[n - 1] == 1 ? n : n - 1;
        for (int i = n - 2; i >= 0; i--) {
            if (a[i] == 1) {
                hop[i] = hop[i + 1];
            } else {
                hop[i] = i;
            }
        }

        long ans = 0;
        for (int i = 0; i < n; i++) {
            long sum = a[i];
            long product = a[i];
            for (int j = i + 1; product <= total && j < n;) {
                if (a[j] == 1) {
                    int dest = hop[j];
                    int dist = dest - j;
                    if (sum < product && sum + dist > product) {
                        ans++;
                    }
                    sum += dist;
                    j = dest;
                } else {
                    sum += a[j];
                    product *= a[j];
                    j++;
                }

                if (sum == product) {
                    ans++;
                }
            }
        }

        System.out.println(ans);
    }
}
