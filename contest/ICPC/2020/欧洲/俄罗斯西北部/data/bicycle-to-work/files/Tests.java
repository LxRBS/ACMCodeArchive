import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;

/**
 * Created by vaksenov on 10.11.2020.
 */
public class Tests {
    public static int MAX = 100;
    public static int MAX_T = 1440;

    public static void main(String[] args) {
        if (args.length > 0) {
            new Tests().gen(args, -1);
        } else {
            new Tests().gen();
        }
    }

    int tests;
    Random rnd;

    public void writeTest(int a, int x, int b, int y, int T) {
        try {
            PrintWriter out = tests == -1 ? new PrintWriter(System.out) : new PrintWriter(String.format("%02d", tests));
            out.println(a);
            out.println(x);
            out.println(b);
            out.println(y);
            out.println(T);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sample(int test) {
        if (test == 1) {
            writeTest(10, 1, 20, 5, 50);
        }
        if (test == 2) {
            writeTest(10, 10, 10, 10, 42);
        }
        if (test == 3) {
            writeTest(10, 10, 10, 10, 27);
        }
    }

    public void zeroCost(int test) {
        if (test == 4) {
            writeTest(0, 0, 0, 0, 15);
        }
        if (test == 5) {
            writeTest(0, 0, 0, 0, 38);
        }
        if (test == 6) {
            writeTest(0, 0, 0, 0, 1440);
        }
    }

    public void zeroAnswer(int seed) {
        rnd = new Random(seed);
        writeTest(rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(30) + 1);
    }

    public void zeroSecond(int seed) {
        rnd = new Random(seed);
        writeTest(rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1),
                31 + rnd.nextInt(15));
    }

    public void minFirst(int seed) {
        rnd = new Random(seed);
        writeTest(1,  1, rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX_T));
    }

    public void minSecond(int seed) {
        rnd = new Random(seed);
        writeTest(rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), 1, 1, rnd.nextInt(MAX_T));
    }

    public void random(int seed) {
        rnd = new Random(seed);
        writeTest(rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX_T) + 1);
    }

    public void maxTest() {
        writeTest(MAX, MAX, MAX, MAX, MAX_T);
    }

    public void fixedT(int seed, int T) {
        rnd = new Random(seed);
        writeTest(rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), rnd.nextInt(MAX + 1), T);
    }

    public void gen(String[] args, int test) {
        tests = test;
        switch (args[0]) {
            case "sample":
                sample(Integer.parseInt(args[1]));
                break;
            case "zero_cost":
                zeroCost(Integer.parseInt(args[1]));
                break;
            case "zero_second":
                zeroSecond(Integer.parseInt(args[1]));
                break;
            case "zero_answer":
                zeroAnswer(Integer.parseInt(args[1]));
                break;
            case "min_first":
                minFirst(Integer.parseInt(args[1]));
                break;
            case "min_second":
                minSecond(Integer.parseInt(args[1]));
                break;
            case "random":
                random(Integer.parseInt(args[1]));
                break;
            case "max_test":
                maxTest();
                break;
            case "fixedT":
                fixedT(Integer.parseInt(args[1]), Integer.parseInt(args[2]));
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
