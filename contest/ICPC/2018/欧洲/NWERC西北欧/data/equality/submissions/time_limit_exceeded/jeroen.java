import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String a = in.readLine();
		String b = in.readLine();

		// Parse to a tree
		Expr ea = parse(a);
		Expr eb = parse(b);

		//System.err.println(ea);
		//System.err.println(eb);

		// Evaluate twice, with shuffle being either sort or reverse sort
		// When both lead to the same list, the shuffles are the same
		System.out.println(Arrays.equals(eval(ea,false),eval(eb,false))
						   && Arrays.equals(eval(ea,true),eval(eb,true))
						   ? "equal" : "not equal");
	}

	public static int[] eval(Expr e, boolean shuffleReverse) {
		int len = e.length();
		int[] res = new int[len];
		e.eval(res, 0, shuffleReverse);
		return res;
	}

	public static Expr parse(String s) {
		parseS = s;
		parseI = 0;
		return parseExpr();
	}

	private static String parseS;
	private static int parseI;
	
	private static Expr parseExpr() {
		switch(parseS.charAt(parseI)) {
		case '[':
			return parseLst();
		case 'c':
			return parseConcat();
		case 's':
			if(parseS.charAt(parseI+1) == 'h') return parseShuffle();
			if(parseS.charAt(parseI+1) == 'o') return parseSorted();
		}
		// nooo :(
		System.out.println("nooo");
		return null;
	}

	private static int parseInt() {
		int num = 0;
		do {
			num *= 10;
			num += parseS.charAt(parseI) - '0';
			parseI++;
		} while('0' <= parseS.charAt(parseI) && parseS.charAt(parseI) <= '9');
		return num;
	}
	
	private static Expr parseLst() {
		List<Integer> nums = new ArrayList<Integer>();
		while(parseS.charAt(parseI) != ']') {
			parseI++;
			nums.add(parseInt());
		}
		parseI++;
		return new Lst(nums);
	}

	private static Expr parseConcat() {
		parseI += 7;
		Expr a = parseExpr();
		parseI++;
		Expr b = parseExpr();
		parseI++;
		return new Concat(a, b);
	}

	private static Expr parseShuffle() {
		parseI += 8;
		Expr a = parseExpr();
		parseI++;
		return new Shuffle(a);
	}

	private static Expr parseSorted() {
		parseI += 7;
		Expr a = parseExpr();
		parseI++;
		return new Sorted(a);
	}
}

interface Expr {
	public void eval(int[] res, int i, boolean shuffleReverse);
	public int length();
}

class Lst implements Expr {
	private List<Integer> nums;

	public Lst(List<Integer> nums) {
		this.nums = nums;
	}
	
	public void eval(int[] res, int i, boolean shuffleReverse) {
		for(int x : nums)
			res[i++] = x;
	}

	public int length() {
		return nums.size();
	}

	public String toString() {
		return nums.toString();
	}
}

class Shuffle implements Expr {
	private Expr a;
	private int len = -1;

	public Shuffle(Expr a) {
		this.a = a;
	}
	
	public void eval(int[] res, int i, boolean shuffleReverse) {
		a.eval(res, i, shuffleReverse);
		int j = i + a.length();
		Arrays.sort(res, i, j);
		if(shuffleReverse) {
			for(int k = i; k < i + j - k - 1; k++) {
				int tmp = res[k];
				res[k] = res[i + j - k - 1];
				res[i + j - k - 1] = tmp;
			}
		}
	}

	public int length() {
		if(len == -1)
			len = a.length();
		return len;
	}

	public String toString() {
		return "shuffle(" + a + ")";
	}
}

class Sorted implements Expr {
	private Expr a;
	private int len = -1;

	public Sorted(Expr a) {
		this.a = a;
	}
	
	public void eval(int[] res, int i, boolean shuffleReverse) {
		a.eval(res, i, shuffleReverse);
		Arrays.sort(res, i, i + a.length());
	}

	public int length() {
		if(len == -1)
			len = a.length();
		return len;
	}

	public String toString() {
		return "sorted(" + a + ")";
	}
}

class Concat implements Expr {
	private Expr a, b;
	private int len = -1;

	public Concat(Expr a, Expr b) {
		this.a = a;
		this.b = b;
	}
	
	public void eval(int[] res, int i, boolean shuffleReverse) {
		a.eval(res, i, shuffleReverse);
		b.eval(res, i + a.length(), shuffleReverse);
	}

	public int length() {
		if(len == -1)
			len = a.length() + b.length();
		return len;
	}

	public String toString() {
		return "concat(" + a + "," + b + ")";
	}
}
