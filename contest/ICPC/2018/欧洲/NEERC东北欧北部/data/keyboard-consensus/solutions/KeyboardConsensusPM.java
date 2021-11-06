import java.util.Arrays;
import java.util.Scanner;

/**
 * @author: pashka
 */
public class KeyboardConsensusPM {

	private void run() {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] pa = new int[n];
		for (int i = 0; i < n; i++) {
			pa[i] = in.nextInt() - 1;
		}
		int[] pb = new int[n];
		for (int i = 0; i < n; i++) {
			pb[i] = in.nextInt() - 1;
		}
		boolean[] z = new boolean[n];
		int res = solve(pa, pb, z);
		int[] ans = new int[n];
		int ansN = 0;
		for (int i = 0; i < n; i++) {
			z[i] = true;
//			System.out.println((i + 1) + " " + solve(pb, pa, z));
			if (solve(pb, pa, z) == res) {
				ans[ansN++] = i;
			}
			z[i] = false;
		}
		System.out.println(res + 1);
		System.out.println(ansN);
		for (int i = 0; i < ansN; i++) {
			System.out.print((ans[i] + 1) + " ");
		}
		System.out.println();
	}

	private int solve(int[] pa, int[] pb, boolean[] z) {
		z = z.clone();
		int res;
		int n = 0;
		for (int i = 0; i < z.length; i++) if (!z[i]) n++;
		if (n % 2 == 0) {
			res = solve2(pa, pb, z);
		} else {
			int res1 = solve2(pa, pb, z);
			z[res1] = true;
			int res2 = solve2(pb, pa, z);
			res = -1;
			for (int i = 0; i < z.length; i++) {
				if (pa[i] == res1 || pa[i] == res2) {
					res = pa[i];
					break;
				}
			}
		}
		return res;
	}

	private int solve2(int[] pa, int[] pb, boolean[] z) {
		z = z.clone();
		int ia = pa.length - 1;
		int ib = pb.length - 1;
		int n = 0;
		for (int i = 0; i < z.length; i++) if (!z[i]) n++;
		for (int i = 0; i < n - 1; i++) {
			if (i % 2 == 0) {
				while (z[pa[ia]]) ia--;
				z[pa[ia]] = true;
			} else {
				while (z[pb[ib]]) ib--;
				z[pb[ib]] = true;
			}
		}
		for (int i = 0; i < z.length; i++) {
			if (!z[i]) return i;
		}
		return -1;
	}

	private int[] rev(int[] p) {
		int n = p.length;
		int[] res = new int[n];
		for (int i = 0; i < n; i++) {
			res[p[i]] = i;
		}
		return res;
	}

	public static void main(String[] args) {
		new KeyboardConsensusPM().run();
	}

}
