/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

import java.util.*;
import java.io.*;

public class jeroen
{
	public static Point[] inner, outer;

	public static void main(String[] args) throws IOException
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n1 = Integer.parseInt(in.readLine());
		inner = new Point[n1];
		for(int i = 0; i < n1; i++) {
			String[] p = in.readLine().split(" ");
			inner[i] = new Point(Integer.parseInt(p[0]), Integer.parseInt(p[1]));
		}
		int n2 = Integer.parseInt(in.readLine());
		outer = new Point[n2];
		for(int i = 0; i < n2; i++) {
			String[] p = in.readLine().split(" ");
			outer[i] = new Point(Integer.parseInt(p[0]), Integer.parseInt(p[1]));
		}

		// Multiply all points by 2 so that we only have even coordinates
		// such that we can construct the exact midpoint of every line.
		for(int i = 0; i < n1; i++) {
			inner[i].X *= 2;
			inner[i].Y *= 2;
		}
		for(int i = 0; i < n2; i++) {
			outer[i].X *= 2;
			outer[i].Y *= 2;
		}

		// Find some point that is definitely in the shortest path
		int startI = 0;
		for(int i = 1; i < n1; i++)
			if(inner[i].X < inner[startI].X || (inner[i].X == inner[startI].X && inner[i].Y < inner[startI].Y))
				startI = i;
			
		// Find some point on outer track to draw a start-finish such that
		// this point is not on the shortest path
		int startO = -1;
		for(int i = 0; i < n2; i++) {
			if(!InTrack(inner[startI], outer[i])) continue;
			if(startO == -1 || outer[i].X < outer[startO].X || (outer[i].X == outer[startO].X && outer[i].Y < outer[startO].Y))
				startO = i;
		}

		// Renumber points such start/finish line is at index 0
		Point[] inner2 = new Point[n1];
		for(int i = 0; i < n1; i++)
			inner2[i] = inner[(i+startI)%n1];
		inner = inner2;
		Point[] outer2 = new Point[n2];
		for(int i = 0; i < n2; i++)
			outer2[i] = outer[(i+startO)%n2];
		outer = outer2;

		// Now find line at the other side of track to use as an index
		// to decide at which side of the start/finish we are
		startI = 1;
		for(int i = 2; i < n1; i++)
			if(inner[i].X > inner[startI].X || (inner[i].X == inner[startI].X && inner[i].Y > inner[startI].Y))
				startI = i;
		startO = -1;
		for(int i = 0; i < n2; i++) {
			if(!InTrack(inner[startI], outer[i])) continue;
			if(startO == -1 || outer[i].X > outer[startO].X || (outer[i].X == outer[startO].X && outer[i].Y > outer[startO].Y))
				startO = i;
		}

		// Initialize graph between pair of points
		int n = n1+n2+2;
		int ao = n1+1; // 0..n1 = inner, ao..ao+n2 = outer
		boolean[][] conn = new boolean[n][n];

		// We can drive along the edges
		for(int i = 0; i < n1; i++)
			conn[i][i+1] = true;
		for(int i = 0; i < n2; i++)
			conn[ao+i][ao+i+1] = true;

		// Connect start to inner points
		for(int i = 2; i <= startI; i++)
			if(InTrack(inner[0], inner[i]))
				conn[0][i] = true;

		// Connect start to outer points
		for(int i = 1; i < startO; i++)
			if(InTrack(inner[0], outer[i]))
				conn[0][ao+i] = true;

		// Connect finish to inner points
		for(int i = startI+1; i < n1; i++)
			if(InTrack(inner[0], inner[i]))
				conn[i][n1] = true;

		// Connect finish to outer points
		for(int i = startO+1; i < n2; i++)
			if(InTrack(inner[0], outer[i]))
				conn[ao+i][n1] = true;

		// Connect outer and inner lines O(n^3)
		for(int i = 1; i < n1; i++) {
			for(int j = 1; j < n2; j++) {
				if(!InTrack(inner[i], outer[j])) continue;
				if(Intersect(inner[i], outer[j], inner[0], outer[0])) continue;
				conn[i][ao+j] = conn[ao+j][i] = true;
			}
		}

		// Connect inner and inner lines O(n^3)
		for(int i = 1; i < n1; i++) {
			for(int j = 1; j < n1; j++) {
				if(!InTrack(inner[i], inner[j])) continue;
				if(Intersect(inner[i], inner[j], inner[0], outer[0])) continue;
				conn[i][j] = conn[j][i] = true;
			}
		}

		// Connect outer and outer lines O(n^3)
		for(int i = 1; i < n2; i++) {
			for(int j = 1; j < n2; j++) {
				if(!InTrack(outer[i], outer[j])) continue;
				if(Intersect(outer[i], outer[j], inner[0], outer[0])) continue;
				conn[ao+i][ao+j] = conn[ao+j][ao+i] = true;
			}
		}

		// All points as they are numbered now
		Point[] allPoints = new Point[n];
		for(int i = 0; i <= n1; i++)
			allPoints[i] = inner[i%n1];
		for(int i = 0; i <= n2; i++)
			allPoints[ao+i] = outer[i%n2];

