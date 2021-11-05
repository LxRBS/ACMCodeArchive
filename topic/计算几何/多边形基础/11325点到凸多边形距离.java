import java.io.*;
import java.util.*;
import java.math.*;

//点
class Point{
	public long x = 0;
	public long y = 0;
	public Point(){}
	//叉积
	public long cross(Point A,Point B){
		long x1 = A.x - x;
		long y1 = A.y - y;
		long x2 = B.x - x;
		long y2 = B.y - y;
		return x1 * y2 - x2 * y1;
	}
	//点积
	public long dot(Point A,Point B){
		long x1 = A.x - x;
		long y1 = A.y - y;
		long x2 = B.x - x;
		long y2 = B.y - y;
		return x1 * x2 + y1 * y2;
	}
	//与点p的距离
	public double dist(Point p){
		double tx = (double)(x - p.x);
		double ty = (double)(y - p.y);
		return Math.sqrt(tx*tx+ty*ty);
	}
	//与线段AB的距离
	public double dist(Point A,Point B){
		long d = A.dot(this, B);
		if ( d < 0L ) return this.dist(A);
		
		d = B.dot(this,A);
		if ( d < 0L ) return this.dist(B);
		
		d = cross(A,B);
		if ( d < 0L ) d = -d;
		double t = (double)d;
		return t / A.dist(B);
	}
}
//多边形
class Polygon{
	public final static int SIZE = 102;
	public Point [] vertex = null;
	public int size = 0;
	public Polygon(){
		vertex = new Point [SIZE];
		for(int i=0;i<SIZE;++i)vertex[i] = new Point ();
	}
	
	//判断多边形是否覆盖点p
	public boolean isCover(Point p){
	    vertex[size].x = vertex[0].x;
	    vertex[size].y = vertex[0].y;
	    int k = 0;
	    long t = 0;
	    while( k < size && 0L == (t = p.cross(vertex[k], vertex[k+1])) ) ++k;
		for(int i=k+1;i<size;++i){
			long tt = p.cross(vertex[i],vertex[i+1]);
			if ( 0L == tt ) continue;
			if ( t * tt < 0L ) return false;
		}
		return true;
	}
	//计算多边形与点p的距离
	public double dist(Point p){
		if ( isCover(p) ) return 0.0;
		double ans = p.dist(vertex[size-1],vertex[0]);
		for(int i=0;i<size-1;++i){
			double t = p.dist(vertex[i],vertex[i+1]);
			if ( t < ans ) ans = t;
		}
		return ans;
	}
}
public class Main {
	public static Point p = new Point ();
	public static Polygon poly = new Polygon ();
	public static void main(String[] args) {
		Scanner cin = new Scanner (System.in);
		while(true){
			int n = cin.nextInt();
			if ( 0 == n ) return;
			poly.size = n;
			p.x = cin.nextLong();
			p.y = cin.nextLong();
			for(int i=0;i<n;++i){
                poly.vertex[i].x = cin.nextLong();
                poly.vertex[i].y = cin.nextLong();
			}
			System.out.printf("%.2f\n",poly.dist(p));
		}
	}
}

