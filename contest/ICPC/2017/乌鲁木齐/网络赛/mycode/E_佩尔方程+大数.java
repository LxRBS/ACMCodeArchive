/*
 * 给定N，要求不小于N的r，使得1+...+r是一个三角平方数
 * 三角平方数  1+...+m = n * n
 * Pell方程的解 x^2 - 2y^2 = 1
 * 最小解 (3 , 2)  
 * m = (x-1)/2, n = y/2 
 */


import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	final static int SIZE = 100;
	final static BigInteger TWO = new BigInteger("2");
	final static BigInteger THREE = new BigInteger("3");
	final static BigInteger FOUR = new BigInteger("4");
	
	static BigInteger [] X = new BigInteger[SIZE];
	static BigInteger [] Y = new BigInteger[SIZE];
	static BigInteger [] M = new BigInteger[SIZE];
    
	public static void main(String [] args){	  
		Pell();
		
		Scanner cin = new Scanner(System.in);
        int nofkase = cin.nextInt();
        for(int kase=1;kase<=nofkase;++kase){
            BigInteger n = cin.nextBigInteger();
            int k = 0;
            while( n.compareTo(M[k]) > 0 ) ++k;
            System.out.println("Case #"+kase+": "+M[k]);
        }
        cin.close();
	}

    static void Pell(){
    	X[0] = THREE;
    	Y[0] = TWO;
    	M[0] = BigInteger.ONE;
    	for(int i=1;i<SIZE;++i){
    		X[i] = X[i-1].multiply(THREE).add(Y[i-1].multiply(FOUR));
    		Y[i] = X[i-1].multiply(TWO).add(Y[i-1].multiply(THREE));
    		M[i] = X[i].subtract(BigInteger.ONE).divide(TWO);
    		//System.out.println(M[i]);
    	}
    }
}


