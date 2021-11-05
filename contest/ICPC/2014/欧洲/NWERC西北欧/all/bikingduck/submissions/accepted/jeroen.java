/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

import java.util.*;
import java.io.*;
import java.text.*;

public class jeroen {
	static int x1, y1, x2, y2, vwalk, vbike;

	public static void main(String[] args) throws IOException {
		// Read input, could be done nicer
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] parts = in.readLine().split(" ");
		vwalk = Integer.parseInt(parts[0]);
		vbike = Integer.parseInt(parts[1]);
		parts = in.readLine().split(" ");
		x1 = Integer.parseInt(parts[0]);
		y1 = Integer.parseInt(parts[1]);
		x2 = Integer.parseInt(parts[2]);
		y2 = Integer.parseInt(parts[3]);
		parts = in.readLine().split(" ");
		int xstart = Integer.parseInt(parts[0]);
		int ystart = Integer.parseInt(parts[1]);
		parts = in.readLine().split(" ");
		final int xdest = Integer.parseInt(parts[0]);
		final int ydest = Integer.parseInt(parts[1]);
		int n = Integer.parseInt(in.readLine());
		int[] xstation = new int[n];
		int[] ystation = new int[n];
		for(int i = 0; i < n; i++) {
			parts = in.readLine().split(" ");
			xstation[i] = Integer.parseInt(parts[0]);
			ystation[i] = Integer.parseInt(parts[1]);
		}

		// Walk directly
		double ans = dist(xstart, ystart, xdest, ydest, true);

		// Go through two existing bike stations
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				double cur = dist(xstart, ystart, xstation[i], ystation[i], true)
					+ dist(xdest, ydest, xstation[j], ystation[j], true)
					+ dist(xstation[i], ystation[i], xstation[j], ystation[j], false);
				ans = Math.min(ans, cur);
			}
		}

		// Go through one visible bike station
		for(int i = 0; i < n; i++) {
			// Walk from start to the bike station
			final int xs = xstation[i];
			final int ys = ystation[i];
			double cur = dist(xstart, ystart, xstation[i], ystation[i], true)
				+ gobike(xdest, ydest, new Cont() {
						public double call(double d, double xm, double ym) {
							return d + dist(xs, ys, xm, ym, false);
						}
					});
			ans = Math.min(ans, cur);

			// Walk from end to the bike station
			final int xs2 = xstation[i];
			final int ys2 = ystation[i];
			double cur2 = dist(xdest, ydest, xstation[i], ystation[i], true)
				+ gobike(xstart, ystart, new Cont() {
						public double call(double d, double xm, double ym) {
							return d + dist(xs2, ys2, xm, ym, false);
						}
					});
			ans = Math.min(ans, cur2);
		}

		// Go though two non-visible bike stations
		double nonext = gobike(xstart, ystart, new Cont() {
				public double call(final double d1, final double xm, final double ym) {
					return gobike(xdest, ydest, new Cont() {
							public double call(final double d2, double xm2, double ym2) {
								return d1 + d2 + dist(xm, ym, xm2, ym2, false);
							}
						});
				}
			});
		ans = Math.min(ans, nonext);

		// Print answer
		System.out.println(ans);
	}

	// Ternary search for best bike station on border
	public static double gobike(double xs, double ys, Cont cont) {
		double ans = Double.MAX_VALUE;
		
		// Possible useful bike station ranges
		double[][] poss = {
			{x1, y1, x1, y2}, // left border
			{x2, y1, x2, y2}, // right border
			{x1, y1, x2, y1}, // top border
			{x1, y2, x2, y2}, // bottom border
		};
		for(int i = 0; i < poss.length; i++) {
			double xlow = Math.min(poss[i][0], poss[i][2]);
			double ylow = Math.min(poss[i][1], poss[i][3]);
			double xhigh = Math.max(poss[i][0], poss[i][2]);
			double yhigh = Math.max(poss[i][1], poss[i][3]);
			
			// Ternary search on best location in this range
			double low = 0;
			double high = 1;
			for(int j = 0; j < 100; j++) {
				double a1 = (low + low + high) / 3;
				double a2 = (low + high + high) / 3;
				double x1 = xlow+a1*(xhigh-xlow);
				double y1 = ylow+a1*(yhigh-ylow);
				double r1 = cont.call(dist(xs,ys,x1,y1,true),x1,y1);
				double x2 = xlow+a2*(xhigh-xlow);
				double y2 = ylow+a2*(yhigh-ylow);
				double r2 = cont.call(dist(xs,ys,x2,y2,true),x2,y2);
				if(r1 < r2) {
					high = a2;
					ans = Math.min(ans, r1);
				} else {
					low = a1;
					ans = Math.min(ans, r2);
				}
			}
		}

		return ans;
	}

	public static interface Cont {
		double call(double d, double xm, double ym);
	}
	
	public static double dist(double x1, double y1, double x2, double y2,
							  boolean walk) {
		double dx = x1 - x2;
		double dy = y1 - y2;
		return Math.sqrt(dx*dx + dy*dy) / (walk ? vwalk : vbike);
	}
}
