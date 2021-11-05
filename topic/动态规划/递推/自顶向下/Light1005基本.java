/*
    给定n×n的棋盘，在其中放置k个车互不攻击，问共有多少种方法
*/
import java.math.BigInteger;
import java.util.Scanner;

public class Main{
	static final int SIZE = 31;
	static int N;
	static int K;
    static BigInteger NONE = BigInteger.valueOf(-1);
	static BigInteger [] B = new BigInteger [SIZE];
	static BigInteger [][] D = new BigInteger [SIZE][SIZE];
	
	public static void main(String [] args){
		B[0] = BigInteger.ZERO;
		for(int i=1;i<SIZE;++i) B[i] = B[i-1].add(BigInteger.ONE);
		
		Scanner cin = new Scanner(System.in);
		int nofkase = cin.nextInt();
		for(int kase=1;kase<=nofkase;++kase){
			N = cin.nextInt();
			K = cin.nextInt();
			
			System.out.print("Case "+kase+": ");
			
			if ( K > N ){
				System.out.println(0);
				continue;
			}
			
			for(int i=0;i<=N;++i){
				for(int j=0;j<=N;++j) D[i][j] = NONE;
			}
			D[1][1] = B[N];

			System.out.println(dp(N,K));
		}
	}
	
	static BigInteger dp(int col,int cnt){
		if ( !NONE.equals(D[col][cnt]) ) return D[col][cnt];
		if ( 0 == cnt ) D[col][cnt] = BigInteger.ONE;
		else if ( col < cnt ) D[col][cnt] = BigInteger.ZERO;
		else D[col][cnt] = dp(col-1, cnt).add(dp(col-1, cnt-1).multiply(BigInteger.valueOf(N-cnt+1)));
		return D[col][cnt];
		
	}
}