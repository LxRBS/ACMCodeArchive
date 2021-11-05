/*
求圈图的所有可能的匹配数量
令Fn为n节点圈图的所求，Dn为n节点的不连接(1,n)边的匹配数量，Un为连接(1,n)边的匹配数量
则
Dn = Dn-1 + Dn-2
Un = Dn-2
所以
Fn = Dn-1 + 2Dn-2
*/
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) {
		dp();
		
	    Scanner cin = new Scanner(System.in);
	    while(cin.hasNext()){
	    	int n = cin.nextInt();
	    	System.out.println(F[n]);
	    }
	    
	    cin.close();
	}
	
	static void dp(){
		D[1] = D[2] = F[1] = BigInteger.ONE;
		D[3] = BigInteger.valueOf(3L);
		D[4] = BigInteger.valueOf(5L);
		F[2] = BigInteger.valueOf(2L);
		F[3] = BigInteger.valueOf(4L);
		F[4] = BigInteger.valueOf(7L);
		for(int i=5;i<SIZE;++i){
			D[i] = D[i-1].add(D[i-2]);
			F[i] = D[i].add(D[i-2]);
		}
	}
	
	static final int SIZE = 10001;
	static BigInteger [] D = new BigInteger [SIZE];
	static BigInteger [] F = new BigInteger [SIZE];
}


