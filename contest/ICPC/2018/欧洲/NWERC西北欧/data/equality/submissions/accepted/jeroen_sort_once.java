import java.util.*;
import java.io.*;

public class jeroen_sort_once
{
	public static void main(String[] args) throws Exception
	{
		boolean visualize = (args.length > 0 && "visualize".equals(args[0]));

		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String a = in.readLine();
		String b = in.readLine();

		// Parse to a tree
		Expr ea = parse(a);
		Expr eb = parse(b);
		if (visualize) {
			System.out.println("digraph G {");
			ea.visualize();
			eb.visualize();
		}

		//System.err.println(ea);
		//System.err.println(eb);

		// Evaluate twice, with shuffle being either sort or reverse sort
		// When both lead to the same list, the shuffles are the same
		int[] eaEval1 = eval(ea, false);
		int[] ebEval1 = eval(eb, false);
		int[] eaEval2 = eval(ea, true);
		int[] ebEval2 = eval(eb, true);
		boolean match1 = Arrays.equals(eaEval1, ebEval1);
		boolean match2 = Arrays.equals(eaEval2, ebEval2);
		boolean match = match1 && match2;
		if (visualize) {
			System.out.println("node_" + System.identityHashCode(eaEval1) + " -> node_" + System.identityHashCode(ea) + ";");
			System.out.println("node_" + System.identityHashCode(eaEval2) + " -> node_" + System.identityHashCode(ea) + ";");
			System.out.println("node_" + System.identityHashCode(ebEval1) + " -> node_" + System.identityHashCode(eb) + ";");
			System.out.println("node_" + System.identityHashCode(ebEval2) + " -> node_" + System.identityHashCode(eb) + ";");
			String color1 = match1 ? "limegreen" : "orange";
			String color2 = match2 ? "limegreen" : "orange";
			System.out.println("node_" + System.identityHashCode(eaEval1) + "[label=\"" + arrayAbbrev(eaEval1) + "\", shape=box, style=filled, fillcolor=" + color1 + "]");
			System.out.println("node_" + System.identityHashCode(eaEval2) + "[label=\"" + arrayAbbrev(eaEval2) + "\", shape=box, style=filled, fillcolor=" + color2 + "]");
			System.out.println("node_" + System.identityHashCode(ebEval1) + "[label=\"" + arrayAbbrev(ebEval1) + "\", shape=box, style=filled, fillcolor=" + color1 + "]");
			System.out.println("node_" + System.identityHashCode(ebEval2) + "[label=\"" + arrayAbbrev(ebEval2) + "\", shape=box, style=filled, fillcolor=" + color2 + "]");
			System.out.println("}");
		} else {
			System.out.println(match ? "equal" : "not equal");
		}
	}

	public static String arrayAbbrev(int[] arr) {
		String ret = "[";
		if (arr.length < 12) {
			for (int i = 0; i < arr.length; i++) {
				if (i != 0) ret += ", ";
				ret += arr[i];
			}
		} else {
			for (int i = 0; i < 5; i++) {
				if (i != 0) ret += ", ";
				ret += arr[i];
			}
			ret += ", ...";
			for (int i = arr.length - 5; i < arr.length; i++) {
				ret += ", " + arr[i];
			}
		}
		return ret + "]";
	}

	public static int[] eval(Expr e, boolean shuffleReverse) {
		int len = e.length();
		int[] res = new int[len];
		e.eval(res, 0, shuffleReverse, false);
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
	public void eval(int[] res, int i, boolean shuffleReverse, boolean sortedLater);
	public void visualize();
	public int length();
}

class Lst implements Expr {
	private List<Integer> nums;

	public Lst(List<Integer> nums) {
		this.nums = nums;
	}
	
	public void eval(int[] res, int i, boolean shuffleReverse, boolean sortedLater) {
		for(int x : nums)
			res[i++] = x;
	}

	public int length() {
		return nums.size();
	}

	public String toString() {
		return nums.toString();
	}

	public void visualize() {
		System.out.println("node_" + System.identityHashCode(this) + "[label=\"" + jeroen_sort_once.arrayAbbrev(nums.stream().mapToInt(i -> i).toArray()) + "\"]");
	}
}

class Shuffle implements Expr {
	private Expr a;
	private int len = -1;

	public Shuffle(Expr a) {
		this.a = a;
	}
	
	public void eval(int[] res, int i, boolean shuffleReverse, boolean sortedLater) {
		a.eval(res, i, shuffleReverse, true);
		if(!sortedLater) {
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
	}

	public int length() {
		if(len == -1)
			len = a.length();
		return len;
	}

	public String toString() {
		return "shuffle(" + a + ")";
	}

	public void visualize() {
		System.out.println("node_" + System.identityHashCode(this) + "[color=gold,penwidth=3,label=\"shuffle\"];");
		System.out.println("node_" + System.identityHashCode(this) + " -> node_" + System.identityHashCode(a) + ";");
		a.visualize();
	}
}

class Sorted implements Expr {
	private Expr a;
	private int len = -1;

	public Sorted(Expr a) {
		this.a = a;
	}
	
	public void eval(int[] res, int i, boolean shuffleReverse, boolean sortedLater) {
		a.eval(res, i, shuffleReverse, true);
		if(!sortedLater)
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

	public void visualize() {
		System.out.println("node_" + System.identityHashCode(this) + "[color=darkorchid1,penwidth=3,label=\"sorted\"];");
		System.out.println("node_" + System.identityHashCode(this) + " -> node_" + System.identityHashCode(a) + ";");
		a.visualize();
	}
}

class Concat implements Expr {
	private Expr a, b;
	private int len = -1;

	public Concat(Expr a, Expr b) {
		this.a = a;
		this.b = b;
	}
	
	public void eval(int[] res, int i, boolean shuffleReverse, boolean sortedLater) {
		a.eval(res, i, shuffleReverse, sortedLater);
		b.eval(res, i + a.length(), shuffleReverse, sortedLater);
	}

	public int length() {
		if(len == -1)
			len = a.length() + b.length();
		return len;
	}

	public String toString() {
		return "concat(" + a + "," + b + ")";
	}

	public void visualize() {
		System.out.println("node_" + System.identityHashCode(this) + "[color=dodgerblue3,penwidth=3,label=\"concat\"];");
		System.out.println("node_" + System.identityHashCode(this) + " -> node_" + System.identityHashCode(a) + ";");
		System.out.println("node_" + System.identityHashCode(this) + " -> node_" + System.identityHashCode(b) + ";");
		a.visualize();
		b.visualize();
	}
}
