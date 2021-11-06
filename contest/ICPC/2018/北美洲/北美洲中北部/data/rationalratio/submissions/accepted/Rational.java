import java.util.*;

/**
 * Rational - Find most reduced fraction corresponding to an infinitely
 * repeating decimal.
 *
 * @author David A. Poplawski
 */
public class Rational {

		public static void main(String [] args) {

				// set up scanner
				Scanner input = new Scanner (System.in);

				// get the number and repeat length
				String num = input.next();
				int replen = input.nextInt();

				// get the fixed part
				int numlen = num.length();
				String fixed = num.substring(0,numlen-replen);

				// get the repeat part
				int fixedlen = fixed.length();
				String rept = num.substring(num.length()-replen);

				// convert fixed part to fraction (whole/tens);
				int tenpower = fixedlen - fixed.indexOf('.') - 1;
				long whole = Long.parseLong(fixed.replaceAll("\\.",""));
				long tens = 1;
				while (tenpower > 0) {
						tens *= 10;
						tenpower -= 1;
				}

				// determine denominator of repeated part
				long repnum = Long.parseLong(rept);
				long saverepnum = repnum;
				long repden = 0;
				for (int i=0; i<replen; i+=1) {
						repden = repden*10 + 9;
				}
				repden = repden*tens;
				repnum = saverepnum;

				// compute sum of fixed part and repeating part fractions
				long numerator = whole*repden + tens*repnum;
				long denominator = tens*repden;

				// find gcd of numerator and demoninator
				long a = numerator;
				long b = denominator;
				while (b != 0) {
						long t = b;
						b = a % b;
						a = t;
				}
				b = a;

				// print answer
				System.out.printf("%d/%d\n", numerator/a, denominator/b);

		} // end of main method

} // end of Rational class
