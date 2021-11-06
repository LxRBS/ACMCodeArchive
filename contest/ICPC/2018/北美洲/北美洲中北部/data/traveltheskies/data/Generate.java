import java.util.*;
import java.lang.*;

public class Generate {

    /* Flow implementation: https://github.com/cipherboy/general-algorithms/blob/master/graph/ford-fulkerson/Flow.java */
    public static HashMap<Integer, HashMap<Integer, EdgeData>> graph;

    static class Edge {
        public int from;
        public int to;

        public Edge(int from, int to) {
            this.from = from;
            this.to = to;
        }

        public String toString() {
            return from + "->" + to;
        }
    }

	static class EdgeData {
		public int from;
		public int to;
		public int capacity;
		public int flow;

        public EdgeData(int from, int to, int capacity) {
            this.from = from;
            this.to = to;
            this.capacity = capacity;
            this.flow = 0;
        }

        public EdgeData(int capacity) {
            this.capacity = capacity;
            this.flow = 0;
        }

		public int remainder() {
			return capacity - flow;
		}

		public void update(int v) {
			this.flow += v;
		}
	}

	static int flow(int source, int end) {
		int flow_value = 0;
		HashMap<Integer, Integer> parents = new HashMap<Integer, Integer>();

		while (bfs(source, end, parents)) {
			Integer current = end;

			int min_cap = Integer.MAX_VALUE;
			while (parents.get(current) != null) {
				Integer prev = parents.get(current);
				int capacity = graph.get(prev).get(current).remainder();
				min_cap = Math.min(capacity, min_cap);
				current = prev;
			}

			current = end;
			while (parents.get(current) != null) {
				Integer prev = parents.get(current);
				graph.get(prev).get(current).update(min_cap);
				current = prev;
			}

			flow_value += min_cap;
		        parents = new HashMap<Integer, Integer>();
		}

		return flow_value;
	}

	static boolean bfs(int start, int end, HashMap<Integer, Integer> parents) {
		LinkedList<Integer> queue = new LinkedList<Integer>();

                queue.add(start);
		parents.put(start, null);

		while (!queue.isEmpty()) {
			Integer u = queue.remove(0);
			for (Integer v : graph.get(u).keySet()) {
				if (graph.get(u).get(v).remainder() == 0) {
					continue;
				}

				if (v == end) {
					parents.put(v, u);
					// Found a start-end path.
					return true;
				}

				if (!parents.containsKey(v)) {
					parents.put(v, u);
					queue.add(v);
				}
			}
		}

		// Found no start-end paths.
		return false;
	}

	public static HashSet<Integer> bfs2(int start) {
		LinkedList<Integer> queue = new LinkedList<Integer>();
        HashSet<Integer> result = new HashSet<Integer>();
		queue.add(start);

		while (!queue.isEmpty()) {
			Integer u = queue.remove(0);
            result.add(u);
			for (Integer v : graph.get(u).keySet()) {
				if (graph.get(u).get(v).remainder() == 0) {
					continue;
				}

				if (!result.contains(v)) {
					queue.add(v);
				}
			}
		}

		// Found no start-end paths.
		return result;
	}


    public static HashSet<Edge> mincut(int start, int end) {
        HashSet<Edge> min_cut = new HashSet<Edge>();
        HashSet<Integer> cs = bfs2(start);
        if (cs.contains(end)) {
            return null;
        }

        for (Integer v : cs) {
            for (Integer u : graph.get(v).keySet()) {
                if (!cs.contains(u)) {
                    min_cut.add(new Edge(v, u));
                }
            }
        }

        return min_cut;
    }

    public static boolean testFlow() {
        graph = new HashMap<Integer, HashMap<Integer, EdgeData>>();
        graph.put(1, new HashMap<Integer, EdgeData>());
        graph.put(2, new HashMap<Integer, EdgeData>());
        graph.put(3, new HashMap<Integer, EdgeData>());
        graph.put(4, new HashMap<Integer, EdgeData>());
        graph.put(5, new HashMap<Integer, EdgeData>());
        graph.put(6, new HashMap<Integer, EdgeData>());
        graph.get(1).put(2, new EdgeData(1, 2, 8));
        graph.get(1).put(3, new EdgeData(1, 3, 10));
        graph.get(2).put(4, new EdgeData(2, 4, 2));
        graph.get(2).put(5, new EdgeData(2, 5, 3));
        graph.get(3).put(5, new EdgeData(3, 5, 4));
        graph.get(4).put(6, new EdgeData(4, 6, 5));
        graph.get(5).put(6, new EdgeData(5, 6, 7));
        System.out.flush();
        System.err.flush();
        int flow_value = flow(1, 6);
        if (flow_value != 9) {
            return false;
        }
        return true;
    }

