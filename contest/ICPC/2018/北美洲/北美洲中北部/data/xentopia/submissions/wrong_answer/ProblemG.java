import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Scanner;

public class ProblemG {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		int targetRed = sc.nextInt();
		int targetBlue = sc.nextInt();
		ArrayList<HashMap<Integer,Integer>> redNeighborLists = new ArrayList<>();
		ArrayList<HashMap<Integer,Integer>> blueNeighborLists = new ArrayList<>();
		ArrayList<HashMap<Integer,Integer>> whiteNeighborLists = new ArrayList<>();
		for(int i = 0 ; i <= n ; i ++) {
			redNeighborLists.add(new HashMap<>());
			blueNeighborLists.add(new HashMap<>());
			whiteNeighborLists.add(new HashMap<>());
		}
		
		for(int i = 0 ; i < m ; i ++) {
			int u = sc.nextInt();
			int v = sc.nextInt();
			int x = sc.nextInt();
			int c = sc.nextInt();
			switch (c) {
			case 0:
				// white
				maybeAddValue(whiteNeighborLists.get(u), v, x);
				maybeAddValue(whiteNeighborLists.get(v), u, x);
				break;
			case 1:
				// red
				maybeAddValue(redNeighborLists.get(u), v, x);
				maybeAddValue(redNeighborLists.get(v), u, x);
				break;
			case 2:
				// blue
				maybeAddValue(blueNeighborLists.get(u), v, x);
				maybeAddValue(blueNeighborLists.get(v), u, x);
				break;
			default:
				break;
			}
		}
		
		int s = sc.nextInt();
		int t = sc.nextInt();
		
		int[][][] grid = new int[n+1][targetRed+1][targetBlue+1];
		for(int i = 0 ; i <= n ; i ++) {
			for(int j = 0 ; j <= targetRed ; j ++) {
				for(int k = 0 ; k <= targetBlue ; k ++) {
					grid[i][j][k] = -1;
				}
			}
		}
		
		PriorityQueue<Element> q = new PriorityQueue<>();
		q.add(new Element(s,0,0,0));
		
		while(!q.isEmpty()) {
			Element current = q.remove();
			
			if(current.numBluePassed > targetBlue || current.numRedPassed > targetRed)
				continue;

			int previousDistance = grid[current.n][current.numRedPassed][current.numBluePassed];
			if(previousDistance != -1)
				continue;
			
			grid[current.n][current.numRedPassed][current.numBluePassed] = current.time;
			
			HashMap<Integer, Integer> whiteNeighbors = whiteNeighborLists.get(current.n);
			for(int neighbor : whiteNeighbors.keySet()) {
				int edgeDistance = whiteNeighbors.get(neighbor);
				q.add(new Element(neighbor,current.numRedPassed,current.numBluePassed,current.time + edgeDistance));
			}
			
			HashMap<Integer, Integer> redNeighbors = redNeighborLists.get(current.n);
			for(int neighbor : redNeighbors.keySet()) {
				int edgeDistance = redNeighbors.get(neighbor);
				q.add(new Element(neighbor,current.numRedPassed+1,current.numBluePassed,current.time + edgeDistance));
			}
			
			HashMap<Integer, Integer> blueNeighbors = blueNeighborLists.get(current.n);
			for(int neighbor : blueNeighbors.keySet()) {
				int edgeDistance = blueNeighbors.get(neighbor);
				q.add(new Element(neighbor,current.numRedPassed,current.numBluePassed+1,current.time + edgeDistance));
			}
		}
		
		System.out.println(grid[t][targetRed][targetBlue]);
		
		
	}
	
	static class Element implements Comparable<Element>{
		int n, numRedPassed, numBluePassed, time;
		
		public Element(int n, int numRedPassed, int numBluePassed, int time) {
			super();
			this.n = n;
			this.numRedPassed = numRedPassed;
			this.numBluePassed = numBluePassed;
			this.time = time;
		}

		@Override
		public int compareTo(Element other) {
			return this.time - other.time;
		}
	}

	// Multiple paths, we only care about the minimum distance path
	private static void maybeAddValue(HashMap<Integer, Integer> neighbors, int destination, int time) {
		Integer oldValue = neighbors.get(destination);
		if(oldValue == null) {
			neighbors.put(destination, time);
		} else {
			if(oldValue > time) {
				neighbors.put(destination, time);
			}
		}
	}

}
