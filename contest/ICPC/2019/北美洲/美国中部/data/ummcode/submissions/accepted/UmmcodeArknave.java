import java.io.*;
import java.util.*;

public class UmmcodeArknave {
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
        Scanner scan = new Scanner(new InputStreamReader(System.in));
        String[] words = scan.nextLine().split(" ");
        StringBuilder res = new StringBuilder();

        int val = 0;
        int len = 0;
        for (String word : words) {
            if (valid(word)) {
                for (char c : word.toCharArray()) {
                    if (c != 'u' && c != 'm') {
                        continue;
                    }

                    val <<= 1;
                    if (c == 'u')
                        val |= 0x1;

                    if (++len == 7) {
                        res.append((char)val);
                        val = 0;
                        len = 0;
                    }
                }
            }
        }

        System.out.println(res);
    }
}
