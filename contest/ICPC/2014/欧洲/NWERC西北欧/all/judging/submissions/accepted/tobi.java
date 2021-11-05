// slowest solution I can think of that should still be accepted
import java.io.*;
import java.util.*;

public class tobi {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int N = sc.nextInt();
		List<String> list = new ArrayList<>();
		for (int i = 0; i < N; i++) {
			list.add(sc.next());
		}
		List<String> list2 = new ArrayList<>();
		for (int i = 0; i < N; i++) {
			list2.add(sc.next());
		}

		Collections.sort(list);
		Collections.sort(list2);

		int totalCnt = 0;
		int ptr = 0, ptr2 = 0;
		while (ptr < N && ptr2 < N) {
			if (list.get(ptr).equals(list2.get(ptr2))) {
				totalCnt++;
				ptr++;
				ptr2++;
			} else if (list.get(ptr).compareTo(list2.get(ptr2)) < 0) {
				ptr++;
			} else {
				ptr2++;
			}
		}

		System.out.println(totalCnt);
	}
}
