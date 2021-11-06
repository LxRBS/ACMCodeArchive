import java.io.IOException;
import java.io.PrintWriter;
import java.io.UncheckedIOException;
import java.util.*;
import java.util.function.Supplier;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Tests {
    private static final int MAX_S = 1000_000;
    private static final int MAX_SIZE = 30;
    private static final int MAX_N = 94;

    private int tests = 1;
    private final Random random = new Random(4570943857023842035L);
    private final List<Character> CHARS = IntStream.rangeClosed(33, 126).mapToObj(i -> (char) i).collect(Collectors.toList());

    void test(final int s, final Image... images) {
        test(s, Arrays.asList(images));
    }

    void test(final int s, final List<Image> images) {
        assignChars(images);
        images.forEach(Image::fixIfNeeded);

        try {
            final Image first = images.get(0);
            try (PrintWriter out = new PrintWriter(String.format("%02d", tests++))) {
                out.printf("%d %d %d %d%n", images.size(), first.getW(), first.getH(), s);
                for (final Image image : images) {
                    out.println(image.toString());
                }
            }
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    }

    private void assignChars(final List<Image> images) {
        final Set<Character> used = images.stream()
                .map(image -> image.ch)
                .collect(Collectors.toSet());

        final List<Character> unusedChar = shuffle(CHARS);
        unusedChar.removeAll(used);
        final Iterator<Character> charI = unusedChar.iterator();
        for (Image image : images) {
            if (image.ch == 0) {
                image.ch = charI.next();
            }
        }
    }

    private <T> List<T> shuffle(final List<? extends T> items) {
        final List<T> result = new ArrayList<>(items);
        Collections.shuffle(result, random);
        return result;
    }

    private class Image {
        char ch;
        boolean[][] pixels;

        Image(int w, int h) {
            pixels = new boolean[h][w];
        }

        Image(char ch, String... rows) {
            this(rows[0].length(), rows.length);
            for (int i = 0; i < getH(); i++) {
                for (int j = 0; j < getW(); j++) {
                    pixels[i][j] = rows[i].charAt(j) == '#';
                }
            }
            this.ch = ch;
        }

        public void fixIfNeeded() {
            if (Arrays.stream(pixels).noneMatch(row -> IntStream.range(0, getW()).anyMatch(i -> row[i]))) {
                pixels[randomInt(getH())][randomInt(getW())] = true;
            }
        }

        public int getW() {
            return pixels[0].length;
        }

        public int getH() {
            return pixels.length;
        }

        @Override
        public String toString() {
            return Stream.concat(
                    Stream.of(Character.toString(ch)),
                    Arrays.stream(pixels).map(row -> IntStream.range(0, row.length).mapToObj(i -> row[i] ? "#" : ".").collect(Collectors.joining())))
                    .collect(Collectors.joining(System.lineSeparator()));
        }
    }

    public void run() {
        test(
                16,
                new Image('I', ".#..", "#.#.", ".#..", ".#..", "###."),
                new Image('C', ".##.", "#..#", "#...", "#..#", ".##."),
                new Image('P', "###.", "#..#", "###.", "#...", "#...")
        );
        test(
                19,
                new Image('Q', ".#.#."),
                new Image('W', "#.#.#")
        );

        randomSeq(97, 2, 3, 1, 1, 0);
        randomSeq(100, 3, 5, 3, 1, 1);
        randomSeq(100, 3, 15, 3, 5, 0);
        randomSeq(100, 3, 15, 3, 5, 2);
        randomP(100, 5, 10, 10, 0.5);

        randomSeq(almost(MAX_S), MAX_N, MAX_SIZE, MAX_SIZE, MAX_SIZE / 2, 0);
        randomSeq(almost(MAX_S), MAX_N, MAX_SIZE, MAX_SIZE, MAX_SIZE / 2 - 1, 1);
        randomP(almost(MAX_S), almost(MAX_N), MAX_SIZE, 1, 0.5);
        randomP(almost(MAX_S), almost(MAX_N), 1, MAX_SIZE, 0.5);
        randomP(MAX_S, MAX_N, MAX_SIZE, MAX_SIZE, 1);
        randomP(MAX_S, MAX_N, MAX_SIZE, MAX_SIZE, 0.1);
        randomP(MAX_S, MAX_N, MAX_SIZE, MAX_SIZE, 0);
        randomP(MAX_S, MAX_N, MAX_SIZE, MAX_SIZE, 0.9);
        randomP(MAX_S, MAX_N, MAX_SIZE, MAX_SIZE, 0.5);
        randomP(almost(MAX_S / 10), almost(MAX_N / 10), randomInt(1, MAX_SIZE), randomInt(1, MAX_SIZE), 1);
        randomP(almost(MAX_S / 10), almost(MAX_N / 10), randomInt(1, MAX_SIZE), randomInt(1, MAX_SIZE), 0.1);
        randomP(almost(MAX_S / 10), almost(MAX_N / 10), randomInt(1, MAX_SIZE), randomInt(1, MAX_SIZE), 0);
        randomP(almost(MAX_S / 10), almost(MAX_N / 10), randomInt(1, MAX_SIZE), randomInt(1, MAX_SIZE), 0.9);
        randomP(almost(MAX_S / 10), almost(MAX_N / 10), randomInt(1, MAX_SIZE), randomInt(1, MAX_SIZE), 0.5);
        for (int iter = 0; iter < 10; iter++) {
            randomP(randomInt(1, MAX_S), randomInt(1, MAX_N), randomInt(1, MAX_SIZE), randomInt(1, MAX_SIZE), 0.01 * randomInt(0, 100));
        }
        for (int iter = 0; iter < 10; iter++) {
            int w = randomInt(3, MAX_SIZE);
            randomSeq(randomInt(1, MAX_S), randomInt(1, MAX_N), w, randomInt(1, MAX_SIZE), randomInt(1, (w - 1) / 2), randomInt(0, 5));
        }
        for (int iter = 0; iter < 10; iter++) {
            int w = randomInt(3, MAX_SIZE);
            randomSeqWithoutS(randomInt(1, MAX_N), w, randomInt(1, MAX_SIZE), randomInt(1, (w - 1) / 2), randomInt(0, 5));
        }
        randomSeqSpecific(MAX_S, MAX_N, MAX_SIZE, MAX_SIZE, randomInt(1, (MAX_SIZE - 1) / 2), '.');
        randomSeqSpecific(MAX_S, MAX_N, MAX_SIZE, MAX_SIZE, randomInt(1, (MAX_SIZE - 1) / 2), '#');
        randomP(1, MAX_N, MAX_SIZE, MAX_SIZE, 0.5);
        randomP(MAX_S, 1, MAX_SIZE, MAX_SIZE, 0.5);
        randomSeq(MAX_S, 1, MAX_SIZE, MAX_SIZE, 1, 0);
    }

    private void randomSeqWithoutS(final int n, final int w, final int h, final int chunks, final int increased) {
        final List<Image> images = randomImages(n, () -> randomImageSeq(w, h, chunks));
        for (int i = 0; i < increased; i++) {
            images.get(randomInt(images.size())).pixels[randomInt(h)] = randomRowSeq(w, chunks + 1);
        }
        int maxC = chunks;
        if (increased > 0) {
            maxC += 1;
        }
        int delta = randomInt(-2, 2);
        test((MAX_S / (2 * maxC) - 1) * (2 * maxC) + delta, images);
    }

    private void randomSeqSpecific(final int s, final int n, final int w, final int h, final int chunks, final char who) {
        final List<Image> images = randomImages(n, () -> randomImageSeq(w, h, chunks));
        assignChars(images);
        for (int j = 0; j < images.size(); j++) {
            if (images.get(j).ch == who) {
                images.get(j).pixels[randomInt(h)] = randomRowSeq(w, chunks + 1);
            }
        }
        test(s, images);
    }
    
    private void randomSeq(final int s, final int n, final int w, final int h, final int chunks, final int increased) {
        final List<Image> images = randomImages(n, () -> randomImageSeq(w, h, chunks));
        for (int i = 0; i < increased; i++) {
            images.get(randomInt(images.size())).pixels[randomInt(h)] = randomRowSeq(w, chunks + 1);
        }
        test(s, images);
    }

    private Image randomImageSeq(final int w, final int h, final int chunks) {
        final Image image = new Image(w, h);
        for (int i = 0; i < h; i++) {
            image.pixels[i] = randomRowSeq(w, chunks);
        }
        return image;
    }

    private boolean[] randomRowSeq(final int w, final int chunks) {
        final int[] sizes = new int[chunks * 2 + 1];
        Arrays.fill(sizes, 1);
        sizes[0] = sizes[sizes.length - 1] = 0;
        for (int sum = chunks * 2; sum <= w; sum++) {
            sizes[randomInt(sizes.length)]++;
        }

        final boolean[] row = new boolean[w];
        for (int i = 0, current = 0; i < sizes.length; i++) {
            for (int j = 0; j < sizes[i]; j++) {
                row[current++] = i % 2 == 1;
            }
        }
        return row;
    }

    private void randomP(final int s, final int n, final int w, final int h, final double p) {
        test(s, randomImages(n, () -> randomImageP(w, h, p)));
    }

    private Image randomImageP(final int w, final int h, final double p) {
        final Image image = new Image(w, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                image.pixels[i][j] = random.nextDouble() <= p;
            }
        }
        return image;
    }

    private List<Image> randomImages(final int n, final Supplier<Image> supplier) {
        return Stream.generate(supplier).limit(n).collect(Collectors.toList());
    }

    private int randomInt(final int bound) {
        return random.nextInt(bound);
    }

    private int almost(final int v) {
        return randomInt(v * 9 / 10, v);
    }

    private int randomInt(final int from, final int to) {
        return from + randomInt(to - from + 1);
    }

    public static void main(String[] args) {
        new Tests().run();
    }
}