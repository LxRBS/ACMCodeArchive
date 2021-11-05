import java.util.*;
import java.io.*;

class r {
	public r(long a, long b, long c, long d) {
		el[0] = a;
		el[1] = b;
		el[2] = c;
		el[3] = d;
	}
	public long el[] = new long[4];
}

public class tobi {

	public static final long INF = (2220000000L);
	public static long N, D, c[][] = new long[2][100000], orig[][] = new long[2][100000], m[] = new long[2];

	public static boolean cut(r a, long o1, long o2, long o3, long o4) {
		r b = new r(o1, o2, o3, o4);
		for(int i = 0; i < 2; i++) if (a.el[0+2*i] > b.el[1+2*i] || b.el[0+2*i] > a.el[1+2*i]) return false; // empty
		for(int i = 0; i < 2; i++) {
			a.el[0+2*i] = Math.max(a.el[0+2*i], b.el[0+2*i]);
			a.el[1+2*i] = Math.min(a.el[1+2*i], b.el[1+2*i]);
		}
		return true;
	}

	public static long dist(long a, long b) {
		long total = 0;
		for(int i = 0; i < N; i++) total += Math.abs(orig[0][i]-a) + Math.abs(orig[1][i]-b);
		return total;
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextLong();
		for(int i = 0; i < N; i++) for(int j = 0; j < 2; j++) c[j][i] = sc.nextLong();
		for(int i = 0; i < N; i++) for(int j = 0; j < 2; j++) orig[j][i] = c[j][i];
		D = sc.nextLong();
		r cur = new r( -INF, INF, -INF, INF );
		boolean poss = true;
		for(int i = 0; i < N; i++) poss &= cut(cur, c[0][i]-(c[1][i]+D), c[0][i]-(c[1][i]-D), c[0][i]+c[1][i]-D, c[0][i]+c[1][i]+D);
		if (!poss) System.out.println("impossible");
		else {
			for(int i = 0; i < 2; i++) Arrays.sort(c[i], 0, (int)N);
			for(int i = 0; i < 2; i++) m[i] = c[i][(int) (N/2)];
			boolean inside = cut(cur, m[0]-m[1], m[0]-m[1], m[0]+m[1], m[0]+m[1]);
			if (!inside) {
				long best = INF*INF;
				for(int j = 0; j < 4; j++){
					long minix = -INF;
					long maxix = INF;
					int factor = j < 2 ? 1 : -1;
					for(int i = 0; i < 52; i++) {
						if (minix + 2 >= maxix) break;
						long l = minix + (maxix-minix)/3, r = minix + ((maxix-minix)*2)/3;
						if (dist(l,factor*(l-cur.el[j])) > dist(r,factor*(r-cur.el[j]))) minix = l;
						else maxix = r;
					}
					for (long oldx = minix; oldx < maxix+1; oldx++) {
						long newx = oldx;
						long newy = factor*(oldx-cur.el[j]);
						long newL = newx + factor*newy;
						newL = Math.max(newL, cur.el[2 - 2*(j/2)]);
						newL = Math.min(newL, cur.el[3 - 2*(j/2)]);
						newy = factor*(newL - cur.el[j]+1)/2;
						for (int k = -1; k < 2; k++) { // avoid rounding issues
							long newy2 = newy + k;
							newx = cur.el[j] + factor*newy2;
							r tmp = new r(newx-newy2, newx-newy2, newx+newy2, newx+newy2);
							if (cut(tmp, cur.el[0], cur.el[1], cur.el[2], cur.el[3])) best = Math.min(best, dist(newx, newy2));
						}
					}
				}
				System.out.println(best);
			} else System.out.println(dist(m[0], m[1]));
		}
	}
}
