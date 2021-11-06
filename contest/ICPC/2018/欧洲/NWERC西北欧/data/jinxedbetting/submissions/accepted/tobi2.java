import java.io.*;
import java.util.*;

public class tobi2 {
	static int N;
	static long jeff, vals[] = new long[100000], steps = 0;
	static long[] p1 = new long[1000000];
	static  int[] p2 = new  int[1000000];
	static int size = 0;
	public static void main(String[] args) throws Exception {
		BufferedReader bufread = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.valueOf(bufread.readLine()) - 1;
		String[] nums = bufread.readLine().split(" ");
		jeff = Long.valueOf(nums[0]);
		for (int i = 0; i < N; i++) vals[i] = Long.valueOf(nums[1+i]);
		Arrays.sort(vals, 0, N);
		long lastVal = vals[0];
		int count = 0;
		for (int i = 0; i < N; i++, count++) if (lastVal != vals[i]) {
			p1[size] = lastVal;
			p2[size++] = count;
			lastVal = vals[i];
			count = 0;
		}
		p1[size] = lastVal;
		p2[size++] = count;
		while (jeff >= p1[size - 1]) step(jeff - p1[size - 1]);
		System.out.println(steps-1);
	}
	static void step(long todo) {
		if (size == 1 || p1[size - 2] + 1 < p1[size - 1]) {
			long p1Tmp = p1[size - 1];
			int p2Tmp = p2[size - 1];
			size--;
			p1[size] = p1Tmp - 1;
			p2[size++] = 0;
			p1[size] = p1Tmp;
			p2[size++] = p2Tmp;
		}
		int curLargestCount = p2[size - 1];
		long curLargestVal = p1[size - 1];
		if (p2[size - 2] == 0) {
			int logtwo = 0, tmp = curLargestCount;
			while (tmp >> 1 > 0) {
				logtwo++;
				tmp = tmp >> 1;
			}
			logtwo++;
			if (size > 2) {
				todo = Math.min(todo, curLargestVal - p1[size - 3]);
				if (curLargestCount == 1) todo = curLargestVal - p1[size - 3];
			}
			long howmuch = todo/logtwo - 1;
			if (howmuch > 0) { // combine steps
				steps += logtwo * howmuch;
				jeff -= logtwo * howmuch;
				size--;
				p2[size - 1] += curLargestCount;
				p1[size - 1] = curLargestVal - howmuch;
				return;
			}
		}
		// single step
		steps++; jeff--;
		if (curLargestCount == 1) {
			size--;
			p2[size - 1]++;
		} else {
			int shift = p2[size - 1] - p2[size - 1] / 2;
			p2[size - 1] /= 2;
			p2[size - 2] += shift;
		}
	}
}
