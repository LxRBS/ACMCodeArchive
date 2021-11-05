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
/* Checker                                                        */
/*                                                                */
/* Author                Mikhail Dvorkin                          */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {
	static final int MAX = 50000;
	static final String MOVES = "RPS";
	static final int M = MOVES.length();
	static final int ROUNDS = 1000000000;
	static final int ROUNDS_LOG = 32 - Integer.numberOfLeadingZeros(ROUNDS);
	static final int PERCENTAGE = 99;

	@Override
	public Outcome test(InStream inf, InStream ouf, @SuppressWarnings("unused") InStream ans) {
		FSM opponent = new FSM(inf, true);
		FSM player = new FSM(ouf, false);
		return check(opponent, player);
	}

	public static Outcome check(FSM opponent, FSM player) {
		int[][] oNext = new int[opponent.n][player.n];
		int[][] pNext = new int[opponent.n][player.n];
		int[][] score = new int[opponent.n][player.n];
		int[][] noNext = new int[opponent.n][player.n];
		int[][] npNext = new int[opponent.n][player.n];
		int[][] nscore = new int[opponent.n][player.n];
		int[] startO = new int[opponent.n];
		int[] startP = new int[opponent.n];
		int[] startS = new int[opponent.n];
		for (int i = 0; i < opponent.n; ++i) {
			startO[i] = i;
			startP[i] = 0;
			startS[i] = 0;
		}
		for (int k = 0; k <= ROUNDS_LOG; ++k) {
			if (k == 0) {
                		for (int o = 0; o < opponent.n; o++) {
                			for (int p = 0; p < player.n; p++) {
                				int oMove = opponent.move[o];
                				int pMove = player.move[p];
                				oNext[o][p] = opponent.next[o][pMove];
                				pNext[o][p] = player.next[p][oMove];
                				score[o][p] = (pMove - oMove + M + M / 2) % M > M / 2 ? 1 : 0;
                			}
                		}
                	} else {
        			for (int o = 0; o < opponent.n; o++) {
        				for (int p = 0; p < player.n; p++) {
        					int o1 = oNext[o][p];
        					int p1 = pNext[o][p];
        					noNext[o][p] = oNext[o1][p1];
        					npNext[o][p] = pNext[o1][p1];
        					nscore[o][p] = score[o][p] + score[o1][p1];
        				}
        			}
        			for (int o = 0; o < opponent.n; o++) {
        				for (int p = 0; p < player.n; p++) {
        					oNext[o][p] = noNext[o][p];
        					pNext[o][p] = npNext[o][p];
        					score[o][p] = nscore[o][p];
        				}
        			}
        		}
        		if (((ROUNDS >> k) & 1) != 0) {
                		for (int i = 0; i < opponent.n; i++) {
                			int o = startO[i];
                			int p = startP[i];
                			int s = startS[i];
        				int o1 = oNext[o][p];
        				int p1 = pNext[o][p];
        				s += score[o][p];
        				o = o1;
        				p = p1;
        				startO[i] = o;
        				startP[i] = p;
        				startS[i] = s;
        			}
        		}
		}
		int worstI = -1;
		int worstScore = ROUNDS + 1;
       		for (int i = 0; i < opponent.n; i++) {
       		        int s = startS[i];
       			if (s < worstScore) {
       				worstScore = s;
       				worstI = i;
       			}
       		}
		if (worstScore < 1L * ROUNDS * PERCENTAGE / 100) {
			return new Outcome(WA, String.format("Wins only %d rounds versus initial state %d", worstScore, worstI + 1));
		}
		return new Outcome(OK, String.format("Epic win in %d rounds (%d states in FSM)", worstScore, player.n));
	}

	static class FSM {
		int n;
		int[] move;
		int[][] next;

		public FSM(int n) { // used by stress
			this.n = n;
			move = new int[n];
			next = new int[n][M];
		}

		public FSM(InStream stream, boolean failOnError) {
			n = stream.nextInt();
			if (n < 1 || n > MAX) {
				throw new Outcome(failOnError ? FAIL : WA, String.format("Invalid number of states: %d", n));
			}
			move = new int[n];
			next = new int[n][M];
			for (int i = 0; i < n; i++) {
				String s = stream.nextToken();
				if (s.length() != 1 || !MOVES.contains(s)) {
					throw new Outcome(failOnError ? FAIL : PE, String.format("Invalid move \"%s\" in state %d", s, i + 1));
				}
				move[i] = MOVES.indexOf(s);
				for (int j = 0; j < M; j++) {
					next[i][j] = stream.nextInt() - 1;
					if (next[i][j] < 0 || next[i][j] >= n) {
						throw new Outcome(failOnError ? FAIL : WA, String.format("Invalid next state %d in state %d", next[i][j] + 1, i + 1));
					}
				}
			}
			if (!stream.seekEoF())
				throw new Outcome(failOnError ? FAIL : PE, String.format("Extra data in output file"));
		}
	}
}