		// Dijkstra to compute shortest path
		PriorityQueue<State> Q = new PriorityQueue<State>();
		Q.add(new State(0, -1, 0));
		boolean[] done = new boolean[n];
		int[] from = new int[n];
		while(!Q.isEmpty()) {
			State top = Q.poll();
			if(done[top.i]) continue;
			done[top.i] = true;
			from[top.i] = top.from;
			if(top.i == n1) {
				System.out.println(top.dist / 2);
				break;
			}

			for(int i = 0; i < n; i++)
				if(conn[top.i][i])
					Q.add(new State(i, top.i, top.dist + Distance(allPoints[top.i], allPoints[i])));
		}

		// Dump data for visualisation
		if(args.length > 0 && args[0].equals("-dump")) {
			System.err.println("1");
			System.err.println();

			// Inner polygon
			System.err.println(n1);
			for(int i = 0; i < n1; i++)
				System.err.println(inner[i]);

			// Outer polygon
			System.err.println(n2);
			for(int i = 0; i < n2; i++)
				System.err.println(outer[i]);
			
			// Construct solution path
			List<Point> solution = new ArrayList<Point>();
			int cur = n1;
			while(cur != -1) {
				solution.add(allPoints[cur]);
				cur = from[cur];
			}

			// Print solution path
			System.err.println(solution.size());
			for(int i = 0; i < solution.size(); i++)
				System.err.println(solution.get(i));
		}
	}

	private static class State implements Comparable<State> {
		public int i, from;
		public double dist;

		public State(int i, int from, double dist) {
			this.i = i;
			this.from = from;
			this.dist = dist;
		}

		public int compareTo(State other) {
			if(dist < other.dist) return -1;
			if(dist > other.dist) return 1;
			return 0;
		}
	}

	/* Check if line A -> B is fully inside the track (only works for even coordinates!) O(n) */
	public static boolean InTrack(Point A, Point B)
	{
		Point halfWay = new Point((A.X + B.X) / 2, (A.Y + B.Y) / 2);
		return PointInPolygon(halfWay, outer) && !PointInPolygon(halfWay, inner) && !TrackIntersect(A, B);
	}

	/* Check if A -> B intersects with track boundaries O(n) */
	public static boolean TrackIntersect(Point A, Point B)
	{
		return PolygonIntersect(inner, A, B) || PolygonIntersect(outer, A, B);
	}
	public static boolean PolygonIntersect(Point[] poly, Point A, Point B)
	{
		for(int i = 0; i < poly.length; i++) 
			if(A != poly[i] && A != poly[(i+1)%poly.length]
			   && B != poly[i] && B != poly[(i+1)%poly.length]
			   && Intersect(poly[i], poly[(i+1)%poly.length], A, B))
				return true;
		return false;
	}

	// Prewritten
	public static class Point
	{
		public int X, Y;

		public Point(int x, int y)
		{
			X = x; Y = y;
		}

		public String toString() {
			return X + " " + Y;
		}
	}
	
	public static Point minus(Point A, Point B)
	{
		return new Point(A.X - B.X, A.Y - B.Y);
	}

	public static int dot(Point A, Point B)
	{
		return A.X * B.X + A.Y * B.Y;
	}

	public static int cross(Point A, Point B)
	{
		return A.X * B.Y - A.Y * B.X;
	}

	public static double Distance(Point A, Point B)
	{
		return Math.sqrt(dot(minus(A,B),minus(A,B)));
	}

	/* Returns whether point C is on segment AB */
	public static boolean OnSegment(Point A, Point B, Point C) {
		return cross(minus(B,A),minus(C,A)) == 0
			&& dot(minus(C,B),minus(B,A)) <= 0
			&& dot(minus(C,A),minus(A,B)) <= 0;
	}
	
	/* Returns whether segments AB and CD intersect */
	public static boolean Intersect(Point A, Point B, Point C, Point D)
	{
		int num1 = cross(minus(D,C), minus(A,C));
		int num2 = cross(minus(B,A), minus(A,C));
		int denom = cross(minus(B,A), minus(D,C));
		if(denom < 0) {
			num1 *= -1;
			num2 *= -1;
			denom *= -1;
		}
		if(denom == 0) // parallel lines
			return OnSegment(A,B,C) || OnSegment(A,B,D) || OnSegment(C,D,A) || OnSegment(C,D,B);
		return 0 <= num1 && num1 <= denom && 0 <= num2 && num2 <= denom;
	}

	/* Calculates if a point is within the polygon */
	public static boolean PointInPolygon(Point P, Point[] polygon)
	{
		int j = polygon.length - 1, c = 0;
		for (int i = 0; i < polygon.length; j = i++) {
			if ((polygon[j].Y <= P.Y) && (P.Y < polygon[i].Y) &&
				cross(minus(polygon[j],P),minus(polygon[i],P)) > 0) ++c;
			if ((polygon[i].Y <= P.Y) && (P.Y < polygon[j].Y) &&
				cross(minus(polygon[j],P),minus(polygon[i],P)) < 0) --c;
		}
		return c != 0;
	}
}
