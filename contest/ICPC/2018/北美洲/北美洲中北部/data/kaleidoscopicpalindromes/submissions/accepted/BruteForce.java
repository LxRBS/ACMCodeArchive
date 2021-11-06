import java.util.*;

public class BruteForce {
    static boolean palindrome(int n, int b) {
        String num = "";
        while (n != 0) {
            num += "" + n%b;
            n /= b;
        }
        return num.equals(new StringBuilder(num).reverse().toString());
    }
    
    public static void main(String[] args) {
        int a, b, k;
        Scanner in = new Scanner(System.in);
        a = in.nextInt();
        b = in.nextInt();
        k = in.nextInt();

        int count = 0;
        for (int i = a; i <= b; ++i) {
            boolean works = true;
            for (int j = 2; j <= k && works; ++j) {
                if (!palindrome(i, j))
                    works = false;
            }
            if (works) ++count;
        }
        System.out.println(count);
    }
}
