
// and other testcases will follow

import java.io.*;
import java.util.*;
import java.math.*;

public class GenCases{
	static Random rand = new Random(817234891245L);

	public static void main(String[] args){
		int N = 5000;
		Scanner scan = new Scanner(System.in);
		String name = scan.next();
		if(name.equals("random")){
			completeRandomCase(scan);
		} else if(name.equals("concentrate")){
			concentrated(scan);
		} else if(name.equals("mixed")){
			mixed(scan);
		}
		System.exit(0);
	}


	static void mixed(int N, int P, int P_SMALL, int R, double prob, long seed){
		rand = new Random(seed);
		System.out.println(N + " " + P + " " + R);
		int diff = rand.nextInt(P);
		for(int i = 0; i < N; i++){
			int p;
			if(rand.nextDouble() <= prob){
				p = rand.nextInt(P);
			} else if(P_SMALL > 0) {
				p = (diff + rand.nextInt(P_SMALL)) % P;
			} else {
				p = ((i==0)?((diff - P_SMALL) % P):((diff + rand.nextInt(-P_SMALL)) % P));
			}
			if(i != 0)System.out.print(" ");
			System.out.print(p);
		}
		System.out.println();
	}

	static void mixed(Scanner scan){
		System.err.println("Input: N P P_SMALL R randomPortion SEED");
		int N = scan.nextInt();
		int P = scan.nextInt();
		int P_SMALL = scan.nextInt();
		int R = scan.nextInt();
		double prob = scan.nextDouble();
		long seed = scan.nextLong();
		mixed(N, P, P_SMALL, R, prob, seed);
	}

	static void concentrated(Scanner scan){
		System.err.println("Input: N P P_SMALL R SEED");
		int N = scan.nextInt();
		int P = scan.nextInt();
		int P_SMALL = scan.nextInt();
		int R = scan.nextInt();
		long seed = scan.nextLong();
		mixed(N, P, P_SMALL, R, -0.1, seed);
	}

	static void completeRandomCase(Scanner scan){
		System.err.println("Input: N SEED");
		int N = scan.nextInt();
		long seed = scan.nextLong();
		rand = new Random(seed);
		int P = rand.nextInt( 9999999) + 1;
		int R = rand.nextInt( 9999999) + 1;
		mixed(N, P, 0, R, 1.1, rand.nextLong());
	}
}
