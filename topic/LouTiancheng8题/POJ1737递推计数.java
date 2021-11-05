/*
n个顶点（带标号）的连通图一共有多少个
令Fn为所求，
Gn为n个顶点的非连通图总数
Hn为n个顶点的图总数
易知：Hn = 2 ^ (n*(n-1)/2)
现在考虑计算Gn。Gn为非联通图的总数，则图至少被分为了2个部分。我们总是考虑点1所在的那个部分。假设点1所在那个连通部分包含k个顶点，则这个k个顶点的可能性一共有C(n-1,k-1)个，每个连通分量的个数为Fk。再考虑剩余的n-k个顶点，这一部分不要求一定连通，所以形成的图的总数为Gn-k。所以，
Gn = sigma( C(n-1,k-1) * Fk * Hn-k )
最后有：
Fn = Hn - Gn
*/
import java.math.BigInteger;
import java.util.Scanner;


public class Main{
	final static int SIZE = 51;
	static final BigInteger TWO = BigInteger.ONE.add(BigInteger.ONE);
	static BigInteger [] H = new BigInteger [SIZE];
	static BigInteger [] G = new BigInteger [SIZE];
	static BigInteger [] F = new BigInteger [SIZE];
	static BigInteger [][] C = new BigInteger [SIZE][SIZE];
	
	static void init(){
		for(int i=0;i<SIZE;++i)for(int j=0;j<=i;++j){
			if ( 0 == j || i == j ) C[i][j] = BigInteger.ONE;
			else C[i][j] = C[i-1][j-1].add(C[i-1][j]);
		}
		C[0][0] = BigInteger.ONE;
		
		BigInteger p = TWO;
		H[0] = BigInteger.ZERO;
		H[1] = BigInteger.ONE;
		for(int i=2;i<SIZE;++i){
			H[i] = H[i-1].multiply(p);
			p = p.multiply(TWO);
		}
		F[1] = BigInteger.ONE;
		F[0] = G[0] = G[1] = BigInteger.ZERO;
		
		for(int i=2;i<SIZE;++i){
			G[i] = BigInteger.ZERO;
			for(int j=1;j<i;++j){
				G[i] = G[i].add(F[j].multiply(H[i-j]).multiply(C[i-1][j-1]));
			}
			F[i] = H[i].subtract(G[i]);
		}
	}
	
	public static void main(String [] args){
		init();
		for(int i=0;i<SIZE;++i){
			;
		}
        Scanner cin = new Scanner(System.in);
        while(true){
        	int n = cin.nextInt();
        	if ( 0 == n ) break;
        	System.out.println(F[n]);
        }
        cin.close();
	}

}