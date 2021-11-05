/*
ÿһ������0�ĳ�10����1�ĳ�01����ʼ��Ϊһ��1
�ʵ�n���Ժ�00�ж��ٸ�
00���������任֮ǰ01�������йأ�
��Ҫ���γ�01������任֮ǰ1�������йأ��Ҹ�00�������й�
���ԣ���DiΪ��i���Ժ�00��������UiΪ��i���Ժ�1������
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


