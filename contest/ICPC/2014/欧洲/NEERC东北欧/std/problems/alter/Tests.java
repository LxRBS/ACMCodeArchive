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
/* Tests                                                          */
/*                                                                */
/* Author                Egor Kulikov                             */
/******************************************************************/

import java.io.*;
import java.util.*;
import java.util.Map.Entry;

public class Tests {
	private static File dir = new File("tests");
	private int curTest = 1;
	private static boolean verbose = true;

	private String testName;
	private PrintWriter out;
	private Random r = new Random(5516681322906813814L);
	

	
	public void run() {
		test(2, 2);
		massTest(1, 3, 1, 3, 1d);
		massTest(48, 50, 48, 50, 1d);
		massTest(1, 3, 49, 50, 1d);
		massTest(4, 47, 4, 47, 25d / 44 / 44);
	}

	private void massTest(int fromRows, int toRows, int fromColumn, int toColumn, double probability) {
		for (int rows = fromRows; rows <= toRows; rows++) {
			for (int columns = fromColumn; columns <= toColumn; columns++) {
				if (r.nextDouble() < probability) {
					test(rows, columns);
				}
			}
		}
	}

	private void test(int rowCount, int columnCount) {
		open();
		out.println(rowCount + " " + columnCount);
		close();
	}

	private void open() {
		try {
			testName = "" + curTest / 10 + curTest % 10;
			out = new PrintWriter(new File(dir, testName));
			if (verbose) { 
				System.out.print("Generating " + testName + "...");
			}
		} catch (IOException e) {
			throw new RuntimeException("Unable to open " + testName + " for writing", e);
		}
	}

	private void close() {
		out.close();
		if (verbose) {
			System.out.println(" done.");
		}
		curTest++;
	}

	public static void main(String[] args) {
		Locale.setDefault(Locale.US);
		dir.mkdirs();
		new Tests().run();
	}
}

