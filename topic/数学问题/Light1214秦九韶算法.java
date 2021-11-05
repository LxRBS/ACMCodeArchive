/*
        给定大整数a和32位整型b
        问a是否整除b

        应该使用秦九韶算法，即：
        a = SIGMA( ci*10^i ) = ( ... ( ( cn*10 + c(n-1) ) * 10 + c(n-2) ) * 10 + ... 
        每一个运算均取模即可
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