/*
 * Wythoff Game
 * ����ʯ�ӵ���Ϸ����a=(sqrt(5)+1)/2, b = a + 1
 * ��(an,bn)Ϊ�ذܵ�
 * ��
 * an = floor(a^n), bn = floor(b^n)
 * ��
 * ( bn - an ) * a == an
 */
import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.math.BigDecimal;
import java.math.MathContext;
import java.util.Arrays;
import java.util.Scanner;
import java.util.SortedSet;
import java.util.TreeSet;

public class Main {
	static Scanner Input;

	public static void main(String[] args) {
		StringBuilder sb = new StringBuilder("0.");
		for(int i=0;i<103;++i) sb.append("0");
		PreString = sb.append("1").toString();
		EPS = new BigDecimal(PreString);
		SQRT5 = Newton();	
		GOLD = SQRT5.add(BigDecimal.ONE).divide(TWO, MC);
		//System.out.println(SQRT5);
		
		Scanner cin = new Scanner(System.in);
        while( cin.hasNext() ){
        	BigDecimal a = cin.nextBigDecimal();
        	BigDecimal b = cin.nextBigDecimal();
        	if ( a.compareTo(b) > 0 ){BigDecimal t=a;a=b;b=t;}
        	
        	BigDecimal c = b.subtract(a).multiply(GOLD, MC);
        	
        	if ( c.compareTo(a) > 0 && c.subtract(a).compareTo(BigDecimal.ONE) < 0 ) System.out.println("0");
        	else System.out.println("1");
        }
        cin.close();
	}


	//ʹ��ţ�ٷ���sqrt(5)���㵽С�����100λ
	static String PreString;
	static BigDecimal EPS;
	static BigDecimal FIVE = BigDecimal.valueOf(5);
	static BigDecimal TWO = BigDecimal.valueOf(2);
	static MathContext MC = new MathContext(105);
	static BigDecimal SQRT5;
	static BigDecimal GOLD;//�ƽ�ָ���
	static BigDecimal Newton(){
		BigDecimal x = BigDecimal.valueOf(Math.sqrt(5));
		while ( f(x).abs().compareTo(EPS) > 0 ){
			x = x.subtract(f(x).divide(fp(x), MC));
		}
		return x;
	}
	
	//����(x) = x * x - 5
	static BigDecimal f(BigDecimal x){
		return x.multiply(x,MC).subtract(FIVE, MC);
	}
	//���� f'(x) = 2x
	static BigDecimal fp(BigDecimal x){
		return TWO.multiply(x, MC);
	}

}