    public static int RandInt(Random rand, int min, int max) {
        // Inclusive rand
        return rand.nextInt(max - min + 1) + min;
    }

    public static void main(String[] args) {
        if (!testFlow()) {
            System.out.println("FAILURE");
            return;
        }

        Random rand = new Random(System.currentTimeMillis());
        int TC = 1;
        int max_airports = 10;
        int max_days = 6;
        int difficulty_range = 12000000;
        int min_difficulty = 3000000;
        //System.out.println(TC);

        for (int tc = 1; tc <= TC; tc++) {
            int airports = RandInt(rand, 8, max_airports);
            int days = RandInt(rand, 5, max_days);
            int max_edges = airports*(airports-1)*days;
            int edges = RandInt(rand, 1+(max_edges/2), max_edges);

            System.out.println(airports + " " + days + " " + edges);

            int[] flight_from = new int[edges];
            int[] flight_to = new int[edges];
            int[] flight_day = new int[edges];
            int[] flight_capacity = new int[edges];

            for (int i = 0; i < edges; i++) {
                boolean found = true;
                int miss_count = 0;

                // Generate in random order...
                while (found) {
                    flight_from[i] = RandInt(rand, 1, airports);
                    flight_to[i] = flight_from[i];
                    while (flight_to[i] == flight_from[i]) {
                        flight_to[i] = RandInt(rand, 1, airports);
                    }
                    flight_day[i] = RandInt(rand, 1, days);

                    found = false;
                    for (int j = 0; j < i; j++) {
                        if (flight_from[i] == flight_from[j] &&
                                flight_to[i] == flight_to[j] &&
                                flight_day[i] == flight_day[j]) {
                            found = true;
                            miss_count += 1;
                            assert(miss_count < 1000);
                            break;
                        }
                    }
                }

                flight_capacity[i] = RandInt(rand, 80000, 100000) * 10;
                System.out.println(flight_from[i] + " " + flight_to[i] + " " + flight_day[i] + " " + flight_capacity[i]);
            }

            int[] events_airport = new int[airports*days];
            int[] events_day = new int[airports*days];
            int[] events_people = new int[airports*days];
            for (int airport = 1; airport <= airports; airport++) {
                for (int day = 1; day <= days; day++) {
                    int i = (airport-1)*days + (day-1);
                    events_airport[i] = airport;
                    events_day[i] = day;
                    events_people[i] = RandInt(rand, min_difficulty, difficulty_range);
                    System.out.println(events_airport[i] + " " + events_day[i] + " " + events_people[i]);
                }
            }

            // Generate airport mapping vertices
            // vertex=0 is source vertex
            // vertex=1 is sink vertex
            // So start at #2
            int vertex_number = 2;
            HashMap<String, Integer> airport_map = new HashMap<String, Integer>();
            HashMap<Integer, String> r_airport_map = new HashMap<Integer, String>();
            for (int airport = 1; airport <= airports; airport++) {
                // Need one additional day to make sure all flights have landed...
                for (int day = 1; day <= days; day++) {
                    String name = "a:" + airport + "|d:" + day;
                    airport_map.put(name, vertex_number);
                    r_airport_map.put(vertex_number, name);
                    vertex_number += 1;
                }
            }

            // Each flight gets a pair of vertices, and any flight that arrives
            // at the same airport on a later day can be connected to the sink.
            HashMap<String, Integer> flight_map = new HashMap<String, Integer>();
            HashMap<Integer, String> r_flight_map = new HashMap<Integer, String>();
            for (int i = 0; i < edges; i++) {
                String name = "f:" + flight_from[i] + "|t:" + flight_to[i] + "|d:" + flight_day[i];

                flight_map.put(name + "|source", vertex_number);
                r_flight_map.put(vertex_number, name + "|source");
                vertex_number += 1;

                flight_map.put(name + "|sink", vertex_number);
                r_flight_map.put(vertex_number, name + "|sink");
                vertex_number += 1;
            }

            // Initialize graph
            graph = new HashMap<Integer, HashMap<Integer, EdgeData>>();
            for (int i = 0; i < vertex_number; i++) {
                graph.put(i, new HashMap<Integer, EdgeData>());
            }

            // For all flights, connect between each other with capacity.
            for (int i = 0; i < edges; i++) {
                int u_a = flight_from[i];
                int v_a = flight_to[i];
                int d = flight_day[i];
                int c = flight_capacity[i];

                String name = "f:" + u_a + "|t:" + v_a + "|d:" + d;

                // Convert airport, day -> veretx number
                int u = flight_map.get(name + "|source");
                int v = flight_map.get(name + "|sink");
                graph.get(u).put(v, new EdgeData(u, v, c));
            }

            // For all flights, connect to the sink.
            for (int i = 0; i < edges; i++) {
                int u_a = flight_from[i];
                int v_a = flight_to[i];
                int d = flight_day[i];
                int c = flight_capacity[i];

                String name = "f:" + u_a + "|t:" + v_a + "|d:" + d;

                // Convert airport, day -> veretx number
                int u = flight_map.get(name + "|sink");
                int v = 1;
                graph.get(u).put(v, new EdgeData(u, v, c));
            }

            // For all pairs of flights, connect i.sink -> j.source
            // when i arrives at an airport on a day prior to j.source
            for (int i = 0; i < edges; i++) {
                int i_u_a = flight_from[i];
                int i_v_a = flight_to[i];
                int i_d = flight_day[i];
                int c = Integer.MAX_VALUE;

                String i_name = "f:" + i_u_a + "|t:" + i_v_a + "|d:" + i_d;
                for (int j = 0; i != j && j < edges; j++) {
                    int j_u_a = flight_from[j];
                    int j_v_a = flight_to[j];
                    int j_d = flight_day[j];

                    String j_name = "f:" + j_u_a + "|t:" + j_v_a + "|d:" + j_d;
                    if (i_d < j_d) {
                        int u = flight_map.get(i_name + "|sink");
                        int v = flight_map.get(j_name + "|source");
                        graph.get(u).put(v, new EdgeData(u, v, c));
                    }
                }
            }

            // Connect start to all airports via arrival events
            for (int i = 0; i < airports*days; i++) {
                int v_a = events_airport[i];
                int d = events_day[i];
                int c = events_people[i];

                int u = 0;
                int v = airport_map.get("a:" + v_a + "|d:" + d);
                graph.get(u).put(v, new EdgeData(u, v, c));
//                System.err.println("##DEBUG## event: " + i + " u:" + u + " v:" + v + " v_a:" + v_a + " d:" + d);
            }

            // Connect all airports which have inbound flights to the sources
            for (int i = 0; i < edges; i++) {
                int u_a = flight_from[i];
                int v_a = flight_to[i];
                int d = flight_day[i];
                int c = Integer.MAX_VALUE;

                String name = "f:" + u_a + "|t:" + v_a + "|d:" + d;

                // Convert airport, day -> veretx number
                int u = airport_map.get("a:" + u_a + "|d:" + d);
                int v = flight_map.get(name + "|source");
                graph.get(u).put(v, new EdgeData(u, v, c));
            }

            // Connect all airports to themselves at the next day
            for (int airport = 1; airport <= airports; airport++) {
                for (int day = 1; day < days; day++) {
                    int u = airport_map.get("a:" + airport + "|d:" + day);
                    int v = airport_map.get("a:" + airport + "|d:" + (day+1));
                    int c = Integer.MAX_VALUE;
                    graph.get(u).put(v, new EdgeData(u, v, c));
                }
            }

            int flow = flow(0, 1);

            boolean at_capacity = true;

            // Check if above capacity on all flights:
            for (int i = 0; i < edges; i++) {
                int u_a = flight_from[i];
                int v_a = flight_to[i];
                int d = flight_day[i];
                int c = flight_capacity[i];

                String name = "f:" + u_a + "|t:" + v_a + "|d:" + d;

                // Convert airport, day -> veretx number
                int u = flight_map.get(name + "|source");
                int v = flight_map.get(name + "|sink");
                EdgeData flight = graph.get(u).get(v);
                if (flight.flow < flight.capacity) {
                    at_capacity = false;
                }
            }

            if (at_capacity) {
                System.err.println("optimal");
            } else {
                System.err.println("suboptimal");
            }

//            System.err.println("#DEBUG# graph");
            for (int u = 0; u <= vertex_number; u++) {
                for (int v = 0; v <= vertex_number; v++) {
                    if (u == v || graph.get(u) == null || graph.get(v) == null) {
                        continue;
                    }

                    EdgeData uv = graph.get(u).get(v);
                    if (uv == null) { continue ; }
                    String nu = "source";
                    if (u == 1) {
                        nu = "sink";
                    } else if (u > 1 && r_airport_map.get(u) != null) {
                        nu = r_airport_map.get(u);
                    } else if (u > 1 && r_flight_map.get(u) != null) {
                        nu = r_flight_map.get(u);
                    }

                    String nv = "source";
                    if (v == 1) {
                        nv = "sink";
                    } else if (v > 1 && r_airport_map.get(v) != null) {
                        nv = r_airport_map.get(v);
                    } else if (v > 1 && r_flight_map.get(v) != null) {
                        nv = r_flight_map.get(v);
                    }
//                    System.err.println("#DEBUG# graph u:" + u + " v:" + v + " nu:" + nu + " nv:" + nv + " cap:" + uv.capacity + " flow:" + uv.flow);
                }
            }


            System.out.flush();
            System.err.flush();

        }
    }
}
