import java.util.*;

/**
 * Other Side
 *
 * @author David A. Poplawski
 */
public class OtherSideWATwo {

		public static void main(String [] args) {

				Scanner input = new Scanner(System.in);
				int W = input.nextInt();
				int S = input.nextInt();
				int C = input.nextInt();
				int K = input.nextInt();

				if (K == 0)
						System.out.println("NO");
				else if (S == 0)
						System.out.println("YES");
				else if (W+C == 0)
						System.out.println("YES");
				else if (W+S+C <= K)
						System.out.println("YES");
				else if (S <= K && W+C <= 2*K)
						System.out.println("YES");
				else if (W+C <= K && S <= 2*K)
						System.out.println("YES");
				else
						System.out.println("NO");

		} // end of main method

} // end of OtherSide class
