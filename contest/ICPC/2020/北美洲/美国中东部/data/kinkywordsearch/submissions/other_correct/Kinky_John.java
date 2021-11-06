import java.util.Hashtable;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Kinky_John {
	
	public static final int MAXSIZE = 10;
	
	public static char[][] grid = new char[MAXSIZE+2][MAXSIZE+2];
	public static Hashtable<String, Integer> ht = new Hashtable<>();
	public static Queue<Node> q = new LinkedList<>();
	public static Direction[] dirs = {new Direction(-1,-1),
									  new Direction(-1,0),
									  new Direction(-1,1),
									  new Direction(0,-1),
									  new Direction(0,1),
									  new Direction(1,-1),
									  new Direction(1,0),
									  new Direction(1,1),
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
				for(Direction d : dirs) {
					if (grid[r][c] == c0 && grid[r+d.r][c+d.c]== c1)
						q.add(new Node(1, r+d.r, c+d.c, d, 0));
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
		
		while(!q.isEmpty()) {
			Node node = q.remove();
//System.out.println(node);
			if (ht.containsKey(node.toString())) {
				continue;
			}
			ht.put(node.toString(), 1);
			int nextIndex = node.index+1;
			for(Direction d: dirs) {
				if (grid[node.r+d.r][node.c+d.c]==s.charAt(nextIndex) ) {
					int nextNK = node.nk;
					if (d != node.lastDir) {
						nextNK++;
					}
					if (nextIndex == s.length()-1) {
//System.out.println("end");
						if (nextNK == numKinks) {
							System.out.println("YES");
							System.exit(0);
						}
					}
					else if (nextNK <= numKinks) {
//System.out.println("adding " + nextIndex + "," +  node.r+d.r+","+ node.c+d.c+" "+nextNK);
						q.add(new Node(nextIndex, node.r+d.r, node.c+d.c, d, nextNK));
					}
				}
			}
		}
		System.out.println("NO");
	}
}

class Direction {
	int r, c;
	
	Direction(int r, int c) {
		this.r = r;
		this.c = c;
	}
}

class Node {
	
	public int index, r, c, nk;
	public Direction lastDir;
	
	public Node(int index, int r, int c, Direction d, int nk)
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
