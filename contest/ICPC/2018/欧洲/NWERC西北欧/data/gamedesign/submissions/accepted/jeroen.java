import java.util.*;
import java.io.*;

public class jeroen
{
	static String dirs = "LURD";
	static int[] dx = { -1, 0, 1, 0 };
	static int[] dy = { 0, 1, 0, -1 };

	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String moves = in.readLine();

		// Simulate the moves and increase distance slowly
		int x = 0;
		int y = 0;
		int dist = 2;
		List<Point> ps = new ArrayList<Point>();
		for(int i = 0; i < moves.length(); i++) {
			int d = dirs.indexOf(moves.charAt(i));
			int j;
			for(j = 0; j < dist; j++) {
				if(ps.contains(new Point(x+dx[d],y+dy[d])))
					break;
				x += dx[d];
				y += dy[d];
			}
			if(j == 0) {
				System.out.println("impossible");
				return;
			}
			if(j == dist) {
				ps.add(new Point(x+dx[d],y+dy[d]));
			}
			dist *= 2;
		}

		// Simulate again to check that we've not passed the final hole
		// such beautiful copy & pasta !
		int fx = x;
		int fy = y;
		x = 0;
		y = 0;
		dist = 2;
		ps.clear();
		for(int i = 0; i < moves.length(); i++) {
			int d = dirs.indexOf(moves.charAt(i));
			int j;
			for(j = 0; j < dist; j++) {
				if(ps.contains(new Point(x+dx[d],y+dy[d])))
					break;
				if(x == fx && y == fy) {
					System.out.println("impossible");
					return;
				}
				x += dx[d];
				y += dy[d];
			}
			if(j == dist) {
				ps.add(new Point(x+dx[d],y+dy[d]));
			}
			dist *= 2;
		}

		// Now move the thing so that our end is exactly at 0,0
		System.out.println((-x) + " " + (-y));
		System.out.println(ps.size());
		for(Point p : ps)
			System.out.println((p.x-x) + " " + (p.y-y));
	}
}

class Point {
	public int x, y;
	public Point(int x, int y) {
		this.x = x;
		this.y = y;
	}
	public boolean equals(Object other) {
		Point p = (Point)other;
		return x == p.x && y == p.y;
	}
}
