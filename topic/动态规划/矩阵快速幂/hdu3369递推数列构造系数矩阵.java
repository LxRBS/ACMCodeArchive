import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main{
	static long [][] C = new long [51][51];//Pascal triangle	
	static Matrix [] Matrices = new Matrix[11];
	static long [][] PowOf7 = new long [8][11];
	static final long MOD = 1000000007L;
	
	static final HashMap<String,Integer> SatMap = new HashMap<String, Integer>(){
		private static final long serialVersionUID = 1L;

		{put("Monday", Integer.valueOf(-1));}
		{put("Tuesday", Integer.valueOf(-2));}
		{put("Wednesday", Integer.valueOf(-3));}
		{put("Thursday", Integer.valueOf(-4));}
		{put("Friday", Integer.valueOf(-5));}
		{put("Saturday", Integer.valueOf(-6));}
		{put("Sunday", Integer.valueOf(0));}
	};
	
	static final HashMap<String,Integer> SunMap = new HashMap<String, Integer>(){
		private static final long serialVersionUID = 1L;

		{put("Monday", Integer.valueOf(0));}
		{put("Tuesday", Integer.valueOf(-1));}
		{put("Wednesday", Integer.valueOf(-2));}
		{put("Thursday", Integer.valueOf(-3));}
		{put("Friday", Integer.valueOf(-4));}
		{put("Saturday", Integer.valueOf(-5));}
		{put("Sunday", Integer.valueOf(-6));}
	};	
	
    public static void main(String [] args){
    	for(int i=1;i<=7;++i){
    		PowOf7[i][0] = 1L;
    		for(int j=1;j<=10;++j)PowOf7[i][j] = ( i * PowOf7[i][j-1] ) % MOD;
    	}
    	
    	initC(10);
    	initMatrix(10);
    	    	
    	Scanner cin = new Scanner(System.in);
    	int nofkase = cin.nextInt();
    	for(int kase=1;kase<=nofkase;++kase){
    		String weekday = cin.next();
    		int n = cin.nextInt();
    		int k = cin.nextInt();
    		
    		Matrix r = Matrix.powerMod(Matrices[k], n-1, MOD);
    		
    		long ret = 0L;
    		for(int i=0;i<r.col;++i) ret = ( ret + r.data[k+1][i] ) % MOD;
    		
    		int a = SatMap.get(weekday);
    		if ( n >= 7 + a ){
    		    Matrix satMatrix = initMatrix(k, a);
    		    r = Matrix.powerMod(satMatrix, (n-7-a)/7, MOD);
    		}
    		
    		long t = 0L;
    		for(int i=0;i<r.col-1;++i) t = ( t + r.data[k+1][i] ) % MOD;
    		t = ( t + PowOf7[7+a][k] ) % MOD;
    		
    		ret = ( ret - t ) % MOD;
    		if ( ret < 0 ) ret += MOD;
    		
    		a = SunMap.get(weekday);
    		if ( n >= 7 + a ){
    			Matrix sunMatrix = initMatrix(k, a);
    		    r = Matrix.powerMod(sunMatrix, (n-7-a)/7, MOD);
    		}
    		
    		t = 0L;
    		for(int i=0;i<r.col-1;++i) t = ( t + r.data[k+1][i] ) % MOD;
    		t = ( t + PowOf7[7+a][k] ) % MOD;
    		
    		ret = ( ret - t ) % MOD;
    		if ( ret < 0 ) ret += MOD;
    		
    		System.out.printf("Case %d: ", kase);
    		System.out.println(ret);
    	}
    	cin.close();
    }
    
    static void initC(int n){
    	for(int i=0;i<=n;++i)for(int j=0;j<=i;++j){
    		if ( 0 == j || i == j ) C[i][j] = 1L;
    		else C[i][j] = C[i-1][j-1] + C[i-1][j];
    	}
    	C[0][0] = 1L;
    }
    
    static void initMatrix(int n){        
        for(int x=1;x<=n;++x){
            Matrices[x] = new Matrix(x+2);
            for(int r=0;r<x+1;++r)for(int c=r;c<x+1;++c){
                Matrices[x].data[r][c] = C[x-r][c-r];
            }
            //last row
            for(int c=0;c<x+1;++c)Matrices[x].data[x+1][c] = C[x][c];
            Matrices[x].data[x+1][x+1] = 1L;
        }
    }
    
    static Matrix initMatrix(int k,int a){
    	Matrix ret = new Matrix(k+2);
    	for(int r=0;r<k+1;++r)for(int c=r;c<k+1;++c){
    		ret.data[r][c] = C[k-r][c-r];
    	}
    	
    	long tmp = 1L, a7 = a + 7L;
    	for(int c=0;c<k+1;++c){
    		ret.data[k+1][c] = C[k][c] * PowOf7[7][k-c] % MOD * tmp % MOD;
    		tmp = tmp * a7 % MOD;
    	}
    	ret.data[k+1][k+1] = 1L;
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
