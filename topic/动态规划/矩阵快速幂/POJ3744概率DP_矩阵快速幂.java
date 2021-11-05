import java.util.Arrays;
import java.util.Scanner;

public class Main {
	static Matrix matrix = new Matrix(2);
	static int N;
	static double P;
	static int [] A = new int [12];

	public static void main(String[] args) {
		A[0] = 0;
		Scanner cin = new Scanner(System.in);
        while( cin.hasNext() ){
        	N = cin.nextInt();
        	P = cin.nextDouble();
        	for(int i=1;i<=N;++i) A[i] = cin.nextInt();
        	Arrays.sort(A, 1, N+1);
        	
        	double ret = 1.0;
        	for(int i=1;i<=N;++i){
        		if ( A[i] == A[i-1] + 1 ) {
        			ret = 0.0;break;
        		}
        		double t = calc(1+A[i-1],A[i]-1);
        		ret *= t * ( 1 - P);        		
        	}
        	System.out.printf("%.7f\n", ret);
        }
        cin.close();
	}
	
	//计算从s到e的概率,[s,e]为安全段
	static double calc(int s,int e){
		matrix.data[0][0] = P;
		matrix.data[0][1] = 1.0 - P;
		matrix.data[1][0] = 1.0;
		matrix.data[1][1] = 0.0;
		
		Matrix m = Matrix.power(matrix, e-s);
		return m.data[0][0];
	}

}

class Matrix{
	int row,col;
	double [][] data;
	
	Matrix(int row,int col){
		this.row = row;
		this.col = col;
		data = new double [row][col];
	}
	
	Matrix(int size){this(size, size);}
	
	static Matrix I(int size){
		Matrix ret = new Matrix(size);
		for(int i=0;i<ret.row;++i)ret.data[i][i] = 1.0;
		return ret;
	}
	
	static Matrix add(Matrix lhs,Matrix rhs){
		Matrix ret = new Matrix(lhs.row,lhs.col);
		for(int i=0;i<ret.row;++i)for(int j=0;j<ret.col;++j){
			ret.data[i][j] = lhs.data[i][j] + rhs.data[i][j];
		}
		return ret;	
	}
	
	static Matrix multiply(Matrix lhs,Matrix rhs){
		Matrix ret = new Matrix(lhs.row,rhs.col);
		for(int i=0;i<ret.row;++i)for(int j=0;j<ret.col;++j)for(int k=0;k<lhs.col;++k){
			ret.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
		}
		return ret;			
	}
	
	static Matrix power(Matrix mat,int n){
		Matrix ret = Matrix.I(mat.row);
		while( n != 0 ){
			if ( (n & 1) == 1 ) ret = multiply(ret, mat);
			mat = multiply(mat, mat);
			n >>= 1;
		}
		return ret;
	}
	
	static Matrix multiplyMod(Matrix lhs,Matrix rhs,int mod){
		Matrix ret = new Matrix(lhs.row,rhs.col);
		for(int i=0;i<ret.row;++i)for(int j=0;j<ret.col;++j)for(int k=0;k<lhs.col;++k){
			ret.data[i][j] = ( ret.data[i][j] +  lhs.data[i][k] * rhs.data[k][j] % mod ) % mod;
		}
		return ret;	
	}
	
	static Matrix powerMod(Matrix mat,int n,int mod){
		Matrix ret = Matrix.I(mat.row);
		while( n != 0 ){
			if ( (n & 1) == 1 ) ret = multiplyMod(ret, mat, mod);
			mat = multiplyMod(mat, mat, mod);
			n >>= 1;
		}
		return ret;
	}
}

