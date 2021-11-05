/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

import java.util.*;
import java.io.*;

public class jeroen {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		long L = sc.nextLong();
		long[][] dst = new long[N][N];
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				dst[i][j] = sc.nextLong();

		// Meet in the middle approach, try to make a route
		// from 0 to midpoint in two distinct ways
		boolean possible = false;
		for(int midpoint = 1; midpoint < N; midpoint++) {
			// Loop over every set of (N-2)/2 nodes
			int half = (N - 2) / 2;
			for(int mask = 0; mask < (1<<N); mask++) {
				if((mask & 1) > 0)             continue; // Contains start
				if((mask & (1<<midpoint)) > 0) continue; // Contains midpoint
				if(countbits(mask) != half)    continue; // Number of nodes not correct

				// For this set of half of the points, store all possible lengths
				HashSet<Long> found = new HashSet<Long>();
			
				for(int k = 0; k < 2; k++) {
					int numnodes = (N - 2 + k) / 2;
					// Find all current nodes (those in mask for k = 0,
					// or those not in mask for k = 1)
					int[] curroute = new int[numnodes];
					int idx = 0;
					for(int i = 1; i < N; i++) {
						if(i == midpoint) continue;
						if((k == 0) == ((mask & (1<<i)) > 0))
							curroute[idx++] = i;
					}
					if(idx != numnodes) System.out.println("Error");
				
					// Loop over all permutations
					do {
						// Find the length
						long len = 0;
						if(numnodes > 0) {
							len += dst[0][curroute[0]];
							len += dst[curroute[numnodes-1]][midpoint];
						} else {
							len += dst[0][midpoint];
						}
						for(int i = 0; len < L && i < numnodes - 1; i++)
							len += dst[curroute[i]][curroute[i+1]];
						if(len > L) continue; // Can never lead to a correct route
						
						if(k == 0) {
							// Insert into list of found lengths
							found.add(len);
						}
						else {
							// Check if we can match this with an opposite route
							if(found.contains(L - len))
								possible = true;
						}
					} while(NextPermutation(curroute));
				}
			}
		}
		
		System.out.println(possible ? "possible" : "impossible");

	}

	public static int countbits(int i) {
		int ret = 0;
		while(i > 0) {
			ret += i & 1;
			i >>= 1;
		}
		return ret;
	}

	public static boolean NextPermutation(int[] array)
	{
		for (int i = array.length - 2; i >= 0; i--) {
			if (array[i] < array[i + 1]) {
				int j = array.length - 1;
				while (array[i] >= array[j])
					j--;
				Swap(array, i, j);
				ArrayReverse(array, i + 1, array.length - i - 1);
				return true;
			}
		}
		return false;
	}

	public static void ArrayReverse(int[] array, int start, int length) {
		for(int i = 0; i < length / 2; i++) {
			Swap(array, start + i, start + length - i - 1);
		}
	}

	public static void Swap(int[] array, int i, int j) {
		int tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}
