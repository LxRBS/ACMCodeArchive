import java.util.*;

public class interactive_petr {

static final double beta = 3.0 / 4;

public static void main(String[] args) {
  Scanner scanner = new Scanner(System.in);
  int n = scanner.nextInt();
  int m = scanner.nextInt();
  int[] scores = new int[n];
  double[] pw = new double[m + 1];
  pw[0] = 1;
  for (int i = 1; i < pw.length; ++i) pw[i] = beta * pw[i - 1];
  Random random = new Random(57);
  for (int step = 0; step < m; ++step) {
    int mn = scores[0];
    for (int x : scores) mn = Math.min(mn, x);
    double w = 0;
    for (int x : scores) w += pw[x - mn];
    w *= random.nextDouble();
    int bi = -1;
    for (int i = 0; i < n; ++i) {
      w -= pw[scores[i] - mn];
      if (w < 0) {
        bi = i;
        break;
      }
    }
    String s = scanner.next();
    System.out.println(s.charAt(bi));
    System.out.flush();
    int a = scanner.nextInt();
    for (int i = 0; i < n; ++i) if (s.charAt(i) != '0' + a) ++scores[i];
  }
}

}