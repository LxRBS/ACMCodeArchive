import java.util.Scanner;
import java.util.Locale;

public class tommy {

  public static double totalTime(int n, double p, double s,
      double v, double c) {
    return n * Math.pow(Math.log(n) / Math.log(2.0), c * Math.sqrt(2.0)) / p + s * (1 + 1 / c) / v;
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in).useLocale(Locale.US);
    int n = sc.nextInt();
    double p = sc.nextDouble();
    double s = sc.nextDouble();
    double v = sc.nextDouble();

    p *= 1e9;

    double left = 0.0;
    double right = 1.0;

    // choose starting interval
    while(totalTime(n, p, s, v, right) < totalTime(n, p, s, v, right / 2))
      right *= 2;

    // ternary search
    while(true) {
      if (Math.abs(right - left) < 1e-9)
        break;

      double leftThird = left + (right - left) / 3;
      double rightThird = right - (right - left) / 3;

      if (totalTime(n, p, s, v, leftThird) > totalTime(n, p, s, v, rightThird))
        left = leftThird;
      else
        right = rightThird;
    }

    Locale.setDefault(new Locale("en"));
    System.out.println(String.format("%9f %9f", totalTime(n, p, s, v, (left + right) / 2),
          (left + right) / 2));
  }

}
