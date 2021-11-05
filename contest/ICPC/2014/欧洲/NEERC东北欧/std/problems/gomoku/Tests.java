/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem G. Gomoku                                              */
/*                                                                */
/* Original idea         Petr Mitrichev                           */
/* Problem statement     Petr Mitrichev                           */
/* Test set              Pavel Mavrin                             */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author                Pavel Mavrin                             */
/******************************************************************/

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.File;
import java.util.*;

public class Tests {
    int testNo = 1;

    public void printTest(int seed) {
        PrintWriter out = null;
        try {
            new File("tests").mkdir();
            out = new PrintWriter("tests/" + testNo / 100 + testNo % 100 / 10 + testNo % 10);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        }

        out.println(seed);

        out.close();
        testNo++;
    }


    Random rnd = new Random(219238948812818L);

    public void run() {
        for (int i = 0; i < 100; i++) {
            printTest(rnd.nextInt());
        }
    }

    public static void main(String[] args) {
        new Tests().run();
    }
}


