import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.lang.StringBuilder;
import java.util.ArrayList; // makes the solution way too slow
import java.util.Vector;

public class tommy {

    public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] parts = in.readLine().split(" ");
		long total_balls = Long.parseLong(parts[0]);
		int switches = Integer.parseInt(parts[1]);

		char state[] = new char[switches+1];
		int left[] = new int[switches+1];
		int right[] = new int[switches+1];
		int indegree[] = new int[switches+1];
		long balls[] = new long[switches+1];
		balls[1] = total_balls;
		for (int i = 1; i <= switches; i++) {
			parts = in.readLine().split(" ");
			state[i] = parts[0].charAt(0);
			left[i] = Integer.parseInt(parts[1]);
			right[i] = Integer.parseInt(parts[2]);
			++indegree[left[i]];
			++indegree[right[i]];
		}
	
	ArrayList<Integer> q = new ArrayList<Integer>();
	for (int i = 1; i < switches; i++) {
	    if (indegree[i] == 0)
		q.add(i);
	}
	while(!q.isEmpty()) {
	    int i = q.remove(0);
	    if (i == 0)
		continue;
		//		System.out.println(i + " " + balls[i]+ " " + state[i]);
	    if (state[i] == 'L') {
			balls[left[i]] += (balls[i]+1)/2;
			balls[right[i]] += balls[i]/2;
			if (balls[i] % 2 == 1)
				state[i] = 'R';
	    } else {
			balls[left[i]] += balls[i]/2;
			balls[right[i]] += (balls[i]+1)/2;
			if (balls[i] % 2 == 1)
				state[i] = 'L';
	    }
		--indegree[left[i]];
	    if (indegree[left[i]] == 0)
			q.add(left[i]);
		--indegree[right[i]];
		if (indegree[right[i]] == 0)
			q.add(right[i]);
	}
	System.out.println(new String(state, 1, switches));
    }
}
