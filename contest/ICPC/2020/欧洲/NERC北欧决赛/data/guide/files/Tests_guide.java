import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;

/**
 * Created by vaksenov on 16.03.2021.
 */
public class Tests_guide {
    int MAX_TESTS = 100;
    int MAX_N = 100;

    public static void main(String[] args) {
        if (args.length > 0) {
            new Tests_guide().gen(args, -1);
        } else {
            new Tests_guide().gen();
        }
    }

    int tests;
    Random rnd;

    public void writeTest(int[][] p, int[] k) {
        try {
            PrintWriter out = tests == -1 ? new PrintWriter(System.out) : new PrintWriter(String.format("%02d", tests));
            out.println(p.length);
            for (int i = 0; i < p.length; i++) {
                out.println(p[i].length + " " + k[i]);
                for (int j = 1; j < p[i].length; j++) {
                    out.print((j != 1 ? " " : "") + (p[i][j] + 1));
                }
                out.println();
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeTest(int[] p) {
        int[] k = new int[p.length];
        int[][] mp = new int[k.length][];
        for (int i = 0; i < mp.length; i++) {
            k[i] = i + 1;
            mp[i] = p;
        }
        writeTest(mp, k);
    }

    public void binaryTree(int n) {
        int[] p = new int[n];
        for (int i = 1; i < n; i++) {
             p[i] = (i - 1) / 2;
        }
        writeTest(p);
    }

    public void bamboo(int n) {
        int[] p = new int[n];
        for (int i = 1; i < n; i++) {
            p[i] = i - 1;
        }
        writeTest(p);
    }

    public void vine(int n) {
        int[] p = new int[n];
        for (int i = 1; i < n; i++) {
            p[i] = i - 2 + i % 2;
        }
        writeTest(p);
    }

    public void star(int n) {
        int[] p = new int[n];
        writeTest(p);
    }

    public void random(int n, int seed) {
        rnd = new Random(seed);
        int[] p = new int[n];
        for (int i = 1; i < n; i++) {
            p[i] = rnd.nextInt(i);
        }
        writeTest(p);
    }

    public void allRandom(int t, int n, int seed) {
        rnd = new Random(seed);
        int[][] p = new int[t][n];
        int[] k = new int[t];
        for (int i = 0; i < t; i++) {
            for (int j = 1; j < n; j++) {
                p[i][j] = rnd.nextInt(j);
            }
            k[i] = rnd.nextInt(n) + 1;
        }

        writeTest(p, k);
    }

    public void sample() {
        int[][] p = new int[][] {
                new int[] { 0, 0, 0, 1, 1, 2},
                new int[] { 0, 0, 0, 1, 1, 2},
                new int[] { 0, 0, 1, 2, 3, 4}
        };
        int[] k = new int[] {
                2,
                6,
                4
        };
        writeTest(p, k);
    }

    public void small() {
        int[][] p = new int[][] {
                new int[] {0},
                new int[] {0, 0},
                new int[] {0, 0},
        };
        int[] k = new int[] {
                1,
                1,
                2
        };
        writeTest(p, k);
    }

    public void gen(String[] args, int test) {
        tests = test;
        switch (args[0]) {
            case "sample":
                sample();
                break;
            case "small":
                small();
                break;
            case "random":
                random(Integer.parseInt(args[1]), Integer.parseInt(args[2]));
                break;
            case "all_random":
                allRandom(Integer.parseInt(args[1]), Integer.parseInt(args[2]), Integer.parseInt(args[3]));
                break;
            case "binary":
                binaryTree(Integer.parseInt(args[1]));
                break;
            case "bamboo":
                bamboo(Integer.parseInt(args[1]));
                break;
            case "vine":
                vine(Integer.parseInt(args[1]));
                break;
            case "star":
                star(Integer.parseInt(args[1]));
                break;
        }
    }

    public void gen() {
        try (Scanner in = new Scanner(new File("tests.txt"))) {
            int test = 1;
            while (in.hasNext()) {
                String line = in.nextLine();
                if (line.length() == 0)
                    break;
                System.err.println("Generating test: " + line);
                int pos = line.indexOf(" ");
                line = line.substring(pos + 1);
                gen(line.split(" "), test++);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
