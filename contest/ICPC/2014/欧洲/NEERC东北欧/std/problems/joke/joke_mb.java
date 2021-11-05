/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem J. Jokewithpermutation                                 */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Maxim Babenko                            */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Maxim Babenko                            */
/******************************************************************/

import java.io.*;

public class joke_mb {
    public static final String NO_SOLUTION = "No solution";

    static class State {
        final int[] digits;
        final int[] answers;
        final int n;
        final boolean[] used;

        int opCount = 0;

        public State(int[] digits, int n) {
            this.digits = digits;
            this.n = n;
            this.answers = new int[digits.length];
            this.used = new boolean[digits.length];
        }

        private int[] permutation() {
            int[] rv = new int[n];
            for (int i = 0, j = 0; i < answers.length; ++i) {
                if (answers[i] == 0) throw new IllegalStateException("Not ready yet!");
                if (i == 0 || answers[i] != answers[i - 1]) {
                    rv[j++] = answers[i];
                }
            }
            return rv;
        }

        private boolean workSmaller(int first, int last) {
            ++opCount;
            if (last == 0) {
                return true;
            }
            if (first == -1) {
                return workSmaller((n - (last - 1)) / 10, last - 1);
            }
            int v = first * 10 + last;
            for (int i = 0; i < digits.length; ++i) {
                if (hasAt(i, v)) {
                    set(i, v);
                    if (!workSmaller(first - 1, last)) {
                        clear(i, v);
                    } else {
                        return true;
                    }
                }
            }
            return false;
        }

        private boolean cutZeros() {
            for (int t = 10; t <= 50 && t <= n; t += 10) {
                ++opCount;
                boolean ok = false;
                for (int i = 0; !ok && i + 1 < digits.length; ++i) {
                    if (hasAt(i, t)) {
                        set(i, t);
                        ok = true;
                    }
                }
                if (!ok) {
                    return false;
                }
            }
            int lastDigitEver = Math.min(n, 9);
            return workSmaller((n - lastDigitEver) / 10, lastDigitEver);
        }

        public int[] solve() {
            if (!cutZeros()) {
                return null;
            } else {
                return permutation();
            }
        }

        public boolean hasAt(int index, int value) {
            if (value <= 9) {
                return index >= 0 && index < digits.length
                    && digits[index] == value && !used[index];
            } else {
                return index >= 0 && index + 1 < digits.length
                    && digits[index] == value / 10 && digits[index + 1] == value % 10
                    && !used[index] && !used[index + 1];
            }
        }

        public void set(int index, int value) {
            if (!hasAt(index, value)) {
                throw new IllegalArgumentException("Asking for an illegal action");
            }
            used[index] = true;
            answers[index] = value;
            if (value >= 10) {
                used[index + 1] = true;
                answers[index + 1] = value;
            }
        }

        public void clear(int index, int value) {
            if (index + (value >= 10 ? 1 : 0) >= digits.length) {
                throw new IllegalArgumentException("Out of bounds");
            }
            used[index] = false;
            answers[index] = 0;
            if (value >= 10) {
                used[index + 1] = false;
                answers[index + 1] = 0;
            }
            if (!hasAt(index, value)) {
                throw new IllegalArgumentException("Asking for an illegal action");
            }
        }
    }

    private static State parseInput(String input) {
        int n = 1, l = 1;
        while (l < input.length()) {
            ++n;
            int nc = n;
            while (nc > 0) {
                ++l;
                nc /= 10;
            }
        }
        if (l != input.length()) {
            return null;
        }
        int[] digitCount = new int[10];
        for (int i = 1; i <= n; ++i) {
            int ic = i;
            while (ic > 0) {
                ++digitCount[ic % 10];
                ic /= 10;
            }
        }
        for (int i = 0; i < l; ++i) {
            --digitCount[input.charAt(i) - '0'];
        }
        for (int i = 0; i < 10; ++i) {
            if (digitCount[i] != 0) {
                return null;
            }
        }
        int[] digits = new int[l];
        for (int i = 0; i < l; ++i) {
            digits[i] = input.charAt(i) - '0';
        }
        return new State(digits, n);
    }

    public static String solve(String input) {
        State state = parseInput(input);
        if (state == null) {
            return NO_SOLUTION;
        } else {
            int[] rv = state.solve();
            if (rv == null) {
                return NO_SOLUTION;
            }
            StringBuilder sb = new StringBuilder();
            for (int i : rv) {
                if (sb.length() != 0) {
                    sb.append(" ");
                }
                sb.append(i);
            }
            return sb.toString();
        }
    }

    public static int fitness(String input) {
        State state = parseInput(input);
        if (state == null) {
            return 0;
        } else {
            int[] rv = state.solve();
            if (rv == null) {
                return 0;
            } else {
                return state.opCount;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        try (BufferedReader in = new BufferedReader(new FileReader("joke.in"));
             PrintWriter out = new PrintWriter("joke.out")) {
            out.println(solve(in.readLine()));
        }
    }
}

