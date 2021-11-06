import java.util.*;

// abstract checker

public class JohnChecker
{
	public static final int MINCARS = 1;
	public static final int MAXCARS = 50;
	public static final int MINHOPPERS = 1;
	public static final int MAXHOPPERS = 100;
	public static final int MINCAPC = 1;
	public static final int MAXCAPC = 200;
	public static final int MINCAPH = 1;
	public static final int MAXCAPH = 2000000;

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

    public static void checkCharBounds(char x, char min, char max, String name, int nLines)
    {
        if (x < min || x > max)
            printError(nLines, "invalid " + name + " value: " + x);
    }

    public static void checkDoubleBounds(double x, double min, double max, String name, int nLines)
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
		int r, s, n;
		String line;
		int nLines=0;

        line = in.nextLine();
        nLines++;
        StringTokenizer st = new StringTokenizer(line);
        if (st.countTokens() != 3)
            printError(nLines, "number of values on line incorrect");
        r = nextInt(st);
        s = nextInt(st);
        n = nextInt(st);
        checkIntBounds(r, MINCARS, MAXCARS, "r", nLines);
        checkIntBounds(s, MINCARS, MAXCARS, "s", nLines);
        checkIntBounds(n, MINHOPPERS, MAXHOPPERS, "n", nLines);

        nLines++;
        line = in.nextLine();
        st = new StringTokenizer(line);
        if (st.countTokens() != r)
            printError(nLines, "number of values on line incorrect");
        for(int i=0; i<st.countTokens(); i++) {
            int val = nextInt(st);
            checkIntBounds(val, MINCAPC, MAXCAPC, "car capacity", nLines);
        }
        nLines++;
        line = in.nextLine();
        st = new StringTokenizer(line);
        if (st.countTokens() != s)
            printError(nLines, "number of values on line incorrect");
        for(int i=0; i<st.countTokens(); i++) {
            int val = nextInt(st);
            checkIntBounds(val, MINCAPC, MAXCAPC, "car capacity", nLines);
        }
        nLines++;
        line = in.nextLine();
        st = new StringTokenizer(line);
        if (st.countTokens() != n)
            printError(nLines, "number of values on line incorrect");
        for(int i=0; i<st.countTokens(); i++) {
            int val = nextInt(st);
            checkIntBounds(val, MINCAPH, MAXCAPH, "hopper capacity", nLines);
        }
		if (in.hasNextLine())
			printError(nLines, "incorrect number of lines");
        System.exit(exitCode);
	}
}
