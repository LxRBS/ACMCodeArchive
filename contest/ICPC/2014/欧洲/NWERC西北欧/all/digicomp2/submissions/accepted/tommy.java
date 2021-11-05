import java.util.Scanner;
import java.lang.StringBuilder;
import java.util.Queue;
import java.util.LinkedList;
import java.util.Vector;

public class tommy {

    public static void main(String[] args) {
	Scanner sc = new Scanner(System.in);
	long total_balls = sc.nextLong();
	int switches = sc.nextInt();

	StringBuilder state = new StringBuilder(switches + 1);
	for (int i = 0; i < switches + 1; i++) {
	    state.append('0');
	}
	Vector<Integer> left = new Vector<Integer>(switches + 1);
	Vector<Integer> right = new Vector<Integer>(switches + 1);
	Vector<Integer> indegree = new Vector<Integer>(switches + 1);
	for (int i = 0; i < switches + 1; i++) {
	    left.addElement(0);
	    right.addElement(0);
	    indegree.addElement(0);
	}
	Vector<Long> balls = new Vector<Long>(switches + 1);
	for (int i = 0; i < switches + 1; i++) {
	    balls.addElement(0L);
	}

	balls.setElementAt(total_balls, 1);
	for (int i = 1; i <= switches; i++) {
	    state.setCharAt(i, sc.next().charAt(0));
	    left.setElementAt(sc.nextInt(), i);
	    right.setElementAt(sc.nextInt(), i);
	    indegree.setElementAt(indegree.elementAt(left.elementAt(i)) + 1, left.elementAt(i));
	    indegree.setElementAt(indegree.elementAt(right.elementAt(i)) + 1, right.elementAt(i));
	}
	
	Queue<Integer> q = new LinkedList<Integer>();
	for (int i = 1; i < switches; i++) {
	    if (indegree.elementAt(i) == 0)
		q.add(i);
	}
	while(!q.isEmpty()) {
	    int i = q.remove();
	    if (i == 0)
		continue;
	    
	    if (state.charAt(i) == 'L') {
		balls.setElementAt(balls.elementAt(left.elementAt(i)) +
				   (balls.elementAt(i) + 1) / 2,
				   left.elementAt(i));
		balls.setElementAt(balls.elementAt(right.elementAt(i)) +
				   balls.elementAt(i) / 2,
				   right.elementAt(i));
		if (balls.elementAt(i) % 2 == 1)
		    state.setCharAt(i, 'R');
	    } else {
		balls.setElementAt(balls.elementAt(left.elementAt(i)) +
				   balls.elementAt(i) / 2,
				   left.elementAt(i));
		balls.setElementAt(balls.elementAt(right.elementAt(i)) +
				   (balls.elementAt(i) + 1 ) / 2,
				   right.elementAt(i));
		if (balls.elementAt(i) % 2 == 1)
		    state.setCharAt(i, 'L');
	    }

	    indegree.setElementAt(indegree.elementAt(left.elementAt(i)) - 1,
				  left.elementAt(i));
	    if (indegree.elementAt(left.elementAt(i)) == 0)
		q.add(left.elementAt(i));
	    indegree.setElementAt(indegree.elementAt(right.elementAt(i)) - 1,
				  right.elementAt(i));
	    if (indegree.elementAt(right.elementAt(i)) == 0)
		q.add(right.elementAt(i));
	}
	System.out.println(state.substring(1));
    }
}
