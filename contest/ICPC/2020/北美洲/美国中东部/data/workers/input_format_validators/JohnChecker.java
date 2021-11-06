import java.util.*;

// abstract checker

public class JohnChecker
{
	public static final int MINN = 1;
	public static final int MAXN = 50;
	public static final int MIND = 1;
	public static final int MAXD = 1000;

	public static int exitCode = 42;

	public static void printError(int line, String msg)
	{
		System.out.println("ERROR Line " + line + ": " + msg);
		exitCode = -1;
	}

	public static void checkIntBounds(int x, int min, int max, String name, int nLines)
	{
		if (x < min || x > max)
			printError(nLines, "invalid " + name + " value: " + x);
	}

	public static int nextInt(StringTokenizer st)
	{
		return Integer.parseInt(st.nextToken());
	}

	public static void main(String [] args)
	{
		Scanner in = new Scanner(System.in);
		int n;
		String line;
		int nLines=0;

		line = in.nextLine();
		nLines++;
		StringTokenizer st = new StringTokenizer(line);
		if (st.countTokens() != 1)
			printError(nLines, "number of values on line incorrect");
		n = nextInt(st);
		checkIntBounds(n, MINN, MAXN, "n", nLines);

		int i=0;
		while (in.hasNextLine() && i < 2*n) {
			nLines++;
			line = in.nextLine();
			st = new StringTokenizer(line);
			if (st.countTokens() != 2*n)
				printError(nLines, "number of values on line incorrect");
			for(int j=0; j<st.countTokens(); j++) {
				int d = nextInt(st);
				checkIntBounds(d, MIND, MAXD, "distance", nLines);
			}
			i++;
		}
		if (i < 2*n) 
			printError(nLines, "to few lines");
		if (in.hasNextLine())
			printError(nLines, "to many lines");
		System.exit(exitCode);
	}
}
