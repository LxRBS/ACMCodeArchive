/*
n�����㣨����ţ�����ͨͼһ���ж��ٸ�
��FnΪ����
GnΪn������ķ���ͨͼ����
HnΪn�������ͼ����
��֪��Hn = 2 ^ (n*(n-1)/2)
���ڿ��Ǽ���Gn��GnΪ����ͨͼ����������ͼ���ٱ���Ϊ��2�����֡��������ǿ��ǵ�1���ڵ��Ǹ����֡������1�����Ǹ���ͨ���ְ���k�����㣬�����k������Ŀ�����һ����C(n-1,k-1)����ÿ����ͨ�����ĸ���ΪFk���ٿ���ʣ���n-k�����㣬��һ���ֲ�Ҫ��һ����ͨ�������γɵ�ͼ������ΪGn-k�����ԣ�
Gn = sigma( C(n-1,k-1) * Fk * Hn-k )
����У�
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