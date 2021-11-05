/*
    给定n、k，将n分解成n=pq
    p、q均为质数，q<=p，且|q-kp|<=1E5
    将p=n/q代入到不等式，得
    q^2-1E5q-kn<=0以及q^2+1E5q-kn>=0
    联立解出
    -5E4+sqrt(25E8+kn)<=q<=5E4+sqrt(25E8+kn)
    也就是说q大约在10万以内
 */

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	static BigInteger E25_8 = new BigInteger("2500000000");
	static BigInteger E5_4 = new BigInteger("50000");
	static BigInteger TWO = BigInteger.ONE.add(BigInteger.ONE);
	static int Certainty = 3;
	
	//*
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		BigInteger [] t;
		
		while(cin.hasNext()){
			BigInteger n = cin.nextBigInteger();
			BigInteger k = cin.nextBigInteger();
			BigInteger a = f(E25_8.add(k.multiply(n)));
			BigInteger start = a.subtract(E5_4);
			if ( start.compareTo(BigInteger.ZERO) <= 0 ) start = BigInteger.ONE;
			BigInteger end = a.add(E5_4).add(BigInteger.ONE);
			if ( end.compareTo(n) >= 0 ) end = n.subtract(BigInteger.ONE);
			
			for(BigInteger i=end;i.compareTo(start)>=0;i=i.subtract(BigInteger.ONE)){
				t = n.divideAndRemainder(i);
				if ( BigInteger.ZERO.equals(t[1]) ){
					output(i,t[0]);
					break;
				}
			}
		}
		cin.close();
	}
	//*/
	static void output(BigInteger a,BigInteger b){
		if ( a.compareTo(b) > 0 ){
			BigInteger t = a;
			a = b;
			b = t;
		}
		System.out.println(a+" * "+b);
	}
	
	//返回x，满足x^2<=n<(x+1)^2
	static BigInteger f(BigInteger n){
		BigInteger left = BigInteger.ONE, right = n, mid;
		do{
			mid = left.add(right).divide(TWO);
			if ( mid.multiply(mid).compareTo(n) <= 0 ) left = mid.add(BigInteger.ONE);
			else right = mid.subtract(BigInteger.ONE);
		}while( left.compareTo(right) <= 0 );
		return right;
	}

}


