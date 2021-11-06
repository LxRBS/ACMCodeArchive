import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.FileNotFoundException;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class heroes_of_coin_flip_av {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        CoinFlipTournament solver = new CoinFlipTournament();
        solver.solve(1, in, out);
        out.close();
    }

    static class CoinFlipTournament {
        double[][] matchAnswer;

        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            int k = in.nextInt(), m = in.nextInt();
            Node finals = null;
            double expectation = 0;
            for (int i = 0; i < m; i++) {
                int stage = in.nextInt(), match = in.nextInt();
                if (finals == null) {
                    finals = new Node(null);
                }
                expectation += addMatch(finals, k - stage, match);
            }

            matchAnswer = new double[k][2];
            for (int i = 0; i < k; i++) {
                if (i == 0) {
                    matchAnswer[i][0] = 0;
                    matchAnswer[i][1] = 1;
                } else {
                    matchAnswer[i][0] = matchAnswer[i - 1][0] + 1.0 / (i + 1) / (1 << i);
                    matchAnswer[i][1] = matchAnswer[i - 1][0] + 2.0 / (i + 1) / (1 << i);
                }
            }

            expectation += calcUnwatched(finals, k - 1, 0, true);
            out.println(expectation);
        }

        double addMatch(Node curNode, int depth, int match) {
            if (depth == 0) {
                int distToWatched = 0;
                Node node = curNode.parent;
                while (node != null && !node.watched) {
                    distToWatched++;
                    node = node.parent;
                }
                curNode.watched = true;
                // this match is interesting if we haven't seen anyone in this match in a later stage
                // iff winner of this match didn't win everything until the closest previously seen match
                if (node == null) {
                    return 1;
                } else {
                    return (double) ((1 << distToWatched) - 1) / (1 << distToWatched);
                }
            }
            if (match <= 1 << (depth - 1)) {
                if (curNode.left == null) {
                    curNode.left = new Node(curNode);
                }
                return addMatch(curNode.left, depth - 1, match);
            } else {
                if (curNode.right == null) {
                    curNode.right = new Node(curNode);
                }
                return addMatch(curNode.right, depth - 1, match - (1 << (depth - 1)));
            }
        }

        double calcUnwatched(Node curNode, int height, int unwatchedUp, boolean upToRoot) {
            if (curNode == null) {
                double result = 0;
                for (int i = 0; i <= height; i++) {
                    result += (1 << i) * matchAnswer[i + unwatchedUp][upToRoot ? 1 : 0];
                }
                return result;
            }
            double result = 0;
            if (!curNode.watched) {
                result += matchAnswer[unwatchedUp][upToRoot ? 1 : 0];
            }
            if (height > 0) {
                if (curNode.watched) {
                    upToRoot = false;
                    unwatchedUp = 0;
                } else {
                    unwatchedUp++;
                }
                result += calcUnwatched(curNode.left, height - 1, unwatchedUp, upToRoot);
                result += calcUnwatched(curNode.right, height - 1, unwatchedUp, upToRoot);
            }
            return result;
        }

        class Node {
            Node left;
            Node right;
            Node parent;
            boolean watched;

            public Node(Node parent) {
                this.parent = parent;
            }

        }

    }

    static class FastScanner {
        public BufferedReader br;
        public StringTokenizer st;

        public FastScanner(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
        }

        public FastScanner(String fileName) {
            try {
                br = new BufferedReader(new FileReader(fileName));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public String next() {
            while (st == null || !st.hasMoreElements()) {
                String line = null;
                try {
                    line = br.readLine();
                } catch (IOException e) {
                }
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }

    }
}

