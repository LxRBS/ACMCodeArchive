/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem A. Alter Board                                         */
/*                                                                */
/* Original idea         Egor Kulikov                             */
/* Problem statement     Egor Kulikov                             */
/* Test set              Egor Kulikov                             */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

public class alter_gk {
    static Scanner in;
    static PrintWriter out;

    void run() {
        int n = in.nextInt();
        int m = in.nextInt();
        out.println(n / 2 + m / 2);
        for (int i = 1; i <= n / 2; i++) {
            out.println(i * 2 + " " + 1 + " " + i * 2 + " " + m);
        }
        for (int i = 1; i <= m / 2; i++) {
            out.println(1 + " " + i * 2 + " " + n + " " + i * 2);
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("alter.in"));
        out = new PrintWriter("alter.out");

        new alter_gk().run();

        in.close();
        out.close();
    }
}

