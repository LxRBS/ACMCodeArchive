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
/* Author                Vitaliy Aksenov                          */
/******************************************************************/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.Arrays;

/**
 * User: Aksenov Vitaly
 * Date: 16.18.14
 * Time: 19:35
 */
public class burrito_va {
    public static void main(String[] args) {
        new burrito_va().run();
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public class Ingredient implements Comparable<Ingredient> {
        int g, x, y, ind;

        public Ingredient(int g, int x, int y, int ind) {
            this.x = x;
            this.y = y;
            this.g = g;
            this.ind = ind;
        }

        public int compareTo(Ingredient i) {
            return this.y * i.x - this.x * i.y;
        }
    }

    public void solve() throws IOException {
        int n = nextInt();
        int X = nextInt();
        int Y = nextInt();

        Ingredient[] ingredients = new Ingredient[n];
        for (int i = 0; i < n; i++) {
            ingredients[i] = new Ingredient(nextInt(), nextInt(), nextInt(), i);
        }

        int l = 0;
        for (int i = 0; i < n; i++) {
            if (ingredients[i].x + ingredients[i].y != 0) {
                ingredients[l++] = ingredients[i];
            }
        }

        ingredients = Arrays.copyOf(ingredients, l);

        if (l > 0)
            Arrays.sort(ingredients, 0, l);

        double[] ans = new double[n];
        int Xn = 0;
        int Yn = 0;
        System.err.println(ingredients.length);
        for (int i = 0; i < ingredients.length; i++) {
            int xx = ingredients[i].x * ingredients[i].g;
            int yy = ingredients[i].y * ingredients[i].g;
            if (Yn <= Y) {
                if (Yn + yy > Y) {
                    if (1L * (X - Xn) * ingredients[i].y > 1L * (Y - Yn) * ingredients[i].x) {
                        out.println("-1 -1");
                        return;
                    }
                    ans[ingredients[i].ind] = 1. * (Y - Yn) / ingredients[i].y;
                    Xn = X;
                    Yn = Y;
                } else {
                    Xn += xx;
                    Yn += yy;
                    ans[ingredients[i].ind] = ingredients[i].g;
                }
            }
        }

        if (Xn < X) {
            out.print("-1 -1");
            return;
        }

        double ansX = 0;
        double ansY = 0;
        for (int i = 0; i < ingredients.length; i++) {
            ansX += ans[ingredients[i].ind] * ingredients[i].x;
            ansY += ans[ingredients[i].ind] * ingredients[i].y;
        }

        out.println(ansX + " " + ansY);
        for (int i = 0; i < ans.length; i++) {
            out.print(ans[i] + " ");
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("burrito.in"));
            out = new PrintWriter("burrito.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}

