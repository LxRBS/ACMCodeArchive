import java.util.*;
import java.lang.*;

public class Solution {
    public static boolean isPalindrome(String s) {
        // Checks if a string is a palindrome.
        int last_index = s.length()-1;

        for (int i = 0; (i < s.length()/2 + 1) && (i < s.length()); i++) {
            if (s.charAt(i) != s.charAt(last_index - i)) {
                return false;
            }
        }

        return true;
    }

    public static void testIsPalindrome() {
        assert(isPalindrome("1"));
        assert(isPalindrome("11"));
        assert(isPalindrome("121"));
        assert(isPalindrome("12121"));
        assert(isPalindrome("121121"));

        assert(!isPalindrome("12"));
        assert(!isPalindrome("314"));
    }

    public static short getMask(int max_base) {
        short[] max_bases = new short[17];
        max_bases[2] = 0b0000000000000001;
        max_bases[3] = 0b0000000000000011;
        max_bases[4] = 0b0000000000000111;
        max_bases[5] = 0b0000000000001111;
        max_bases[6] = 0b0000000000011111;
        max_bases[7] = 0b0000000000111111;
        max_bases[8] = 0b0000000001111111;
        max_bases[9] = 0b0000000011111111;
        max_bases[10] = 0b0000000111111111;
        max_bases[11] = 0b0000001111111111;
        max_bases[12] = 0b0000011111111111;
        max_bases[13] = 0b0000111111111111;
        max_bases[14] = 0b0001111111111111;
        max_bases[15] = 0b0011111111111111;
        max_bases[16] = 0b0111111111111111;

        return max_bases[max_base];
    }

    public static short genEntry(int number) {
        short result = 0;

        for (short radix = 2; radix <= 16; radix++) {
            String repr = Integer.toString(number, radix);
            if (isPalindrome(repr)) {
                result = (short)(result | (short)(1 << (short)(radix - 2)));
            } else {
                break;
            }
        }

        return result;
    }

    public static void main(String[] args) {
        int max_size = 4*1000*1000;
        short[] matrix = new short[max_size];
        for (int i = 0; i < max_size; i++) {
            matrix[i] = -1;
        }

        Scanner in = new Scanner(System.in);

        // Input begins with a number of test cases...
        int TC = 1;
        for (int tc = 1; tc <= TC; tc++) {
            // Each test case is three numbers:
            //   a - the minimum of the range, inclusive
            //   b - the maximum of the range, inclusive
            //   k - the base range size
            //
            // Problem statement: for $[a, b] \subseteq \Z$, print
            //     Test <i>: <z>
            // where <i> is the current test case number (1 <= i <= TC)
            // and <z> is the number of palindromes in all bases, b,
            // between 2 <= b <= k
            int a = in.nextInt();
            int b = in.nextInt();
            int k = in.nextInt();
            short mask = getMask(k);

            int answer = 0;
            for (int i = a; i <= b; i++) {
                if (matrix[i] == -1) {
                    matrix[i] = genEntry(i);
                }

                if ((matrix[i] & mask) == mask) {
                    answer += 1;
                }
            }

            System.out.println(answer);
        }
    }
}
