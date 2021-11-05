/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem E. Epic Win!                                           */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Mikhail Dvorkin                          */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author                Mikhail Dvorkin                          */
/******************************************************************/

import java.io.*;
import java.util.*;
import java.util.Map.Entry;

public class Tests {
	private static File dir = new File("tests");
	private static String descsFilename = "description.txt";
	private int curTest = 1;
	private static boolean verbose = true;

	private String testName;
	private PrintWriter out;
	private static PrintWriter descs;
	private static long seed = 4243674435618678L;
	private Random r;
	
	final static int MAX = 100;
	final static String MOVES = "RPS";
	final static int M = MOVES.length();
	
	public void run() {
		{
			State a = new State(0);
			State b = new State(1);
			a.setNext(a, a, b);
			b.setNext(b, b, a);
			t("manual sample", a, b);
		}
		for (int i = 1; i <= 4; i++) {
			t("random", aRandom(i));
		}
		for (int i = 0; i < 3; i++) {
			State a = new State(i % 3);
			State b = new State((i + 1) % 3);
			State c = new State((i + 2) % 3);
			a.setNext(a, b, c);
			b.setNext(a, b, c);
			c.setNext(a, b, c);
			t("manual 1-move memory", a, b, c);
		}
		for (int t = 0; t < 3; t++) {
			State[][][] states = new State[3][3][3];
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int m = 0; m < 3; m++) {
						int move;
						switch (t) {
						case 0: move = i; break;
						case 1: move = m; break;
						case 2: move = r(); break;
						default: throw new RuntimeException();
						}
						if (t == 1) {
							move = r();
						}
						states[i][j][m] = new State(move);
					}
				}
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int m = 0; m < 3; m++) {
						for (int k = 0; k < 3; k++) {
							states[i][j][m].next[k] = states[j][m][k];
						}
					}
				}
			}
			t("3-move memory, type " + t, states[0][0][0]);
		}
		{
			State a = new State(1);
			State b = new State(2);
			State c = new State(2);
			a.setNext(c, a, c);
			b.setNext(a, b, c);
			c.setNext(c, b, b);
			t("manual", a, b, c);
		}
		{
			State a = new State(0);
			State b = new State(1);
			a.setNext(a, a, b);
			b.setNext(b, b, a);
			State a1 = new State(0);
			State b1 = new State(1);
			a1.setNext(a1, a1, b1);
			b1.setNext(b1, b1, a1);
			t("sample x2", a, a1);
		}
		{
			State a = new State(0);
			State b = new State(1);
			a.setNext(a, a, b);
			b.setNext(b, b, a);
			State a1 = new State(1);
			State b1 = new State(2);
			a1.setNext(a1, a1, b1);
			b1.setNext(b1, b1, a1);
			t("sample + sample'", a, a1);
		}
		{
			State a1 = new State(0);
			State b1 = new State(1);
			State c1 = new State(2);
			State a2 = new State(0);
			State b2 = new State(1);
			State c2 = new State(0);
			a1.setNext(b1, b1, b1);
			b1.setNext(c1, c1, c1);
			c1.setNext(c1, c1, c1);
			a2.setNext(b2, b2, b2);
			b2.setNext(c2, c2, c2);
			c2.setNext(c2, c2, c2);
			t("two similar paths", a1, a2);
		}
		t("cycle", aDeafCycle(0));
		t("cycle", aDeafCycle(0, 1));
		t("cycle", aDeafCycle(0, 1, 2));
		t("cycle", aDeafCycle(0, 0, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2));
		for (int s : new int[]{1, 2, 5, 10, MAX / 4, MAX / 2}) {
			List<State> states = new ArrayList<>();
			for (int i = 0; i < MAX / s; i++) {
				states.addAll(Arrays.asList(a(s)));
			}
			t("all types of FSMs of size " + s, states);
			
			states.clear();
			for (int i = 0; i < MAX / s; i++) {
				states.addAll(Arrays.asList(aRandom(s)));
			}
			t("random FSMs of size " + s, states);
			
			int m = MAX / (s + 1);
			states.clear();
			for (int i = 0; i < m; i++) {
				states.add(aDeafCycleRandom(s));
			}
			t("ternary + cycles of length " + s, aTernary(states));
			
			states.clear();
			for (int i = 0; i < m; i++) {
				states.add(a(s)[0]);
			}
			t("ternary + all types of size " + s, aTernary(states));
			
			states.clear();
			for (int i = 0; i < m; i++) {
				states.add(aRandom(s)[0]);
			}
			t("ternary + random of size " + s, aTernary(states));
		}
		t("random", aRandom(MAX / 3));
		for (int i = 7; i >= 0; i--) {
			t("random", aRandom(MAX - i));
		}
		for (int i = MAX - 3; i <= MAX; i++) {
			t("cycle", aDeafCycleRandom(i));
			t("polygon with diagonals", aPolygonDiagonals(i));
		}
		t("polygon", aPolygon(MAX));
		{
			State a = aPolygon(MAX / 2);
			State b = aPolygon(MAX / 2 - 1);
			t("2 almost equal polygons", a, b);
		}
		
	}
	
	State[] a(int n) {
		switch (r.nextInt(9)) {
		case 0: return aRandom(n);
		case 1: return new State[]{aDeafCycleRandom(n)};
		case 2: return new State[]{aPolygon(n)};
		case 3: return new State[]{aPolygonDiagonals(n)};
		default: return a(n);
		}
	}
	
	State[] aRandom(int n) {
		State[] states = new State[n];
		for (int i = 0; i < n; i++) {
			states[i] = new State(r.nextInt(M));
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < M; j++) {
				states[i].next[j] = states[r.nextInt(n)];
			}
		}
		return states;
	}
	
	State aDeafCycle(int... moves) {
		int n = moves.length;
		State[] states = new State[n];
		for (int i = 0; i < n; i++) {
			states[i] = new State(moves[i]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < M; j++) {
				states[i].next[j] = states[(i + 1) % n];
			}
		}
		return states[0];
	}

	State aDeafCycleRandom(int n) {
		int[] moves = new int[n];
		for (int i = 0; i < n; i++) {
			moves[i] = r();
		}
		return aDeafCycle(moves);
	}
	
	State aTernary(List<State> states) {
		if (states.size() == 1) {
			return states.get(0);
		}
		State s = new State(r());
		for (int k = 0; k < M; k++) {
			List<State> subList = states.subList(states.size() * k / M, states.size() * (k + 1) / M);
			if (subList.isEmpty()) {
				s.next[k] = s;
			} else {
				s.next[k] = aTernary(subList);
			}
		}
		return s;
	}
	
	State aPolygon(int n) {
		State[] states = new State[n];
		for (int i = 0; i < n; i++) {
			states[i] = new State(Integer.signum(i));
		}
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < M; k++) {
				states[i].next[k] = states[(i + Integer.signum(k)) % n];
			}
		}
		return states[0];
	}
	
	State aPolygonDiagonals(int n) {
		State[] states = new State[n];
		for (int i = 0; i < n; i++) {
			states[i] = new State(Integer.signum(i));
		}
		for (int i = 0; i < n; i++) {
			states[i].next[0] = states[(i + 1) % n];
			for (int k = 1; k < M; k++) {
				states[i].next[k] = states[r.nextInt(n)];
			}
		}
		return states[0];
	}
	
	int r() {
		return r.nextInt(M);
	}

	class State {
		int move;
		State[] next;
		
		public State(int move) {
			this.move = move;
			this.next = new State[M];
		}
		
		void setNext(State... states) {
			next = states.clone();
		}
	}

	private void t(String desc, Collection<State> states) {
		t(desc, states.toArray(new State[states.size()]));
	}

	private void t(String desc, State... states) {
		open();
		Map<State, Integer> id = new HashMap<>();
		if (desc.startsWith("manual")) {
			for (State state : states) {
				id.put(state, id.size());
			}
		} else {
			for (State state : states) {
				if (!id.containsKey(state)) {
					dfsId(state, id);
				}
			}
		}
		State[] s = new State[id.size()];
		for (Entry<State, Integer> entry : id.entrySet()) {
			s[entry.getValue()] = entry.getKey();
		}
		out.println(s.length);
		for (int i = 0; i < s.length; i++) {
			out.print(MOVES.charAt(s[i].move));
			for (int j = 0; j < M; j++) {
				out.print(" " + (id.get(s[i].next[j]) + 1));
			}
			out.println();
		}
		desc += ", N=" + s.length;
		descs.println(desc);
		if (verbose) {
			System.out.println(" " + desc + ".");
		}
		close();
	}

	private void dfsId(State state, Map<State, Integer> id) {
		id.put(state, id.size());
		for (State s : state.next) {
			if (!id.containsKey(s)) {
				dfsId(s, id);
			}
		}
	}

	private void open() {
		try {
			testName = "" + curTest / 10 + curTest % 10;
			out = new PrintWriter(new File(dir, testName));
			if (verbose) { 
				System.out.print("Generating " + testName + "...");
			}
		} catch (IOException e) {
			throw new RuntimeException("Unable to open " + testName + " for writing", e);
		}
	}

	private void close() {
		out.close();
		curTest++;
		r = new Random(seed);
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		dir.mkdirs();
		descs = new PrintWriter(new File(dir, descsFilename));
		new Tests().run();
		descs.close();
	}
}

