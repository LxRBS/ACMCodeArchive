import java.util.*;

class Philipp_On {
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int n = s.nextInt();
		int c = s.nextInt();
		int b = s.nextInt();
		boolean[] broken = new boolean[n];
		for(int i = 0; i < b; i++) {
			int z = s.nextInt();
			broken[z-1] = true;
		}

		int i;
		if(c % 2 == 0) {
			System.out.print(0);
			i = 1;
		} else {
			System.out.print(10);
			c--;
			i = 2;
		}
		for(; i < n; i++) {
			if(broken[i] || c == 0) {
				System.out.print(0);
			} else {
				System.out.print(10);
				c -= 2;
				i++;
			}
		}
		System.out.println();
	}
}
