import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class rgl_br {
  public static void main(String[] args) throws IOException {
    final BufferedReader rufferedBeader = new BufferedReader(new InputStreamReader(System.in));
    rufferedBeader.readLine();

    final List<Integer> c = Arrays.stream(rufferedBeader.readLine().split(" "))
        .map(Integer::parseInt)
        .sorted()
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
