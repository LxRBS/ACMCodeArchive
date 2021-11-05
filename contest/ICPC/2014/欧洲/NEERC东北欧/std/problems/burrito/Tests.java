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
/* Tests                                                          */
/*                                                                */
/* Author                Vitaliy Aksenov                          */
/******************************************************************/

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;

public class Tests {
    static int MAXN = 100000;
    static int MAX = 100;
    static int MAXX = 1000000000;
    int group;

    Random rnd = new Random(239);

    String folder;

    public static void main(String[] args) throws FileNotFoundException {
        new Tests().gen();
    }

    public int random(int l, int r) {
        if (r < l)
            return l;

        return l + rnd.nextInt(r - l + 1);
    }

    static int tests = 1;

    class Ingredient implements Comparable<Ingredient> {
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

        public String toString() {
            return  g + " " + x + " " + y;
        }
    }

    public void writeTest(int X, int Y, Ingredient[] a) {
        try {
            PrintWriter out = new PrintWriter(String.format(folder + "%02d", tests++));

            System.err.println("Writing test " + (tests - 1));

            backup(a);

            out.println(a.length + " " + X + " " + Y);

            for (int i = 0; i < a.length; i++) {
                out.println(a[i]);
            }

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Ingredient[] genAlZeros(int n) {
        Ingredient[] ingredients = new Ingredient[n];
        for (int i = 0; i < n; i++) {
            ingredients[i] = new Ingredient(random(0, MAX), 0, 0, i);
        }
        return ingredients;
    }

    public Ingredient[] genZeros(int n, int MIN, int MAX) {
        Ingredient[] ingredients = new Ingredient[n];
        for (int i = 0; i < n; i++) {
            ingredients[i] = new Ingredient(random(0, MAX), 0, random(MIN, MAX), i);
        }
        return ingredients;
    }

    public Ingredient[] genRandomIngredients(int n, int MIN, int MAX) {
        Ingredient[] ingredients = new Ingredient[n];
        for (int i = 0; i < ingredients.length; i++) {
            ingredients[i] = new Ingredient(random(1, MAX), random(0, MAX), random(MIN, MAX), i);
        }

        int l = n - 1;
        for (int i = 0; i < l; i++) {
            while (l >= 0 && ingredients[l].x + ingredients[l].y == 0) {
                l--;
            }
            if (l > i && ingredients[i].x + ingredients[i].y == 0) {
                Ingredient tmp = ingredients[i];
                ingredients[i] = ingredients[l];
                ingredients[l] = tmp;
            }
        }

        Arrays.sort(ingredients, 0, l);

        return ingredients;
    }

    public void backup(Ingredient[] ingredients) {
        Ingredient[] fc = new Ingredient[ingredients.length];
        for (int i = 0; i < ingredients.length; i++) {
            fc[i] = ingredients[i];
        }
        for (int i = 0; i < ingredients.length; i++) {
            ingredients[fc[i].ind] = fc[i];
        }
    }

    public void genGeneral(Ingredient[] ingredients) {
        int split = rnd.nextInt(ingredients.length);
        int X = 0;
        int Y = 0;
        for (int i = 0; i < split; i++) {
            X += ingredients[i].g * ingredients[i].x;
            Y += ingredients[i].g * ingredients[i].y;
        }

        int dy = rnd.nextInt(ingredients[split].g * ingredients[split].y);
        double cc = 1. * dy / (ingredients[split].g * ingredients[split].y);
        double dx = 1. * cc * (ingredients[split].g * ingredients[split].x);
        writeTest(rnd.nextInt(X + (int) dx + 1), Y + dy, ingredients);
    }

    public void genIntegerSplit(Ingredient[] ingredients) {
        int split = rnd.nextInt(ingredients.length);
        int X = 0;
        int Y = 0;
        for (int i = 0; i < split; i++) {
            X += ingredients[i].g * ingredients[i].x;
            Y += ingredients[i].g * ingredients[i].y;
        }

        writeTest(rnd.nextInt(X + 1), Y, ingredients);
    }

    public void genExactSplit(Ingredient[] ingredients) {
        int split = rnd.nextInt(ingredients.length);
        int X = 0;
        int Y = 0;
        for (int i = 0; i < split; i++) {
            X += ingredients[i].g * ingredients[i].x;
            Y += ingredients[i].g * ingredients[i].y;
        }

        writeTest(X, Y, ingredients);
    }

    public void genBigX(Ingredient[] ingredients) {
        int split = rnd.nextInt(ingredients.length);
        int X = 0;
        int Y = 0;
        for (int i = 0; i < split; i++) {
            X += ingredients[i].g * ingredients[i].x;
            Y += ingredients[i].g * ingredients[i].y;
        }

        int dy = rnd.nextInt(ingredients[split].g * ingredients[split].y);
        double cc = 1. * dy / (ingredients[split].g * ingredients[split].y);
        double dx = 1. * cc * (ingredients[split].g * ingredients[split].x);
        writeTest(X + (int) dx + 1, Y + dy, ingredients);
    }

    public void genAll1(Ingredient[] ingredients) {
        int X = 0;
        int Y = 0;
        for (int i = 0; i < ingredients.length; i++) {
            X += ingredients[i].g * ingredients[i].x;
            Y += ingredients[i].g * ingredients[i].y;
        }

        writeTest(random(0, X), random(Y, MAX * MAX * MAXN), ingredients);
    }

    public void genAll2(Ingredient[] ingredients) {
        int X = 0;
        int Y = 0;
        for (int i = 0; i < ingredients.length; i++) {
            X += ingredients[i].g * ingredients[i].x;
            Y += ingredients[i].g * ingredients[i].y;
        }

        writeTest(random(X + 1, MAX * MAX * MAXN), random(Y, MAX * MAX * MAXN), ingredients);
    }

    public void genExact(Ingredient[] ingredients) {
        int X = 0;
        int Y = 0;
        for (int i = 0; i < ingredients.length; i++) {
            X += ingredients[i].g * ingredients[i].x;
            Y += ingredients[i].g * ingredients[i].y;
        }

        writeTest(X, Y, ingredients);
    }

    public void genOverflows() {
        Ingredient[] ingredients = new Ingredient[MAXN];
        for (int i = 0; i < ingredients.length; i++) {
            ingredients[i] = new Ingredient(MAX, MAX, 0, i);
        }
        writeTest(MAXX, MAXX, ingredients);
        writeTest(MAXX, 0, ingredients);
        writeTest(0, MAXX, ingredients);

        for (int i = 0; i < ingredients.length; i++) {
            ingredients[i] = new Ingredient(MAX, 0, MAX, i);
        }

        writeTest(MAXX, MAXX, ingredients);
        writeTest(MAXX, 0, ingredients);
        writeTest(0, MAXX, ingredients);

        for (int i = 0; i < ingredients.length; i++) {
            ingredients[i] = new Ingredient(MAX, MAX, MAX, i);
        }
        writeTest(MAXX, MAXX, ingredients);
        writeTest(MAXX, 0, ingredients);
        writeTest(0, MAXX, ingredients);

        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < ingredients.length; i++) {
               ingredients[i] = new Ingredient(MAX, MAX / 2 + random(0, MAX / 2), 0, i);
            }
            writeTest(1, MAXX, ingredients);

            for (int i = 0; i < ingredients.length; i++) {
               ingredients[i] = new Ingredient(MAX, 0, MAX / 2 + random(0, MAX / 2), i);
            }
            writeTest(MAXX, 0, ingredients);
        }

        for (int i = 0; i < ingredients.length; i++) {
            ingredients[i] = new Ingredient(MAX, 1, 3, i);
        }
        writeTest(MAXX, 0, ingredients);

        for (int i = 0; i < ingredients.length; i++) {
            ingredients[i] = new Ingredient(MAX, 3, 1, i);//
        }
        writeTest(0, MAXX, ingredients);
    }

