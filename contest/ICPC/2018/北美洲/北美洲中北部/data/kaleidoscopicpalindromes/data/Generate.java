import java.util.*;
import java.lang.*;

public class Generate {
    public static boolean isPalindrome(String s) {
        // Checks if a string is a palindrome.

        int start_index = 0;
        int end_index = s.length()-1;

        while (start_index <= end_index && start_index < s.length() && end_index >= 0) {
            if (s.charAt(start_index) != s.charAt(end_index)) {
                return false;
            }

            start_index += 1;
            end_index -= 1;
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

    public static void testGenEntry() {
        int all_palindromes = (2 << 14) - 1;
        assert(genEntry(0) == all_palindromes);
        assert(genEntry(1) == all_palindromes);
        assert(genEntry(2) == (all_palindromes-1));
    }

    public static void main(String[] args) {
        testIsPalindrome();
        testGenEntry();

        Random rand = new Random(System.currentTimeMillis());

        int max_size = 4*1000*1000;
        short[] matrix = new short[max_size];
        for (int i = 0; i < max_size; i++) {
            matrix[i] = genEntry(i);
        }

        int current_tc = 1;
        int num_tc = 1;
        int TC = num_tc;

        // small test cases
        /*
        for (int tc = 1; tc <= TC; tc++) {
            int a = rand.nextInt(1000);
            int b_offset = rand.nextInt(100) + 11;
            int b = a + b_offset;
            int k = rand.nextInt(15);
            short mask = getMask(2+k);
            int answer = 0;
            for (int i = a; i <= b; i++) {
                if ((matrix[i] & mask) == mask) {
                    answer += 1;
                }
            }
            System.out.println(a + " " + b + " " + k);
            System.err.println(answer);
            current_tc += 1;
        }

    /*
        // medium test cases
        TC = num_tc;
        for (int tc = 1; tc <= TC; tc++) {
            int a = rand.nextInt(10000);
            int b_offset = rand.nextInt(10000) + 1000;
            int b = a + b_offset;
            int k = rand.nextInt(15);
            short mask = getMask(2+k);
            int answer = 0;
            for (int i = a; i <= b; i++) {
                if ((matrix[i] & mask) == mask) {
                    answer += 1;
                }
            }
            System.out.println(a + " " + b + " " + k);
            System.err.println(answer);
            current_tc += 1;
        }*/

        // large test cases
        TC = 1;
        for (int tc = 1; tc <= TC; tc++) {
            int a = rand.nextInt(2000000);
            int b_offset = rand.nextInt(1000000) + 100000;
            int b = a + b_offset;
            int k = rand.nextInt(15);
            short mask = getMask(2+k);
            int answer = 0;
            for (int i = a; i <= b; i++) {
                if ((matrix[i] & mask) == mask) {
                    answer += 1;
                }
            }
            System.out.println(a + " " + b + " " + k);
            System.err.println(answer);
            current_tc += 1;
        }/**/
    }
}
