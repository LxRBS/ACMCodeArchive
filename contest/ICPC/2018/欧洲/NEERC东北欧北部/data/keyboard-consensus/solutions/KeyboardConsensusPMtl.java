import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * @author: pashka
 */
public class KeyboardConsensusPMtl {

	private int[] mem;

	void run() {
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
		int res = solve(pa, pb);
		List<Integer> moves = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			if (mem[(1 << n) - 1 - (1 << i)] == res) {
				moves.add(i);
			}
		}
		System.out.println(res + 1);
		System.out.println(moves.size());
		for (Integer move : moves) {
			System.out.print((move + 1) + " ");
		}
	}

	int solve(int[] pa, int[] pb) {
		int n = pa.length;
		mem = new int[1 << n];
		int[] ra = rev(pa);
		int[] rb = rev(pb);
		for (int i = 1; i < (1 << n); i++) {
			if (Integer.bitCount(i) == 1) {
				int j = 0;
				while ((i & (1 << j)) == 0) j++;
				mem[i] = j;
			} else {
				int z = -1;
				for (int j = 0; j < n; j++) {
					if ((i & (1 << j)) > 0) {
						int x = mem[i - (1 << j)];
						if (z == -1 ||
								((n - Integer.bitCount(i)) % 2 == 0 && ra[x] < ra[z]) ||
								((n - Integer.bitCount(i)) % 2 == 1 && rb[x] < rb[z])) {
							z = x;
						}
					}
				}
				mem[i] = z;
			}
		}
		return mem[(1 << n) - 1];
	}

	int[] rev(int[] p) {
		int n = p.length;
		int[] res = new int[n];
		for (int i = 0; i < n; i++) {
			res[p[i]] = i;
		}
		return res;
	}

	public static void main(String[] args) {
		new KeyboardConsensusPMtl().run();
	}

}
