
import java.util.Scanner;

public class E {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int n;
	n = in.nextInt();
	
	System.out.println(euler(n));
    }
    
    static double euler(int n) {
	double val = 0;
	
	long fact = 1;

	if(17 <= n+1)
	    n = 17;
	
	for(int i=0; i<n+1; i++) {
	    if(i != 0)
		fact *= i;
	    val += 1.0/fact;
	}
	
	return val;
    }
}
