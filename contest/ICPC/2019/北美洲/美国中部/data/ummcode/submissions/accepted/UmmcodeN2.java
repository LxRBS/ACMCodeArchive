import java.io.*;
import java.util.*;

/**
 * This solution uses O(N^2) output concatenation. 
 *
 * Even though the input is over 300k characters, the output isn't more than a
 * few thousand, so this is fine.
 */
public class UmmcodeN2 {
    public static boolean valid(String s) {
        for (char c : s.toCharArray()) {
            if (c == 'u' || c == 'm') {
                continue;
            }
            if ('0' <= c && c <= '9') {
                return false;
            }
            if ('A' <= c && c <= 'Z') {
                return false;
            }
            if ('a' <= c && c <= 'z') {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        String res = "";
        int val = 0;
        int len = 0;
        while (st.hasMoreTokens()) {
            String word = st.nextToken();
            if (valid(word)) {
                for (char c : word.toCharArray()) {
                    if (c != 'u' && c != 'm') {
                        continue;
                    }

                    val <<= 1;
                    if (c == 'u')
                        val |= 0x1;

                    if (++len == 7) {
                        res += "" + (char)val;
                        val = 0;
                        len = 0;
                    }
                }
            }
        }

        System.out.println(res);
    }
}
