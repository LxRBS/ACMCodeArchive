//0，n平方
//90，偶，n平方除以4
//    奇，n平方除以4加1
//180,偶，n方除以2
//    奇，n方除以2加1
//270，同90
//对称变化也有4种
//竖直轴，偶，n方除以2
//        奇，n方减n再除以2再加上n
//水平轴，同竖直轴
//主对角线，n方减n再除以2再加上n
//辅对角线，同主对角线
//最基本的Polya定理
//671ms，3572k，1726B

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

            //0度旋转
            BigInteger s = c.pow(n*n);
            ans = ans.add(s);

            //90度旋转
            if ( 0 == n % 2 )
                s = c.pow(n*n/4);
            else
                s = c.pow(n*n/4+1);

             ans = ans.add(s);

            //180度
            if ( 0 == n % 2 )
                s = c.pow(n*n/2);
            else
                s = c.pow(n*n/2+1);

             ans = ans.add(s);

             //270度
            if ( 0 == n % 2 )
                s = c.pow(n*n/4);
            else
                s = c.pow(n*n/4+1);

             ans = ans.add(s);

             //竖直轴及水平轴
            if ( 0 == n % 2 )
                s = c.pow(n*n/2);
            else
                s = c.pow(n*(n+1)/2);

             ans = ans.add(s);
             ans = ans.add(s);

             //对角线
            s = c.pow(n*(n+1)/2);
            ans = ans.add(s);
            ans = ans.add(s);

            System.out.println(ans.divide(eight));
        }
    } 
}