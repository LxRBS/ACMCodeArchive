import java.util.*;
import java.io.*;

class Philipp_BR_On {
	public static void main(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String[] ncb = reader.readLine().split("\\s+");
		String[] idx = reader.readLine().split("\\s+");

		int n = Integer.parseInt(ncb[0]);
		int c = Integer.parseInt(ncb[1]);
		int b = Integer.parseInt(ncb[2]);

		boolean[] broken = new boolean[n];
		for(int i = 0; i < b; i++) {
			int z = Integer.parseInt(idx[i]);
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
