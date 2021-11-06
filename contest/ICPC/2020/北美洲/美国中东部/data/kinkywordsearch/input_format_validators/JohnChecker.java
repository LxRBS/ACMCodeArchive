import java.util.*;

// abstract checker

public class JohnChecker
{
	public static final int MINR = 1;
	public static final int MAXR = 10;
	public static final int MINC = 1;
	public static final int MAXC = 10;
	public static final char MINCH = 'A';
	public static final char MAXCH = 'Z';
	public static final int MINK = 0;
	public static final int MAXK = Integer.MAX_VALUE;
	public static final int MAXS = 100;

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
		int r, c, k;
		String line;
		int nLines=0;

        line = in.nextLine();
        nLines++;
        StringTokenizer st = new StringTokenizer(line);
        if (st.countTokens() != 2)
            printError(nLines, "number of values on line incorrect");
        r = nextInt(st);
        c = nextInt(st);
        checkIntBounds(r, MINR, MAXR, "r", nLines);
        checkIntBounds(c, MINC, MAXC, "c", nLines);

        for(int i=0; i<r; i++) {
            nLines++;
            line = in.nextLine();
            st = new StringTokenizer(line);
            if (st.countTokens() != c)
                printError(nLines, "number of values on line incorrect");
            for(int j=0; j<st.countTokens(); j++) {
                char ch = st.nextToken().charAt(0);
                checkCharBounds(ch, MINCH, MAXCH, "ch", nLines);
            }
        }
        nLines++;
        line = in.nextLine();
        st = new StringTokenizer(line);
        if (st.countTokens() != 1)
            printError(nLines, "number of values on line incorrect");
        k = nextInt(st);
        checkIntBounds(k, MINK, MAXK, "k", nLines);
        nLines++;
        line = in.nextLine();
        st = new StringTokenizer(line);
        if (st.countTokens() != 1)
            printError(nLines, "number of values on line incorrect");
        if (line.length() > MAXS) {
        	printError(nLines, "String too long");
        }
        for(int i=0; i<line.length(); i++) {
        	char ch = line.charAt(i);
            checkCharBounds(ch, MINCH, MAXCH, "ch", nLines);
        }
		if (in.hasNextLine())
			printError(nLines, "incorrect number of lines");
        System.exit(exitCode);
	}
}
