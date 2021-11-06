import java.util.Hashtable;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Kinky2 {
	
	public static final int MAXSIZE = 10;
	
	public static char[][] grid = new char[MAXSIZE+2][MAXSIZE+2];
	public static Hashtable<String, Integer> htf = new Hashtable<>();	// forward hash table
	public static Hashtable<String, Integer> htb = new Hashtable<>();	// backward hash table
	public static Queue<Node2> q = new LinkedList<>();
	public static Direction2[] dirs = {new Direction2(-1,-1),
									   new Direction2(-1,0),
									   new Direction2(-1,1),
									   new Direction2(0,-1),
									   new Direction2(0,1),
									   new Direction2(1,-1),
									   new Direction2(1,0),
									   new Direction2(1,1),
									  };
	
	public static void main(String [] args)
	{
		int numr, numc, numKinks;
		String s;
		
		Scanner in = new Scanner(System.in);
		numr = in.nextInt();
		numc = in.nextInt();
		for(int i=1; i<=numr; i++)
			grid[i][0] = grid[i][numc+1] = ' ';
		for(int c=1; c<numc; c++)
			grid[0][c] = grid[numr+1][c] = ' ';
		for(int i=1; i<=numr; i++) {
			for(int j=1; j<=numc; j++) {
				String t = in.next();
				grid[i][j] = t.charAt(0);
			}
		}
		numKinks = in.nextInt();
		s = in.next();
		if ((s.length() == 1 && numKinks > 0) || (s.length() > 1 && numKinks >= s.length()-1)) {
			System.out.println("NO");
			System.exit(0);
		}
		
		char c0 = s.charAt(0);
		if (s.length() == 1) {						// special case: length = 1
			for(int r=1; r<=numr; r++) {
				for(int c=1; c<=numc; c++) {
					if (grid[r][c] == c0) {
						System.out.println("YES");
						System.exit(0);
					}
				}
			}
			System.out.println("NO");
			System.exit(0);
		}
		char c1 = s.charAt(1);
		for(int r=1; r<=numr; r++) {
			for(int c=1; c<=numc; c++) {
				for(Direction2 d : dirs) {
					if (grid[r][c] == c0 && grid[r+d.r][c+d.c]== c1)
						q.add(new Node2(1, r+d.r, c+d.c, d, 0));
				}
			}
		}
		if (s.length() == 2) {					// special case: length = 2
			if (!q.isEmpty()) {
				System.out.println("YES");
			}
			else {
				System.out.println("NO");
			}
			System.exit(0);
		}
												// search halfway from start of string
		while(!q.isEmpty()) {
			Node2 node = q.remove();
			if (node.index > s.length()/2)		// first string over 1/2 length - time to end loop
				break;
//System.out.println(node);
			if (htf.containsKey(node.toString()))
				continue;
//if (node.index == s.length()/2) System.out.println("Storing " + node);
			htf.put(node.toString(), 1);

			int nextIndex = node.index+1;
			for(Direction2 d: dirs) {
				if (grid[node.r+d.r][node.c+d.c]==s.charAt(nextIndex) ) {
					int nextNK = node.nk;
					if (d != node.lastDir) {
						nextNK++;
					}
//System.out.println("adding " + nextIndex + "," +  node.r+d.r+","+ node.c+d.c+" "+nextNK);
					q.add(new Node2(nextIndex, node.r+d.r, node.c+d.c, d, nextNK));
				}
			}
		}
										// do backward search
		q.clear();
		c0 = s.charAt(s.length()-1);
		c1 = s.charAt(s.length()-2);
		for(int r=1; r<=numr; r++) {
			for(int c=1; c<=numc; c++) {
				for(Direction2 d : dirs) {
					if (grid[r][c] == c0 && grid[r+d.r][c+d.c]== c1)
						q.add(new Node2(s.length()-2, r+d.r, c+d.c, d, 0));
				}
			}
		}
		while(!q.isEmpty()) {
			Node2 node = q.remove();
			if (node.index < s.length()/2)
				break;
			if (htb.containsKey(node.toString()))
				continue;
			if (node.index == s.length()/2) {		// first string over 1/2 length - look for match
//System.out.println("End of back search " + node);
				for(Direction2 d: dirs) {
					Node2 n = new Node2(node.index, node.r, node.c, d, numKinks-node.nk-1);	// assume forward and backward meet at a kink
					if (d.r == -node.lastDir.r && d.c == -node.lastDir.c)
						n.nk++;
//System.out.println("  Checking " + n);
					if (htf.containsKey(n.toString())) {
						System.out.println("YES");
						System.exit(0);
					}
				}
			}
//System.out.println(node);
			htb.put(node.toString(), 1);
			int nextIndex = node.index-1;
			for(Direction2 d: dirs) {
				if (grid[node.r+d.r][node.c+d.c]==s.charAt(nextIndex) ) {
					int nextNK = node.nk;
					if (d != node.lastDir) {
						nextNK++;
					}
//System.out.println("adding " + nextIndex + "," +  node.r+d.r+","+ node.c+d.c+" "+nextNK);
					q.add(new Node2(nextIndex, node.r+d.r, node.c+d.c, d, nextNK));
				}
			}
		}
		System.out.println("NO");
	}
}

class Direction2 {
	int r, c;
	
	Direction2(int r, int c) {
		this.r = r;
		this.c = c;
	}
}

class Node2 {
	
	public int index, r, c, nk;
	public Direction2 lastDir;
	
	public Node2(int index, int r, int c, Direction2 d, int nk)
	{
		this.index = index;
		this.r = r;
		this.c = c;
		this.lastDir = d;
		this.nk = nk;
	}
	
	public String toString()
	{
		return index+","+r+","+c+","+lastDir.r+","+lastDir.c+","+nk;
	}
}
/**/
