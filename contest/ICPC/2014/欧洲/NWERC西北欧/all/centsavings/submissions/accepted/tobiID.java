import java.io.*;
import java.util.*;

public class tobiID {
	static int I, D;
       	static int prices[] = new int[2005];
	static int dp[] = new int[21];
	static int pSum[] = new int[2005];

	public static int ROUND(int x) {
		return ((((x)+5)/10)*10);
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		I = sc.nextInt();
		D = sc.nextInt();
		for (int i = 0; i < I; i++) prices[i] = sc.nextInt();
		dp[0] = 0; // cost is zero with 0 divider
		for (int i = 1; i < D+1; i++) dp[i] = Integer.MAX_VALUE/2;
		for (int i = 0; i < I; i++) {
			for (int j = D; j >= 1; j--) dp[j] = Math.min(dp[j] + prices[i], ROUND(dp[j - 1] + prices[i])); // either just add item or place divider after item
			dp[0] += prices[i]; // no divider, no choice
		}
		int mini = Integer.MAX_VALUE/2;
		for (int i = 0; i < D+1; i++) mini = Math.min(mini, dp[i]);
		System.out.println(ROUND(mini));
	}
}
