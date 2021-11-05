/*
每一步，将0改成10，将1改成01，初始串为一个1
问第n步以后，00有多少个
00的数量跟变换之前01的数量有关，
而要想形成01，则跟变换之前1的数量有关，且跟00的数量有关
所以，令Di为第i步以后00的数量，Ui为第i不以后1的数量
Di = Di-2 + Ui-2
Ui = 2Ui-1
*/
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) {
		dp();
		
	    Scanner cin = new Scanner(System.in);
	    while( cin.hasNext() ){
	    	int n = cin.nextInt();
	    	System.out.println(D[n]);
	    }
	    
	    cin.close();
	}
	
	static void dp(){
		D[0] = D[1] = BigInteger.ZERO;
		U[0] = U[1] = BigInteger.ONE;
		for(int i=2;i<SIZE;++i) {
			D[i] = D[i-2].add(U[i-2]);
			U[i] = U[i-1].multiply(TWO);
		}
	} 
	
	static final BigInteger TWO = BigInteger.valueOf(2L);
	static final int SIZE = 1001;
	static BigInteger [] D = new BigInteger [SIZE];
	static BigInteger [] U = new BigInteger [SIZE];
}


