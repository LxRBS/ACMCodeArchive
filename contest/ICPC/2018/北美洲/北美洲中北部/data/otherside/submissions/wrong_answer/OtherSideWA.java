import java.util.*;

/**
 * Other Side
 *
 * @author David A. Poplawski
 */
public class OtherSideWA {

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
				else if (W == 0 && C == 0)
						System.out.println("YES");
				else if (W == 0) {
						if (S <= K && C <= 2*K)
							System.out.println("YES");
						else if (C <= K && S <= 2*K)
							System.out.println("YES");
						else
							System.out.println("NO");
				}
				else if (C == 0) {
						if (S <= K && W <= 2*K)
							System.out.println("YES");
						else if (W <= K && S <= 2*K)
							System.out.println("YES");
						else
							System.out.println("NO");
				}
				else if (S > K)
							System.out.println("NO");
				else
						if (W + C > 2*K)
							System.out.println("NO");
						else
							System.out.println("YES");

		} // end of main method

} // end of OtherSide class
