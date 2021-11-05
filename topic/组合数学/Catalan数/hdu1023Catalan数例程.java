import java.math.BigInteger;
import java.util.Scanner;

public class Main{
	final static BigInteger ONE = BigInteger.ONE;
	final static BigInteger TWO = ONE.add(ONE);
	final static BigInteger FOUR = TWO.add(TWO);
	
	final static int SIZE = 101;
	static BigInteger [] Catalan = new BigInteger [SIZE];
	
	public static void main(String [] args){
        init();
        
        Scanner cin = new Scanner(System.in);
        while(cin.hasNextInt()){
        	int n = cin.nextInt();
        	System.out.println(Catalan[n]);
        }
        
	}
	
	private static void init(){
		Catalan[0] = ONE;
		
		BigInteger n = ONE;
		for(int i=1;i<SIZE;++i){
			BigInteger a = FOUR.multiply(n).subtract(TWO);
			n = n.add(ONE);
			Catalan[i] = Catalan[i-1].multiply(a).divide(n);
		}
	}

}