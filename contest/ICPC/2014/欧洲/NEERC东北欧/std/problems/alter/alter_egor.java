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
/* Author                Egor Kulikov                             */
/******************************************************************/

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * @author egor@egork.net
 */
public class alter_egor {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new FileInputStream("alter.in"));
        PrintWriter out = new PrintWriter(new FileOutputStream("alter.out"));
        int rowCount = in.nextInt();
        int columnCount = in.nextInt();
        out.println(rowCount / 2 + columnCount / 2);
        for (int i = 2; i <= rowCount; i += 2) {
            out.println(i + " 1 " + i + " " + columnCount);
        }
        for (int i = 2; i <= columnCount; i += 2) {
            out.println("1 " + i + " " + rowCount + " " + i);
        }
        out.close();
    }
}

