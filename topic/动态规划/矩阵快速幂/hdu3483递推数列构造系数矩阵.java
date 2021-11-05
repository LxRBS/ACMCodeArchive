import java.util.Scanner;

public class Main{
	static long [][] C = new long [51][51];//Pascal's triangle	
	static Matrix [] Matrices = new Matrix[51];
	
    public static void main(String [] args){
    	initC(50);
    	    	
    	Scanner cin = new Scanner(System.in);
    	while(true){
    		int n = cin.nextInt();
    		int x = cin.nextInt();
    		int m = cin.nextInt();
    		if ( -1 == n && -1 == x && -1 == m ) break;
    		
    		Matrix matrix = initMatrix(x, m);
    		
    		Matrix r = Matrix.powerMod(matrix, n-1, m);
    		
    		long ret = 0L;
    		for(int i=0;i<r.col;++i) ret = ( ret + r.data[x+1][i] ) % m;
    		System.out.println((ret*x)%m);
    	}
    	cin.close();
    }
    
    static void initC(int n){
    	for(int i=0;i<=n;++i)for(int j=0;j<=i;++j){
    		if ( 0 == j || i == j ) C[i][j] = 1;
    		else C[i][j] = C[i-1][j-1] + C[i-1][j];
    	}
    	C[0][0] = 1;
    }
    
    static Matrix initMatrix(int n,int mod){    	
    	Matrix ret = new Matrix(n+2);
    	for(int r=0;r<n+1;++r)for(int c=r;c<n+1;++c){
    		ret.data[r][c] = n * C[n-r][c-r] % mod;
    	}
    	//last row
    	for(int c=0;c<n+1;++c)ret.data[n+1][c] = n * C[n][c] % mod;
    	ret.data[n+1][n+1] = 1L;
    	
    	return ret;
    }
}

class Matrix{
	int row,col;
	long [][] data;
	
	Matrix(int row,int col){
		this.row = row;
		this.col = col;
		data = new long [row][col];
	}
	
	Matrix(int size){this(size, size);}
	
	void disp(){
		for(int i=0;i<this.row;++i){
			for(int j=0;j<this.col;++j) System.out.printf("%15d", this.data[i][j]);
			System.out.println();
		}
	}
	
	static Matrix I(int size){
		Matrix ret = new Matrix(size);
		for(int i=0;i<ret.row;++i)ret.data[i][i] = 1L;
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
	
	static Matrix multiplyMod(Matrix lhs,Matrix rhs,long mod){
		Matrix ret = new Matrix(lhs.row,rhs.col);
		for(int i=0;i<ret.row;++i)for(int j=0;j<ret.col;++j)for(int k=0;k<lhs.col;++k){
			ret.data[i][j] = ( ret.data[i][j] +  lhs.data[i][k] * rhs.data[k][j] % mod ) % mod;
		}
		return ret;	
	}
	
	static Matrix powerMod(Matrix mat,int n,long mod){
		Matrix ret = Matrix.I(mat.row);
		while( n != 0 ){
			if ( (n & 1) == 1 ) ret = multiplyMod(ret, mat, mod);
			mat = multiplyMod(mat, mat, mod);
			n >>= 1;
		}
		return ret;
	}
}
