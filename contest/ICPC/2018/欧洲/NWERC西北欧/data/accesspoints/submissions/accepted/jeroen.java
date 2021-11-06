import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.valueOf(in.readLine());
		int[] s = new int[n];
		int[] t = new int[n];
		for(int i = 0; i < n; i++) {
			String[] ps = in.readLine().split(" ");
			s[i] = Integer.valueOf(ps[0]);
			t[i] = Integer.valueOf(ps[1]);
		}

		//. Solve two dimensions separately
		System.out.println(solve1(s) + solve1(t));
	}

	public static double solve1(int[] xs) {
		// Work from left to right, add new segments every
		// time, but if they need to go to the left of the
		// previous on we merge them.
		Stack<Segment> segs = new Stack<Segment>();
		for(int x : xs) {
			Segment next = new Segment(x);
			while(!segs.isEmpty() && segs.peek().getPlacement() > next.getPlacement()) {
				next.addSegment(segs.pop());
			}
			segs.push(next);
		}

		// Now add all costs
		double ret = 0;
		for(Segment seg : segs) ret += seg.getCosts();
		return ret;
	}
}

class Segment {
	// Represents a segment from i - j, where we can in constant
	// time compute the placement position (mean of the elements)
	// as well as the cost for that.
	// Let p be the placement position of all points in this segment
	// Cost = Sum_i (x[i] - p)^2 = Sum_i x[i]^2 - 2 * p * x[i] + p^2
	//      = Sum_i x[i]^2 - 2 * p * Sum_i x[i] + n * p^2
	public long sum_x;
	public long sum_x2;
	public long len;

	public Segment(int x) {
		sum_x  = x;
		sum_x2 = (long)x * x;
		len    = 1;
	}

	public void addSegment(Segment other) {
		sum_x  += other.sum_x;
		sum_x2 += other.sum_x2;
		len    += other.len;
	}

	public double getPlacement() {
		return (double)sum_x / (double)len;
	}

	public double getCosts() {
		double p = getPlacement();
		return sum_x2 - 2 * p * sum_x + len * p * p;
	}
}
