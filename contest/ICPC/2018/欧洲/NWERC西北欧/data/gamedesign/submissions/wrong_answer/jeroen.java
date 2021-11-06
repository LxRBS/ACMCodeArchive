import java.util.*;
import java.io.*;

public class jeroen
{

	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String moves = in.readLine();

		// Work backwards
		int x = 0;
		int y = 0;
		int dist = 1000;
		int pdx = 0;
		int pdy = 0;
		int px = 0;
		int py = 0;
		List<String> ans = new ArrayList<String>();
		boolean wasRollback = false;
		for(int i = moves.length() - 1; i >= 0; i--) {
			int dx = 0;
			int dy = 0;
			boolean nowRollback = false;
			switch(moves.charAt(i)) {
			case 'L':
				dx = 1;
				break;
			case 'U':
				dy = -1;
				break;
			case 'R':
				dx = -1;
				break;
			case 'D':
				dy = 1;
				break;
			}

			// Check if this is a roll back
			if(pdx == -dx && pdy == -dy) {
				if(x == 0 || y == 0) {
					System.out.println("impossible");
					return;
				}
				nowRollback = true;
			}

			// Do the move
			px = x;
			py = y;
			if(!wasRollback || !nowRollback)
				ans.add((x-dx) + " " + (y-dy));
			x += dx*dist;
			y += dy*dist;

			// Update
			dist -= 42;
			pdx = dx;
			pdy = dy;
			wasRollback = nowRollback;
		}

		// Outputting
		System.out.println(x + " " + y);
		System.out.println(ans.size());
		for(String line : ans) System.out.println(line);
	}
}
