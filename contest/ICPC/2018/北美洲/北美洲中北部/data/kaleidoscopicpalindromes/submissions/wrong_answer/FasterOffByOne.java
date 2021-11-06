import java.util.*;
import java.lang.*;

public class FasterOffByOne {
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

    public static short[] matrix = new short[4*1000*1000];

    public static void build_matrix(int max) {
        matrix[1] = 0b0111111111111111;
        for (int i = 0; i < 8192; i++) {
            boolean a = build_matrix_internal(i, max, "");
            boolean b = build_matrix_internal(i, max, "0");
            boolean c = build_matrix_internal(i, max, "1");
            if (a == false && b == false && c == false) {
                break;
            }
        }
    }

    public static boolean build_matrix_internal(int prefix, int max, String intermediate) {
        StringBuilder repr = new StringBuilder();
        repr.append(Integer.toString(prefix, 2));

        int repr_length = repr.length() - 1;
        repr.append(intermediate);

        for (int i = repr_length; i >= 0; i--) {
            repr.append(repr.charAt(i));
        }

        int value = Integer.parseInt(repr.toString(), 2);
        if (value > max) {
            return false;
        }

        short entry = 0b0000000000000001;
        for (int radix = 3; radix <= 16; radix++) {
            String r_repr = Integer.toString(value, radix);
            if (isPalindrome(r_repr)) {
                entry = (short)(entry | (short)(1 << (short)(radix - 2)));
            } else {
                break;
            }
        }

        matrix[value] = entry;

        return true;
    }

    public static void main(String[] args) {
        int max_size = 4*1000*1000;

        build_matrix(max_size);

        Scanner in = new Scanner(System.in);

        // Input begins with a number of test cases...
        int TC = 1;
        for (int tc = 1; tc <= TC; tc++) {
            // Each test case is three numbers:
            //   a - the minimum of the range, inclusive
            //   b - the maximum of the range, inclusive
            //   k - the base max
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
                if ((matrix[i] & mask) == mask) {
                    answer += 1;
                }
            }

            System.out.println(answer);
        }
    }
}
