/*
    n次抛硬币，至少连续k个正面的情况有多少种
*/
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;

public class Main{
	static BigInteger [] PowOf2 = new BigInteger [101];
    static BigInteger [][] Dp = new BigInteger [2][101];
	static int N,K;
    
	public static void main(String [] args){
		initPowOf2();
        Scanner cin = new Scanner(System.in);
        while( cin.hasNext() ){
        	N = cin.nextInt();
        	K = cin.nextInt();
        	
        	Arrays.fill(Dp[0], null);
        	Arrays.fill(Dp[1], null);
        	
        	Dp[1][0] = Dp[0][0] = Dp[1][1] = BigInteger.ONE;
        	Dp[0][1] = 1 == K ? BigInteger.ZERO : BigInteger.ONE;
        	
        	System.out.println(PowOf2[N].subtract(dp(0, N)).subtract(dp(1, N)));
        	
        	//disp();
        }
    	cin.close();
    }

    static BigInteger dp(int color,int n){
    	if ( null != Dp[color][n] ) return Dp[color][n];
    	
    	if ( 1 == color ){//tail
    		Dp[1][n] = dp(0, n-1).add(dp(1, n-1));
    		return Dp[1][n];
    	}
    	
    	//head
    	BigInteger ret = BigInteger.ZERO;
    	for(int i=1;i<=K-1&&n-i>=0;++i){
    		ret = ret.add(dp(1, n-i));
    	}
    	Dp[0][n] = ret;
    	return ret;
    }

    static void initPowOf2(){
    	PowOf2[0] = BigInteger.ONE;
    	BigInteger two = BigInteger.ONE.add(BigInteger.ONE);
    	for(int i=1;i<101;++i){
    		PowOf2[i] = two.multiply(PowOf2[i-1]);
    	}
    }

    static void disp(){
    	for(int i=0;i<=N;++i){
    		System.out.print(" "+Dp[0][i]);
    	}
    	System.out.println();
    	for(int i=0;i<=N;++i){
    		System.out.print(" "+Dp[1][i]);
    	}
    	System.out.println();
    }
}

