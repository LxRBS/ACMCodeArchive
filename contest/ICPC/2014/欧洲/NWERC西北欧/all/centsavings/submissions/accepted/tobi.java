import java.io.*;
import java.util.*;

public class tobi {
	static int I, D;
       	static int prices[] = new int[2005];
	static int dp[][][] = new int[2005][21][2005];
	static int pSum[] = new int[2005];
	final static int UNKNOWN = -1;

	public static int ROUND(int x) {
		return ((((x)+5)/10)*10);
	}

	public static int rec(int lastDiv, int restDiv, int index) {
		if (index == I) return ROUND(pSum[I] - pSum[lastDiv]); // last item
		if (dp[lastDiv][restDiv][index] != UNKNOWN) return dp[lastDiv][restDiv][index]; // table lookup
		int best = pSum[I] + 10; // INF
		if (restDiv > 0) best = ROUND(pSum[index] - pSum[lastDiv]) + rec(index, restDiv - 1, index + 1); // place divider if possible
		best = Math.min(best, rec(lastDiv, restDiv, index + 1)); // don't place divider
		dp[lastDiv][restDiv][index] = best; // table store
		return best;
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		I = sc.nextInt();
		D = sc.nextInt();
		for (int i = 0; i < I; i++) prices[i] = sc.nextInt();
		for (int i = 0; i < I; i++) pSum[i+1] = prices[i] + pSum[i]; // partial sums
		for (int i = 0; i < I; i++) for (int j = 0; j <= D; j++) for (int k = 0; k < I; k++) dp[i][j][k] = UNKNOWN;
		System.out.println(rec(0, D, 0));
	}
}


