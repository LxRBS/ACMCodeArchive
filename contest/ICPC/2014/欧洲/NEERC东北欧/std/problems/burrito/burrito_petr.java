/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem B. Burrito King                                        */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Petr Mitrichev                           */
/******************************************************************/


import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.Comparator;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.util.StringTokenizer;
import java.io.InputStream;
 
/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class burrito_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("burrito.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("burrito.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Burrito solver = new Burrito();
        solver.solve(1, in, out);
        out.close();
    }

    static class Burrito {
        static class Ingredient {
            int g;
            int a;
            int b;
            int index;
            double amount;
        }

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            long A = in.nextInt();
            long B = in.nextInt();
            Ingredient[] ingredients = new Ingredient[n];
            for (int i = 0; i < n; ++i) {
                ingredients[i] = new Ingredient();
                ingredients[i].g = in.nextInt();
                ingredients[i].a = in.nextInt();
                ingredients[i].b = in.nextInt();
                ingredients[i].index = i;
            }
            Arrays.sort(ingredients, new Comparator<Ingredient>() {
                @Override
                public int compare(Ingredient o1, Ingredient o2) {
                    int z1 = (o1.a == 0 && o1.b == 0) ? 1 : 0;
                    int z2 = (o2.a == 0 && o2.b == 0) ? 1 : 0;
                    if (z1 != z2) {
                        return z1 - z2;
                    }
                    return o2.a * o1.b - o2.b * o1.a;
                }
            });
            double ra = 0;
            double rb = 0;
            for (Ingredient ingredient : ingredients) {
                if (ingredient.g * ingredient.b <= B) {
                    ra += ingredient.g * ingredient.a;
                    rb += ingredient.g * ingredient.b;
                    B -= ingredient.g * ingredient.b;
                    A -= ingredient.g * ingredient.a;
                    ingredient.amount = ingredient.g;
                    continue;
                }
                if (A > 0 && B * ingredient.a < A * ingredient.b) {
                    out.println("-1 -1");
                    return;
                }
                double take = B / (double) ingredient.b;
                ra += ingredient.a * take;
                rb += ingredient.b * take;
                ingredient.amount = take;
                A = 0;
                B = 0;
                break;
            }
            if (A > 0) {
                out.println("-1 -1");
                return;
            }
            out.println(ra + " " + rb);
            double[] res = new double[n];
            for (Ingredient ingredient : ingredients) res[ingredient.index] = ingredient.amount;
            for (int i = 0; i < n; ++i) {
                if (i > 0) out.print(" ");
                out.print(res[i]);
            }
            out.println();
        }
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

    }
}

