//TLE, so output and then use table method
class Matrix{	
	final static MathContext MATH_CONTEXT = new MathContext(43); 
	
	BigDecimal [][] data;
	int size;
	
	Matrix(int n){
		size = n;
		data = new BigDecimal [size][size];
		
		for(int i=0;i<size;++i)for(int j=0;j<size;++j) data[i][j] = BigDecimal.ZERO;
	}
	
	public BigDecimal det(){
		BigDecimal ret = BigDecimal.ONE;
		int sgn = 0;
		
	    for(int i=0,j,k;i<size;++i){
	        if ( 0 == data[i][i].signum() ){
	            for(j=i+1;j<size;++j){
	                if ( 0 != data[j][i].signum() ) break;
	            }

	            if ( size == j ) return BigDecimal.ZERO;

	            for(k=i;k<size;++k){
	            	BigDecimal t = data[i][k];
	            	data[i][k] = data[j][k];
	            	data[j][k] = t;
	            }

	            ++sgn;
	        }

	        ret = ret.multiply(data[i][i]);
	        for(k=i+1;k<size;++k) data[i][k] = data[i][k].divide(data[i][i],MATH_CONTEXT);

	        for(j=i+1;j<size;++j)for(k=i+1;k<size;++k){
	        	data[j][k] = data[j][k].subtract(data[j][i].multiply(data[i][k]));
	        }
	    }

	    if ( 1 == ( sgn & 1 ) ) ret = ret.negate();
		
		return ret;
	}
	
	public void disp(PrintStream ps){
		for(int i=0;i<size;++i){
			for(int j=0;j<size;++j) ps.print(" "+data[i][j]);
			ps.println();
		}
	}
}
