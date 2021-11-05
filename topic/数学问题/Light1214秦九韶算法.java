/*
        ����������a��32λ����b
        ��a�Ƿ�����b

        Ӧ��ʹ���ؾ����㷨������
        a = SIGMA( ci*10^i ) = ( ... ( ( cn*10 + c(n-1) ) * 10 + c(n-2) ) * 10 + ... 
        ÿһ�������ȡģ����
*/
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) {
	    Scanner cin = new Scanner(System.in);
	    int nofkase = cin.nextInt();
	    for(int kase=1;kase<=nofkase;++kase){
	    	BigInteger a = cin.nextBigInteger().abs();
	    	BigInteger b = cin.nextBigInteger().abs();	    	
	    	BigInteger c = a.mod(b);
	    	System.out.printf("Case %d: ",kase);
	    	System.out.println(c.equals(BigInteger.ZERO)?"divisible":"not divisible");
	    }
	    cin.close(); 
	}

}