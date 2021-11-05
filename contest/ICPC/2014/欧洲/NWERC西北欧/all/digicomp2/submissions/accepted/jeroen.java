/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

import java.util.*;
import java.io.*;

public class jeroen {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] parts = in.readLine().split(" ");
		long N = Long.parseLong(parts[0]);
		int M = Integer.parseInt(parts[1]);
		char[] state = new char[M+1];
		out1 = new int[M+1];
		out2 = new int[M+1];
		for(int i = 1; i <= M; i++) {
			parts = in.readLine().split(" ");
			state[i] = parts[0].charAt(0);
			out1[i] = Integer.parseInt(parts[1]);
			out2[i] = Integer.parseInt(parts[2]);
		}

		nums = new Stack<Integer>();
		done = new boolean[M+1];
		done[0] = true;
		topsort(1);
		
		long[] incoming = new long[M+1];
		incoming[1] = N;
		while(!nums.isEmpty()) {
			int i = nums.pop();
			if(state[i] == 'L') {
				incoming[out1[i]] += (incoming[i] + 1) / 2;
				incoming[out2[i]] += incoming[i] / 2;
				if(incoming[i] % 2 == 1) state[i] = 'R';
			}
			else {
				incoming[out1[i]] += incoming[i] / 2;
				incoming[out2[i]] += (incoming[i] + 1) / 2;
				if(incoming[i] % 2 == 1) state[i] = 'L';
			}
		}
		String ret = new String(state);
		ret = ret.substring(1);
		System.out.println(ret);
	}

	static int[] out1, out2;
	static boolean[] done;
	static Stack<Integer> nums;

	public static void topsort(int i) {
		if(done[i]) return;
		topsort(out1[i]);
		topsort(out2[i]);
		done[i] = true;
		nums.add(i);
	}
}
