import java.util.Scanner;

public class MathTrade_John {

	public static int MAX = 100;

	public static String[] has = new String[MAX];
	public static String[] wants = new String[MAX];
	public static boolean[] used = new boolean[MAX];

	public static void main(String [] args)
	{
		int n;
		Scanner in = new Scanner(System.in);

		n = in.nextInt();
		for(int i=0; i<n; i++) {
			has[i] = in.next();
			has[i] = in.next();			// over write names
			wants[i] = in.next();
			used[i] = false;
		}
		int maxcycle = 0;
		for(int i=0; i<n; i++) {
			if (used[i])
				continue;
			String stop = has[i];
			String curr = wants[i];
			int cycle = 1;
			while(!curr.equals(stop)) {
				int j=find(curr, n);
				if (j == -1)
					break;
				curr = wants[j];
				cycle++;

			}
			if (curr.equals(stop) && cycle > maxcycle)
				maxcycle = cycle;
		}
		if (maxcycle > 0)
			System.out.println(maxcycle);
		else
			System.out.println("No trades possible");
	}

	public static int find(String s, int n)
	{
		for(int i=0; i<n; i++)
			if (has[i].equals(s))
				return i;
		return -1;
	}
}
