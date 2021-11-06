import java.util.*;

class Philipp {
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int n = s.nextInt();
		int c = s.nextInt();
		int b = s.nextInt();
		Set<Integer> broken = new TreeSet<>();
		for(int i = 0; i < b; i++) {
			int z = s.nextInt();
			broken.add(z-1);
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
			if(broken.contains(i) || c == 0) {
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
