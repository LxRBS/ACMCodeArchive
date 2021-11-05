/*
全1序列，有多少种合并的方法
111有3种方法，分别是：111/21/12
*/
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) {
		dp();
		
	    Scanner cin = new Scanner(System.in);
	    int n = cin.nextInt();
	    for(int i=0;i<n;++i){
	    	String s = cin.next();
	    	System.out.println(F[s.length()]);
	    }
	    
	    cin.close();
	}
	
	static void dp(){
		F[0] = F[1] = BigInteger.ONE;
		for(int i=2;i<SIZE;++i) F[i] = F[i-1].add(F[i-2]);
	} 
	
	static final int SIZE = 201;
	static BigInteger [] F = new BigInteger [SIZE];
}


