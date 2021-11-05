import java.util.Scanner;

public class Main{
	final static int MOD = 10000;
	static Matrix MATRIX = new Matrix(2);
	
    public static void main(String [] args){
    	MATRIX.data[0][0] = MATRIX.data[0][1] = MATRIX.data[1][0] = 1;
    	
    	Scanner cin = new Scanner(System.in);
    	while(true){
    		int n = cin.nextInt();
    		if ( -1 == n ) break;
    		if ( 0 == n ){
    			System.out.println(0);
    			continue;
    		}
    		
    		Matrix mat = Matrix.powerMod(MATRIX,n-1,MOD);
    		System.out.println(mat.data[0][0]);
    	}
    	cin.close();
    }
}

class Matrix{
	int row,col;
	int [][] data;
	
	Matrix(int row,int col){
		this.row = row;
		this.col = col;
		data = new int [row][col];
	}
	
	Matrix(int size){this(size, size);}
	
	static Matrix I(int size){
		Matrix ret = new Matrix(size);
		for(int i=0;i<ret.row;++i)ret.data[i][i] = 1;
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
