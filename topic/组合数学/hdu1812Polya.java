//0��nƽ��
//90��ż��nƽ������4
//    �棬nƽ������4��1
//180,ż��n������2
//    �棬n������2��1
//270��ͬ90
//�ԳƱ仯Ҳ��4��
//��ֱ�ᣬż��n������2
//        �棬n����n�ٳ���2�ټ���n
//ˮƽ�ᣬͬ��ֱ��
//���Խ��ߣ�n����n�ٳ���2�ټ���n
//���Խ��ߣ�ͬ���Խ���
//�������Polya����
//671ms��3572k��1726B

import java.io.*;
import java.util.*;
import java.math.*;

public class Main{
    public static void main(String [] args){
        Scanner cin = new Scanner(System.in);

         BigInteger eight = new BigInteger("8");
         while( cin.hasNextInt() ){
            int n = cin.nextInt();
            BigInteger c = cin.nextBigInteger();

            BigInteger ans = BigInteger.ZERO;

            //0����ת
            BigInteger s = c.pow(n*n);
            ans = ans.add(s);

            //90����ת
            if ( 0 == n % 2 )
                s = c.pow(n*n/4);
            else
                s = c.pow(n*n/4+1);

             ans = ans.add(s);

            //180��
            if ( 0 == n % 2 )
                s = c.pow(n*n/2);
            else
                s = c.pow(n*n/2+1);

             ans = ans.add(s);

             //270��
            if ( 0 == n % 2 )
                s = c.pow(n*n/4);
            else
                s = c.pow(n*n/4+1);

             ans = ans.add(s);

             //��ֱ�ἰˮƽ��
            if ( 0 == n % 2 )
                s = c.pow(n*n/2);
            else
                s = c.pow(n*(n+1)/2);

             ans = ans.add(s);
             ans = ans.add(s);

             //�Խ���
            s = c.pow(n*(n+1)/2);
            ans = ans.add(s);
            ans = ans.add(s);

            System.out.println(ans.divide(eight));
        }
    } 
}