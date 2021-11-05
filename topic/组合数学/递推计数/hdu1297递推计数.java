/*
男孩女孩站成一排，不允许有单独的女孩。问方法总数
Di为i个人以女孩结尾的方法总数
Ui为i个人以男孩结尾的方法总数
Fi为方法总数，显然Fi=Di+Ui
Ui = Di-1 + Ui-1    
考虑i个人以女孩结尾的数量，如果i-1是以女孩结尾的，则直接加一个女孩仍然合法。
如果i-1是不合法的，加上一个女孩变为合法，则其结尾必然为： XXXXX...XXX男女，且XX部分本身是合法的
所以：Di = Di-1 + Fi-3
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
		D[1] = BigInteger.ZERO;
		F[1] = U[1] = D[2] = U[2] = BigInteger.ONE;
		F[2] = D[3] = U[3] = BigInteger.valueOf(2L);
		F[3] = BigInteger.valueOf(4L);
		
		for(int i=4;i<SIZE;++i){
			D[i] = D[i-1].add(F[i-3]);
			U[i] = D[i-1].add(U[i-1]);
			F[i] = D[i].add(U[i]);
		}
	} 
	
	static final int SIZE = 1001;
	static BigInteger [] D = new BigInteger [SIZE];
	static BigInteger [] U = new BigInteger [SIZE];
	static BigInteger [] F = new BigInteger [SIZE];
}


