import java.io.*;
import java.util.*;

public class fredrik {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		Map<String, Integer> judges = new TreeMap<String, Integer>();
		for (int i = 0; i < n; i++) {
			String s = sc.next();
			if (judges.containsKey(s))
				judges.put(s, judges.get(s) + 1);
			else
				judges.put(s, 1);
		}
		int ret = 0;
		for (int i = 0; i < n; i++) {
			String s = sc.next();
			if (judges.containsKey(s)) {
				ret++;
				int x = judges.get(s);
				if (x == 1)
					judges.remove(s);
				else
					judges.put(s, x - 1);
			}
		}
		System.out.println(ret);
	}
}
