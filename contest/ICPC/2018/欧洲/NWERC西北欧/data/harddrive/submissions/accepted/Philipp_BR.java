import java.util.*;
import java.io.*;

class Philipp_BR {
	public static void main(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String[] ncb = reader.readLine().split("\\s+");
		String[] idx = reader.readLine().split("\\s+");

		int n = Integer.parseInt(ncb[0]);
		int c = Integer.parseInt(ncb[1]);
		int b = Integer.parseInt(ncb[2]);

		Set<Integer> broken = new TreeSet<>();
		for(int i = 0; i < b; i++) {
			int z = Integer.parseInt(idx[i]);
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
