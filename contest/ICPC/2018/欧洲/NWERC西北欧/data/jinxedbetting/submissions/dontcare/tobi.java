import java.io.*;
import java.util.*;

public class tobi {
	static int N;
	static long jeff, vals[] = new long[100000], steps = 0;
	static LinkedList<Pair> valFrequency = new LinkedList<>();
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		N = scanner.nextInt() - 1;
		jeff = scanner.nextLong();
		for (int i = 0; i < N; i++) vals[i] = scanner.nextLong();
		Arrays.sort(vals, 0, N);
		for (int i = 0; i < N/2; i++) {
			long tmp = vals[i];
			vals[i] = vals[N-1-i];
			vals[N-1-i] = tmp;
		}
		long lastVal = vals[0];
		int count = 0;
		for (int i = 0; i < N; i++, count++) if (lastVal != vals[i]) {
			valFrequency.add(new Pair(lastVal, count));
			lastVal = vals[i]; count = 0;
		}
		valFrequency.add(new Pair(lastVal, count));
		while (jeff >= valFrequency.peek().first) step(jeff - valFrequency.peek().first);
		System.out.println(steps-1);
	}
	static void step(long todo) {
		if (valFrequency.size() == 1 || valFrequency.get(1).first + 1 < valFrequency.peek().first) {
			valFrequency.add(1, new Pair(valFrequency.peek().first - 1, 0));
		}
		int curLargestCount = valFrequency.peek().second;
		long curLargestVal = valFrequency.peek().first;
		if (valFrequency.get(1).second == 0) {
			int logtwo = 0, tmp = curLargestCount;
			while (tmp >> 1 > 0) {
				logtwo++;
				tmp = tmp >> 1;
			}
			logtwo++;
			if (valFrequency.size() > 2) {
				todo = Math.min(todo, curLargestVal - valFrequency.get(2).first);
				if (curLargestCount == 1) todo = curLargestVal - valFrequency.get(2).first;
			}
			long howmuch = todo/logtwo - 1;
			if (howmuch > 0) { // combine steps
				steps += logtwo * howmuch;
				jeff -= logtwo * howmuch;
				valFrequency.pop();
				valFrequency.peek().second += curLargestCount;
				valFrequency.peek().first = curLargestVal - howmuch;
				return;
			}
		}
		// single step
		steps++; jeff--;
		if (curLargestCount == 1) {
			valFrequency.pop();
			valFrequency.peek().second++;
		} else {
			int shift = valFrequency.peek().second - valFrequency.peek().second / 2;
			valFrequency.peek().second /= 2;
			valFrequency.get(1).second += shift;
		}
	}
}

class Pair {
	public Long first;
	public Integer second;
	public Pair(Long first, Integer second) {
		this.first = first;
		this.second = second;
	}
}
