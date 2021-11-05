//Prufer sequence
import java.math.BigInteger;
import java.util.Scanner;

public class Main{
	static BigInteger [] FAC = new BigInteger[1001];
   
	static int [] D = new int [1001];
	
	public static void main(String [] args){
        initFac();
        
        int s = 0;
        int cnt = 0;
        boolean flag = false;
        
        Scanner cinScanner = new Scanner(System.in);
        int n = cinScanner.nextInt();
        for(int i=0;i<n;++i){
        	D[i] = cinScanner.nextInt();
        	
        	if ( 0 == D[i] || D[i] >= n ){
        		flag = true;continue;
        	}
        	
        	if ( -1 == D[i] ) continue;
        	
        	s += D[i] - 1;
        	++cnt;
        }      
        cinScanner.close();
        
        if ( 1 == n ){
        	System.out.println(0==D[0]||-1==D[0]?1:0);
        	return;
        }
        
        if ( flag ){
        	System.out.println(0);
        	return;
        }
        
        if ( 2 == n ){
        	System.out.println(1);
        	return;
        }
        
        BigInteger aBigInteger = FAC[n-2]
        		       .multiply(BigInteger.valueOf(n-cnt).pow(n-2-s))
        		       .divide(FAC[n-2-s]);
        for(int i=0;i<n;++i){
        	if ( -1 == D[i] ) continue;
        	aBigInteger = aBigInteger.divide(FAC[D[i]-1]);
        }
        
        System.out.print(aBigInteger);
    }
	
	static void initFac(){
		FAC[0] = FAC[1] = BigInteger.ONE;
		BigInteger aBigInteger = BigInteger.ONE;
		
		for(int i=2;i<=1000;++i){
			aBigInteger = aBigInteger.add(BigInteger.ONE);
			FAC[i] = FAC[i-1].multiply(aBigInteger);
		}
	}
}
