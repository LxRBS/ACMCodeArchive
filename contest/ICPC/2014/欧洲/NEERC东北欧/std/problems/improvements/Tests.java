/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem I. Improvements                                        */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author                Vitaliy Aksenov                          */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {
    public static void main(String[] args) {
        new Tests().gen();
    }

    final static int MAXN = 200000;
    Random rnd = new Random(239);
    int tests = 1;

    public ArrayList<Integer> putOnLine(ArrayList<Integer> numbers) {
        ArrayList<Integer> ans = new ArrayList<>();

        if (numbers.size() == 0) {
            return numbers;
        }
        ArrayDeque<Integer> deque = new ArrayDeque<>();

        int ind = 1;
        for (int i = numbers.size() - 1; i >= 0; i--) {
            if (rnd.nextBoolean()) {
                deque.offerLast(numbers.get(i));
            } else {
                deque.offerFirst(numbers.get(i));
            }
        }
        for (int x : deque)
            ans.add(x);
        return ans;
    }

    public void writeTest(ArrayList<Integer> a) {
        try {
            System.out.println("Writing test " + tests);
            PrintWriter out = new PrintWriter(String.format("tests/%02d", tests++));
            out.println(a.size());

            int[] reverse = new int[a.size()];

            for (int i = 0; i < reverse.length; i++) {
                reverse[a.get(i)] = i;
            }

            boolean first = true;
            for (int b : reverse) {
                if (!first) {
                    out.print(" ");
                }
                first = false;
                out.print(b + 1);
            }
            out.println();
            out.close();
        } catch (IOException ex) {
        }
    }

    /**
     * Generate test
     * 
     * @param n
     *            count of numbers
     * @param k
     *            approximate answer
     */
    public void gen(int n, int k) {
        ArrayList<Integer> have = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            have.add(i);
        }

        Collections.shuffle(have, rnd);

        ArrayList<Integer> take = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            take.add(have.get(n - i - 1));
            have.remove(n - i - 1);
        }

        Collections.sort(have);
        have = putOnLine(have);

        Collections.shuffle(take, rnd);

        ArrayList<Integer> ans = new ArrayList();
        int l = 0;
        int r = 0;
        while (l < have.size() || r < take.size()) {
            if (l == have.size()) {
            	ans.add(take.get(r++));
            	continue;
            }
            if (r == take.size()) {
				ans.add(have.get(l++));
				continue;
            }
            if (rnd.nextInt(have.size() + take.size() - l - r) < have.size() - l)
				ans.add(have.get(l++));
			else
				ans.add(take.get(r++));
        }

        writeTest(ans);
    }

    public void increasing(int n) {
        ArrayList<Integer> ans = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            ans.add(i);
        }
        writeTest(ans);
    }

    public void near_increasing(int n) {
        ArrayList<Integer> ans = new ArrayList<Integer>();
        int toPut = rnd.nextInt(n);
        for (int i = 0; i < n; i++) {
            if (toPut != i)
                ans.add(i);
        }
        ans.add(rnd.nextInt(n), toPut);
        writeTest(ans);
    }

    public void decreasing(int n) {
        ArrayList<Integer> ans = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            ans.add(n - i - 1);
        }
        writeTest(ans);
    }

    public void near_decreasing(int n) {        ArrayList<Integer> ans = new ArrayList<Integer>();
        int toPut = rnd.nextInt(n);
        for (int i = 0; i < n; i++) {
            if (toPut != n - i - 1)
                ans.add(n - i - 1);
        }
        ans.add(rnd.nextInt(n), toPut);
        writeTest(ans);
    }


    public void gen() {
        // Samples.
        ArrayList<Integer> x = new ArrayList<Integer>();
        x.add(0);
        x.add(2);
        x.add(1);
        x.add(3);
        writeTest(x);

        x.clear();
        x.add(0);
        x.add(2);
        x.add(3);
        x.add(1);
        writeTest(x);

        x.clear();
        x.add(0);
        x.add(2);
        x.add(3);
        x.add(1);
                x.clear();
        x.add(0);
        x.add(2);
        x.add(1);
        writeTest(x);

        x.clear();
        x.add(0);
        writeTest(x);

        for (int i = 0; i < 2; i++) {
            int n = rnd.nextInt(30) + 2;
            gen(n, n);
            n = rnd.nextInt(30) + 2;
            gen(n, n);
        }

        for (int i = 0; i < 2; i++) {
            int n = rnd.nextInt(30) + 2;
            gen(n, rnd.nextInt(n) + 1);
        }

        for (int i = 0; i < 4; i++) {
            gen(rnd.nextInt(30) + 2, 0);
        }

        for (int i = 0; i < 3; i++) {
            int n = MAXN;
            gen(n, n);
        }

        for (int i = 0; i < 5; i++) {
            int n = MAXN;
            gen(n, rnd.nextInt(n) + 1);
        }

        for (int i = 0; i < 4; i++) {
            gen(MAXN, 0);
        }

        increasing(MAXN);
        decreasing(MAXN);
        for (int i = 0; i < 2; i++) {
            near_increasing(MAXN);
            near_decreasing(MAXN);
        }
    }
}

