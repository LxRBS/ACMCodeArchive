import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public class rgl {
  public static void main(String[] args) {
    final Scanner scanner = new Scanner(System.in);

    final long startTime = scanner.nextLong();
    final long endTime = scanner.nextLong();
    final int nVertices = scanner.nextInt();

    final Graph fullGraph = new Graph(
        nVertices,
        IntStream.range(0, scanner.nextInt())
            .mapToObj(i -> new Edge(
                scanner.nextInt() - 1,
                scanner.nextInt() - 1,
                scanner.nextLong()))
            .collect(Collectors.groupingBy(e -> e.from)));

    final Map<Integer, Long> distanceFromSource = fullGraph.dijkstra(0);
    final Map<Integer, Long> distanceToSink = fullGraph.reverseEdges().dijkstra(nVertices - 1);

    long largestKnownImpossible = distanceToSink.get(0) - startTime - 1;
    long smallestKnownPossible = Math.min(
        Math.max(distanceToSink.get(0), endTime) - startTime,
        distanceToSink.get(0));
    while (largestKnownImpossible + 1 < smallestKnownPossible) {
      final long lag = (largestKnownImpossible + smallestKnownPossible) / 2;

      final BitSet reachableVertices =
          fullGraph.filterEdges(e -> e.weight + distanceToSink.getOrDefault(e.to, lag + 1) <= lag)
              .reachableFrom(IntStream.range(0, nVertices)
                  .filter(x ->
                      distanceFromSource.containsKey(x) && distanceToSink.containsKey(x)
                          && distanceFromSource.get(x) + distanceToSink.get(x) <= startTime + lag)
                  .boxed()
                  .collect(Collectors.toList()));
      final Graph reducedGraph = fullGraph.filterEdges(edge ->
          reachableVertices.get(edge.from)
              && edge.weight + distanceToSink.getOrDefault(edge.to, lag + 1) <= lag);

      try {
        boolean possible = false;
        for (Map.Entry<Integer, Long> pathLength : reducedGraph.dagLongestPaths(nVertices - 1).entrySet()) {
          final int x = pathLength.getKey();
          if (distanceFromSource.get(x) + distanceToSink.get(x) <= startTime + lag && pathLength.getValue() > 0) {
            final long arrivalTime = startTime + lag - distanceToSink.get(x);
            final long travelTime = pathLength.getValue();
            possible |= (arrivalTime + travelTime >= endTime);
          }
        }
        if (possible) {
          smallestKnownPossible = lag;
        } else {
          largestKnownImpossible = lag;
        }
      } catch (CycleException canGoForever) {
        smallestKnownPossible = lag;
      }
    }

    System.out.println(smallestKnownPossible);
  }

  private static class Graph {
    private final int nVertices;
    private final Map<Integer, List<Edge>> edges;

    public Graph(int nVertices, Map<Integer, List<Edge>> edges) {
      this.nVertices = nVertices;
      this.edges = edges;
    }

    public Graph filterEdges(Predicate<Edge> predicate) {
      return new Graph(
          nVertices,
          edges.values().stream().flatMap(List::stream)
              .filter(predicate)
              .collect(Collectors.groupingBy(e -> e.from)));
    }

    public Graph reverseEdges() {
      return new Graph(
          nVertices,
          edges.values().stream().flatMap(List::stream)
              .map(Edge::reversed)
              .collect(Collectors.groupingBy(e -> e.from)));
    }

    public Map<Integer, Long> dijkstra(int source) {
      Map<Integer, Long> distances = new HashMap<>();
      distances.put(source, 0L);

      PriorityQueue<Edge> frontier = new PriorityQueue<>();
      frontier.offer(new Edge(source, source, 0L));

      while (!frontier.isEmpty()) {
        final int x = frontier.peek().to;
        if (distances.get(x) != frontier.poll().weight) {
          continue;
        }
        for (Edge edge : edges.getOrDefault(x, Collections.emptyList())) {
          final long distance = edge.weight + distances.get(x);
          if (distance < distances.getOrDefault(edge.to, distance + 1)) {
            frontier.offer(new Edge(x, edge.to, distance));
            distances.put(edge.to, distance);
          }
        }
      }
      return distances;
    }

    public BitSet reachableFrom(List<Integer> sources) {
      BitSet visited = new BitSet(nVertices);
      Stack<Integer> frontier = new Stack<>();
      for (int source : sources) {
        visited.set(source);
        frontier.push(source);
      }
      while (!frontier.isEmpty()) {
        for (Edge edge : edges.getOrDefault(frontier.pop(), Collections.emptyList())) {
          if (!visited.get(edge.to)) {
            visited.set(edge.to);
            frontier.push(edge.to);
          }
        }
      }
      return visited;
    }

    public Map<Integer, Long> dagLongestPaths(int sink) throws CycleException {
      Map<Integer, Long> pathLengths = new HashMap<>();
      pathLengths.put(sink, 0L);

      final List<Integer> sorted = dagTopologicalSort();
      for (int i = sorted.size() -1 ; i >= 0; i--) {
        for (Edge edge : edges.getOrDefault(sorted.get(i), Collections.emptyList())) {
          if (pathLengths.containsKey(edge.to)) {
            final long length = pathLengths.get(edge.to) + edge.weight;
            if (length > pathLengths.getOrDefault(edge.from, length - 1)) {
              pathLengths.put(edge.from, length);
            }
          }
        }
      }
      return pathLengths;
    }

    public List<Integer> dagTopologicalSort() throws CycleException {
      final int[] deps = new int[nVertices];
      edges.values().stream().flatMap(List::stream).forEach(edge -> deps[edge.to]++);

      List<Integer> sorted = new ArrayList<>();
      for (int i = 0; i < nVertices; i++) {
        if (deps[i] == 0) {
          sorted.add(i);
        }
      }
      for (int i = 0; i < nVertices; i++) {
        if (i == sorted.size()) {
          throw new CycleException("Processed " + i + " vertices out of " + nVertices);
        }
        for (Edge edge : edges.getOrDefault(sorted.get(i), Collections.emptyList())) {
          deps[edge.to]--;
          if (deps[edge.to] == 0) {
            sorted.add(edge.to);
          }
        }
      }
      return sorted;
    }
  }

  private static class Edge implements Comparable<Edge> {
    public final int from;
    public final int to;
    public final long weight;

    public Edge(int from, int to, long weight) {
      this.from = from;
      this.to = to;
      this.weight = weight;
    }

    public Edge reversed() {
      return new Edge(to, from, weight);
    }

    @Override
    public int compareTo(Edge other) {
      return Long.compare(weight, other.weight);
    }
  }

  private static class CycleException extends RuntimeException {
    public CycleException(String message) {
      super(message);
    }
  }
}
