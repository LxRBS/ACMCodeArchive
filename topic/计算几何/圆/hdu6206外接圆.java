/*
 * 给定ABCP4个点，问P是否在ABC外接圆外
 * 首先令A为原点，做一个转化则外接圆的圆心满足方程
 * (x-xB)^2+(y-yB)^2=R^2
 * (x-xC)^2+(y-yC)^2=R^2
 * x^2+y^2=R^2
 * 化为二元一次方程
 * 2xB*x+2yB*y=xB^2+yB^2
 * 2xC*x+2yC*y=xC^2+yC^2
 * 解得
 * x = ( yB(xC^2+yC^2) - yC(xB^2+yB^2) ) / ( 2 * (xCyB-xByC) )
 * y = ( xC(xB^2+yB^2) - xB(xC^2+yC^2) ) / ( 2 * (xCyB-xByC) )
 * 最后判断一下 (xP-x)^2 + (yP-y)^2 > x^2 + y^2，等价于
 * xP^2+yP^2>2(xxP+yyP)，等价于
 * (xP^2+yP^2)*(xCyB-xByC) > xP * ( yB(xC^2+yC^2) - yC(xB^2+yB^2) ) + yP * ( xC(xB^2+yB^2) - xB(xC^2+yC^2) )
 */


import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    
    
	public static void main(String [] args){
		Point A = new Point();
	    Point B = new Point();
	    Point C = new Point();
	    Point P = new Point();
	    
		Scanner cin = new Scanner(System.in);
        int nofkase = cin.nextInt();
        for(int kase=0;kase<nofkase;++kase){
        	A.x = cin.nextBigInteger();
        	A.y = cin.nextBigInteger();
        	B.x = cin.nextBigInteger();
        	B.y = cin.nextBigInteger();
        	C.x = cin.nextBigInteger();
        	C.y = cin.nextBigInteger();
        	P.x = cin.nextBigInteger();
        	P.y = cin.nextBigInteger();
        	
        	B = B.subtract(A);
        	C = C.subtract(A);
        	P = P.subtract(A);
        	
        	BigInteger BR2 = B.dist2();
        	BigInteger CR2 = C.dist2();
        	BigInteger chaji = C.cross(B);
        	
        	BigInteger left = P.dist2().multiply(chaji);
        	BigInteger right = P.x.multiply(B.y.multiply(CR2).subtract(C.y.multiply(BR2)));
        	right = right.add(P.y.multiply(C.x.multiply(BR2).subtract(B.x.multiply(CR2))));
        	System.out.println(left.abs().compareTo(right.abs())>0?"Accepted":"Rejected");
        }
        cin.close();
	}
	
	static class Point{
		BigInteger x,y;
		
		Point subtract(Point p){
		    Point ans = new Point();
		    ans.x = this.x.subtract(p.x);
		    ans.y = this.y.subtract(p.y);
		    return ans;
		}
		
		BigInteger dist2(){
			return x.multiply(x).add(y.multiply(y));
		}
		
		BigInteger cross(Point p){
			return x.multiply(p.y).subtract(y.multiply(p.x));
		}
	}

}


