import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int c = Integer.valueOf(ps[1]);
		int b = Integer.valueOf(ps[2]);
		ps = in.readLine().split(" ");
		int[] z = new int[b];
		for(int i = 0; i < b; i++) z[i] = Integer.valueOf(ps[i]);

		// Greedily change to 1-bits as early as possible
		char prev = '0';
		int j = 0;
		StringBuilder ans = new StringBuilder();
		for(int i = 1; i <= n; i++) {
			// no need for more broken bits
			if(c == 0) {
				prev = '0';
				ans.append('0');
				continue;
			}
			// if this is broken, we need a 0
			if(i == z[j]) {
				if(prev == '1') c--;
				prev = '0';
				ans.append('0');
				j++;
				continue;
			}
			// for and even number the first bit should stay 0
			if(i == 1 && c % 2 == 0) {
				prev = '0';
				ans.append('0');
				continue;
			}
			// make a change!
			c--;
			if(prev == '0') {
				prev = '1';
				ans.append('1');
			} else {
				prev = '0';
				ans.append('0');
			}
		}
		System.out.println(ans);
	}
}
