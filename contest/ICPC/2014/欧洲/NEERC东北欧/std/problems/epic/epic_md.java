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
/* Solution                                                       */
/*                                                                */
/* Author                Mikhail Dvorkin                          */
/******************************************************************/

import java.io.*;
import java.util.*;

public class epic_md {
	static final String MOVES = "RPS";
	static final int M = MOVES.length();
	
	int n;
	int[] move;
	int[][] next;
	List<Integer>[][] prev;
	int[][] diff;
	Map<List<Integer>, Integer> myMove = new HashMap<>();
	Map<List<Integer>, List<Integer>[]> myNext = new HashMap<>();
	Map<List<Integer>, Integer> id = new HashMap<>();
	List<List<Integer>> byId = new ArrayList<>();
	
	public void run() {
		n = in.nextInt();
		move = new int[n];
		next = new int[n][M];
		prev = new List[n][M];
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < M; k++) {
				prev[i][k] = new ArrayList<>();
			}
		}
		for (int i = 0; i < n; i++) {
			move[i] = MOVES.indexOf(in.next());
			for (int k = 0; k < M; k++) {
				next[i][k] = in.nextInt() - 1;
				prev[next[i][k]][k].add(i);
			}
		}
		diff = new int[n][n];
		for (int i = 0; i < n; i++) {
			Arrays.fill(diff[i], -1);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (move[i] == move[j] || diff[i][j] >= 0) {
					continue;
				}
				diff[i][j] = move[i];
				dfsDiff(i, j);
			}
		}
		List<Integer> init = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			init.add(i);
		}
		dfs(init);
		out.println(id.size());
		for (int i = 0; i < id.size(); i++) {
			List<Integer> list = byId.get(i);
			out.print(MOVES.charAt(myMove.get(list)));
			for (int k = 0; k < M; k++) {
				out.print(" ");
				out.print(id.get(myNext.get(list)[k]) + 1);
			}
			out.println();
		}
	}

	void dfs(List<Integer> list) {
		int m = Integer.MAX_VALUE;
		int v0 = list.get(0);
		for (int v : list) {
			for (int u : list) {
				if (diff[v][u] >= 0) {
					m = Math.min(m, diff[v][u]);
				}
			}
		}
		if (m == Integer.MAX_VALUE) {
			m = (move[v0] + 1) % M;
		} else {
			m %= M;
		}
		List<Integer>[] nextArray = new ArrayList[M];
		for (int k = 0; k < M; k++) {
			nextArray[k] = new ArrayList<>();
		}
		for (int v : list) {
			int u = next[v][m];
			nextArray[move[v]].add(u);
		}
		for (int k = 0; k < M; k++) {
			if (nextArray[k].isEmpty()) {
				nextArray[k] = list;
			} else {
				nextArray[k] = new ArrayList<>(new TreeSet<>(nextArray[k]));
			}
		}
		myMove.put(list, m);
		myNext.put(list, nextArray);
		id.put(list, id.size());
		byId.add(list);
		for (List<Integer> nextList : nextArray) {
			if (!id.containsKey(nextList)) {
				dfs(nextList);
			}
		}
	}

	void dfsDiff(int u, int v) {
		for (int k = 0; k < M; k++) {
			for (int i : prev[u][k]) {
				for (int j : prev[v][k]) {
					if (diff[i][j] >= 0) {
						continue;
					}
					diff[i][j] = (diff[u][v] / M + 1) * M + k;
					dfsDiff(i, j);
				}
			}
		}
	}

	private static String fileName = epic_md.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;
	
	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new File(inputFileName));
		out = new PrintWriter(outputFileName);
		new epic_md().run();
		in.close();
		out.close();
	}
}

