/*
�к�Ů��վ��һ�ţ��������е�����Ů�����ʷ�������
DiΪi������Ů����β�ķ�������
UiΪi�������к���β�ķ�������
FiΪ������������ȻFi=Di+Ui
Ui = Di-1 + Ui-1    
����i������Ů����β�����������i-1����Ů����β�ģ���ֱ�Ӽ�һ��Ů����Ȼ�Ϸ���
���i-1�ǲ��Ϸ��ģ�����һ��Ů����Ϊ�Ϸ��������β��ȻΪ�� XXXXX...XXX��Ů����XX���ֱ����ǺϷ���
���ԣ�Di = Di-1 + Fi-3
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