    public void gen() {
        tests = 1;
        folder = "tests/";
        if (!new File(folder).exists())
            new File(folder).mkdir();

        writeTest(5, 5, new Ingredient[] { new Ingredient(2, 2, 1, 0), new Ingredient(2, 2, 4, 1) });

        writeTest(5, 5, new Ingredient[] { new Ingredient(2, 2, 2, 0), new Ingredient(2, 2, 4, 1) });

        genGeneral(genRandomIngredients(rnd.nextInt(10) + 1, 0, 10));
        genIntegerSplit(genRandomIngredients(rnd.nextInt(10) + 1, 0, 10));
        genExactSplit(genRandomIngredients(rnd.nextInt(10) + 1, 0, 10));
        genBigX(genRandomIngredients(rnd.nextInt(10) + 1, 0, 10));
        genAll1(genRandomIngredients(rnd.nextInt(10) + 1, 0, 10));
        genAll2(genRandomIngredients(rnd.nextInt(10) + 1, 0, 10));
        genExact(genRandomIngredients(rnd.nextInt(10) + 1, 0, 10));

        for (int i = 0; i < 2; i++)
            genGeneral(genRandomIngredients(rnd.nextInt(MAXN) + 1, 0, MAX));
        genIntegerSplit(genRandomIngredients(rnd.nextInt(MAXN) + 1, 0, MAX));
        genExactSplit(genRandomIngredients(rnd.nextInt(MAXN) + 1, 0, MAX));
        genBigX(genRandomIngredients(rnd.nextInt(MAXN) + 1, 0, MAX));
        genAll1(genRandomIngredients(rnd.nextInt(MAXN) + 1, 0, MAX));
        genAll2(genRandomIngredients(rnd.nextInt(MAXN) + 1, 0, MAX));
        genExact(genRandomIngredients(rnd.nextInt(MAXN) + 1, 0, MAX));

        genGeneral(genZeros(MAXN, 0, MAX));
        genIntegerSplit(genZeros(MAXN, 0, MAX));
        genExactSplit(genZeros(MAXN, 0, MAX));
        genBigX(genZeros(MAXN, 0, MAX));
        genAll1(genZeros(MAXN, 0, MAX));
        genAll2(genZeros(MAXN, 0, MAX));
        genExact(genZeros(MAXN, 0, MAX));

        genAll1(genZeros(MAXN, MAX, MAX));
        genAll2(genZeros(MAXN, MAX, MAX));
        genExact(genZeros(MAXN, MAX, MAX));

        genGeneral(genRandomIngredients(MAXN, 0, MAX));
        genIntegerSplit(genRandomIngredients(MAXN, 0, MAX));
        genExactSplit(genRandomIngredients(MAXN, 0, MAX));
        genBigX(genRandomIngredients(MAXN, 0, MAX));
        genAll1(genRandomIngredients(MAXN, 0, MAX));
        genAll2(genRandomIngredients(MAXN, 0, MAX));
        genExact(genRandomIngredients(MAXN, 0, MAX));

        genAll1(genRandomIngredients(MAXN, MAX, MAX));
        genAll2(genRandomIngredients(MAXN, MAX, MAX));
        genExact(genRandomIngredients(MAXN, MAX, MAX));

        genAll1(genAlZeros(MAXN));
        genAll2(genAlZeros(MAXN));
        genExact(genAlZeros(MAXN));
        genOverflows();
    }
}

