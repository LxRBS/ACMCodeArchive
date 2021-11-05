import java.math.*;
import java.util.*;
import java.lang.String;


public class Main {
	static BigInteger FAC[];
	static int A[];
	static void init(){
		A = new int [26];
		FAC = new BigInteger [13];
		FAC[0] = BigInteger.ONE;
		BigInteger x = BigInteger.ONE;
		for(int i=1;i<13;++i){
			FAC[i] = FAC[i-1].multiply(x);
			x = x.add(BigInteger.ONE);
		}
	}
	
	static BigInteger fac(int n){
		if ( n < 13 ) return FAC[n];
		
		BigInteger ret = FAC[12];
		BigInteger x = new BigInteger("13");
		for(int i=13;i<=n;++i){
			ret = ret.multiply(x);
			x = x.add(BigInteger.ONE);
		}
		return ret;
	}
	
    public static void main(String [] arg){
    	init();
    	
    	Scanner cin = new Scanner(System.in);
		
    	while( true ){
    		int n = cin.nextInt();
    		
    		if ( 0 == n ) return;
    		
    		int sum = 0;
    		for(int i=0;i<n;++i){
    			A[i] = cin.nextInt();
    			sum += A[i];
    		}
    		
    	    BigInteger ret = fac(sum);	
    	    for(int i=0;i<n;++i) ret = ret.divide(FAC[A[i]]);
    	    
    	    System.out.println(ret);
    	}
    }
}
