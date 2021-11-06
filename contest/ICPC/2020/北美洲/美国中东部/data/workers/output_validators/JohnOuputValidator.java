import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class JohnOuputValidator {

	public static final int MAX = 100;

	public static int[][] workToGates = new int[MAX][2*MAX];
	public static int[][] gatesToStas = new int[2*MAX][MAX];

	public static boolean[] stationUsed = new boolean[MAX];
	public static boolean[] gateUsed = new boolean[2*MAX];

	public static Scanner input=null, ans=null;
	public static PrintWriter output = null;

	public static void exit(int code, String mesg)
	{
		if (output != null) {
			output.println(mesg);
			output.close();
		}
		System.out.println(mesg);
		System.exit(code);
	}

	public static void main(String [] args)
	{
		try {
			input = new Scanner(new FileInputStream(args[0]));
			ans = new Scanner(new FileInputStream(args[1]));
		}
		catch (FileNotFoundException e) {
			System.exit(-1);
		}
		if (args.length == 3) {
			try {
				output = new PrintWriter(new FileOutputStream(args[2]+"judgemessage.txt"));
			}
			catch (FileNotFoundException e) {
				System.exit(-1);
			}
		}

		int n;
		n = input.nextInt();

		for(int i=0; i<n; i++) {
			for(int j=0; j<2*n; j++)
				workToGates[i][j] = input.nextInt();
		}
		for(int j=0; j<n; j++) {
			for(int i=0; i<2*n; i++)
				gatesToStas[i][j] = input.nextInt();
		}
		int minDist = ans.nextInt();

		Scanner in = new Scanner(System.in);
		int sum = 0, teamMinDist = 0;
		try {
			teamMinDist = in.nextInt();
			if (teamMinDist > minDist) {
				exit(43, "greater min distance");
			}
			in.nextLine();
			for(int i=1; i<=n; i++) {
				String line = in.nextLine();
				StringTokenizer st = new StringTokenizer(line);
				if (st.countTokens() != 3)
					exit(43, st.countTokens() + " for worker line " + i);
				int worker = Integer.parseInt(st.nextToken());
				if (worker != i)
					exit(43, "bad worker number " + i);
				worker--;
				String gate = st.nextToken();
				int gateIndex = 2*Integer.parseInt(gate.substring(0,gate.length()-1)) - 2;
				gate = gate.substring(gate.length()-1);
				if (gate.equals("B"))
					gateIndex++;
				else if (!gate.equals("A"))
					exit(43, "bad corridor letter " + gate);
				if (gateUsed[gateIndex])
					exit(43, "re-used gate " + (gateIndex)/2);
				gateUsed[gateIndex] = true;
				int station = Integer.parseInt(st.nextToken())-1;
				if (station < 0 || station >= n)
					exit(43, "bad station number " + (station+1) + " for worker " + i);
				else if (stationUsed[station])
					exit(43, "used station number " + (station+1) + " for worker " + i);
				stationUsed[station] = true;
				sum += workToGates[worker][gateIndex] + gatesToStas[gateIndex][station];
			}
		}
		catch (Exception e) {
			exit(43, e.toString());
		}
		int i=0;
		while (i < 2*n && gateUsed[i]) {
			if (gateUsed[i+1])
				exit(43, "both corridors used for gate " + (i/2+1));
			i += 2;
		}
		while (i < 2*n && !gateUsed[i]) {
			if (!gateUsed[i+1])
				exit(43, "neither corridors used for gate " + (i/2+1));
			i += 2;
		}
		if (i != 2*n) {
			exit(43, "bad corridor for gate " + (i/2+1));
		}
		if (sum != teamMinDist)
			exit(43, "matching doesn't match min distance");
		if (in.hasNext())
			exit(43, "extraneous output");
		if (teamMinDist < minDist) {		// gulp! - contestant found a better answer
			exit(43, "Contestant found a better answer");
		}
		System.exit(42);
	}
}
