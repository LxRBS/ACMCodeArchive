//Solution by lukasP (Lukáš Poláček)
import java.util.Scanner;
import java.util.Locale;

public class lukas_power {

    public static double ff(int n, double p, double s,
			    double v, double c) {
	return n * Math.pow(Math.log(n) / Math.log(2.0), c * Math.sqrt(2.0)) / p + s / (c * v);
    }

    public static void main(String[] args) {
	Scanner sc = new Scanner(System.in).useLocale(Locale.US);
	int n = sc.nextInt();
	double p = sc.nextDouble();
	double s = sc.nextDouble();
	double v = sc.nextDouble();

	p *= 1e9;

	double res = ff(n, p, s, v, 3), val = 3;
	for (double q = 1.22; q <= 38.16; q *= (1 + 9e-7))
	    {
		double tmp = ff(n, p, s, v, q);
		if (tmp < res)
		    {
			res = tmp;
			val = q;
		    }
	    }

	Locale.setDefault(new Locale("en"));
	System.out.println(String.format("%9f %9f", res + s / v, val));
    }

}
