import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.valueOf(in.readLine());
		int[] c = new int[n];
		String[] ps = in.readLine().split(" ");
		for(int i = 0; i < n; i++)
			c[i] = Integer.valueOf(ps[i]);

		// Sorting is always the solution
		Arrays.sort(c);
		double ans = 1;
		for(int i = 0; i < n; i++) {
			if(c[i] > i + 1) {
				System.out.println("impossible");
				return;
			}
			ans = Math.min(ans, (double)c[i] / (i + 1));
		}
		System.out.println(ans);
	}
}
