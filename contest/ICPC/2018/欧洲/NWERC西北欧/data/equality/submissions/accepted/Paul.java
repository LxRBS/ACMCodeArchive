import java.util.*;

class Parser {
	char[] prog;
	int[] match;
	int[] depth;
	List<Object> result = new ArrayList<Object>();
	
	Parser(String str) {
		prog = str.toCharArray();
		match = new int[prog.length];

		int[] stack = new int[prog.length];
		int top = -1;
		for (int i = 0; i < prog.length; i++) {
			char c = prog[i];
			if (c == ',' || c == ')' || c == ']') {
				int j = stack[top--];
				match[j] = i;
			}
			if (c == ',' || c == '(' || c == '[') {
				stack[++top] = i;
			}
		}
	}
	
	List<Integer> parseNumbers(int from, int to) {
		String str = new String(prog, from, to-from);
		StringTokenizer st = new StringTokenizer(str, "concatshufflesorted[](),");
		List<Integer> result = new ArrayList<Integer>();
		while (st.hasMoreTokens()) {
			result.add(Integer.parseInt(st.nextToken()));
		}
		return result;
	}

	void parseRecursive(int from, int to) {
		if (prog[from] == '[') {
			result.addAll(parseNumbers(from,to));
		} else if (prog[from] == 'c') {
			int mid = match[from+6];
			parseRecursive(from+7, mid);
			parseRecursive(mid+1, to-1);
		} else if (prog[from] == 's') {
			List<Integer> values = parseNumbers(from,to);
			Collections.sort(values);
			
			if (prog[from+1] == 'h' && values.get(0) != values.get(values.size()-1)) {
				result.add(values);
			} else {
				result.addAll(values);
			}
		} else {
			throw new RuntimeException();
		}
	}
	
	List<Object> parse() {
		parseRecursive(0, prog.length);
		return result;
	}
}

public class Paul {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		List<Object> a = new Parser(sc.next()).parse();
		List<Object> b = new Parser(sc.next()).parse();
		if (!a.equals(b)) System.out.print("not ");
		System.out.println("equal");
	}
}
