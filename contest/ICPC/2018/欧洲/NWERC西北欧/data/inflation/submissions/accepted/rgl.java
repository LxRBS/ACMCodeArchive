import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class rgl {
  public static void main(String[] args) {
    final Scanner scanner = new Scanner(System.in);

    final List<Integer> c = IntStream.range(0, scanner.nextInt())
        .map(x -> scanner.nextInt())
        .sorted()
        .boxed()
        .collect(Collectors.toList());

    final List<Integer> v = IntStream.rangeClosed(1, c.size())
        .boxed()
        .collect(Collectors.toList());

    if (v.stream().anyMatch(x -> x < c.get(x-1))) {
      System.out.println("impossible");
    } else {
      System.out.printf("%.9f\n", v.stream().mapToDouble(x -> c.get(x-1) / (double) x).min().getAsDouble());
    }
  }
}
