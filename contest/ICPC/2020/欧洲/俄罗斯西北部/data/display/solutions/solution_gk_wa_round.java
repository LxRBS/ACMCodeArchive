// Solution with answer rounding error
import java.io.PrintStream;
import java.util.Scanner;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class solution_gk_wa_round {
    private static Scanner in;
    private static PrintStream out;

    public static void main(String[] args) {
        in = new Scanner(System.in);
        out = System.out;
        new solution_gk_wa_round().run();
    }

    private void run() {
        int n = in.nextInt();
        int w = in.nextInt();
        int h = in.nextInt();
        int s = in.nextInt();
        in.nextLine();

        final StringBuilder characters = new StringBuilder();
        final String[][] images = new String[n][h];
        for (int i = 0; i < n; i++) {
            characters.append(in.nextLine().charAt(0));
            for (int r = 0; r < h; r++) {
                images[i][r] = in.nextLine();
            }
        }

        char answer = ' ';
        int max = -1;
        for (int r = 0; r < h; r++) {
            for (int i = 0; i < n; i++) {
                int q = calc(images[i][r]);
                if (max < q) {
                    max = q;
                    answer = characters.charAt(i);
                }
            }
        }
        out.println(new String(new char[s / max]).replace('\0', answer));
    }

    private int calc(final String row) {
        int q = 0;
        for (int c = 0; c < row.length(); c++) {
            if ((row.charAt(c) == '.') != (q % 2 == 0)) {
                q++;
            }
        }
        if (q % 2 == 1) {
            q++;
        }
        return q;
    }
}
