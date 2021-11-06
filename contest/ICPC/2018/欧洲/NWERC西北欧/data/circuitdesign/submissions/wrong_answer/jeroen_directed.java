import java.util.*;
import java.io.*;

public class jeroen_directed
{
	static int n;
	static List<Integer>[] nb;
	static int[] width;
	static double[] x, y;

	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.valueOf(in.readLine());
		nb = new List[n];
		for(int i = 0; i < n; i++) nb[i] = new ArrayList<Integer>();
		for(int i = 0; i < n - 1; i++) {
			String[] ps = in.readLine().split(" ");
			int a = Integer.valueOf(ps[0]) - 1;
			int b = Integer.valueOf(ps[1]) - 1;
			nb[a].add(b);
		}

		// Pick 0 as root and compute the treewidth of each subtree
		width = new int[n];
		computewidth(0, -1);

		// Now recursively draw the tree, where we evenly divide the space over
		// the remainder of the tree
		x = new double[n];
		y = new double[n];
		draw(0, -1, 0, 0, 1);

		// And output
		for(int i = 0; i < n; i++)
			System.out.println(x[i] + " " + y[i]);
	}

	public static int computewidth(int i, int p) {
		width[i] = 0;
		for(int j : nb[i]) {
			if(j == p) continue;
			width[i] += computewidth(j, i);
		}
		if(width[i] == 0) width[i]++;
		return width[i];
	}

	public static void draw(int i, int p, double ix, double iy, double iw) {
		x[i] = ix;
		y[i] = iy;

		double perleaf = iw / width[i];
		for(int j : nb[i]) {
			if(j == p) continue;
			double ny = iy + Math.sqrt(1 - (x[i] - ix) * (x[i] - ix));
			double nw = perleaf * width[j];
			draw(j, i, ix, ny, nw);
			ix += nw;
		}
	}
}
