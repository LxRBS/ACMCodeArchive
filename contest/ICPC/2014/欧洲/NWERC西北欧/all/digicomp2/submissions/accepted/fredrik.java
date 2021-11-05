import java.io.*;
import java.util.*;

class Switch {
	boolean startLeft;
	long balls = 0;
	int left = -1;
	int right = -1;
	int inputcount = 0;
}

public class fredrik {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		long ballsin = sc.nextLong();
		int switchcount = sc.nextInt();
		Switch[] switches = new Switch[switchcount+1]; // Zero initialized
		for (int i = 0; i <= switchcount; ++i)
			switches[i] = new Switch();
		for (int i = 1; i <= switchcount; ++i)
		{
			Switch s = switches[i];
			s.startLeft = sc.next().equals("L");
			s.left = sc.nextInt();
			s.right = sc.nextInt();
			switches[s.left].inputcount++;
			switches[s.right].inputcount++;
		}
		switches[1].balls = ballsin;

		Queue<Integer> q = new ArrayDeque<Integer>();
		for (int i = 0; i <= switchcount; ++i)
		{
			if (switches[i].inputcount == 0)
				q.add(i);
		}
		for (int cur = q.poll(); cur != 0; cur = q.poll())
		{
			Switch scur = switches[cur];
			Switch sleft = switches[scur.left];
			Switch sright = switches[scur.right];
			if (scur.startLeft)
			{
				sleft.balls += (scur.balls + 1) / 2;
				sright.balls += scur.balls / 2;
			}
			else
			{
				sleft.balls += scur.balls / 2;
				sright.balls += (scur.balls + 1) / 2;
			}
			if (--sleft.inputcount == 0)
				q.add(scur.left);
			if (--sright.inputcount == 0)
				q.add(scur.right);
		}

		for (int i = 1; i <= switchcount; ++i)
			System.out.print(((switches[i].balls & 1) == 0) ^ switches[i].startLeft ? 'R' : 'L');
		System.out.println();
	}
}
