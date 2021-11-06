// translated from per.py by Tobi
import java.util.*;
import java.io.*;

public class per_badskip {
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
			if ((big > gap && inc != 0) || biginc * inc >= gap || (big != 0 && biginc/big != inc)) {
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
}
