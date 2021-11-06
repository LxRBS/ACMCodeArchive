// translated from per.py by Tobi
import java.util.*;
import java.io.*;

public class per_badskip2 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int N = scanner.nextInt();
		long[] p = new long[N];
		for (int i = 0; i < N; i++) p[i] = scanner.nextLong();
		long lead = p[0];
		p[0] = ((long)-1) << 60;
		Arrays.sort(p);
		long gap = lead - p[N-1] + 1;
		long f = 1;
		long steps = 0;
		while (gap > 0) {
			long inc = Long.toBinaryString(f).length() - 1;
			long big = p[N-1] - p[N-2];
			long biginc = big * inc;
			if (productIsGreaterThanOrEqual(big, inc, gap) && inc != 0) {
				steps += gap + (gap-1)/inc;
				break;
			}
			gap -= inc*big;
			steps += (inc+1)*big;
			f += 1;
			N--;
		}
		System.out.println(steps - 1);
	}

	private static boolean productIsGreaterThanOrEqual(long b, long a, long c) {
		if (b==0) return c == 0;
		long cq = c / b;
		long cr = c % b;
		return a != cq ? a >= cq : cr >= 0; // ʘ‿ʘ whoops.
	}
}
