import java.util.Scanner;
import java.util.LinkedList;

public class ContestPassListEnding {
    public static void main(String[] args) throws Exception {
        // Read input
        Scanner sc = new Scanner (System.in);
        int nrTeams = sc.nextInt();
        int[] xCoords = new int[nrTeams];
        int[] yCoords = new int[nrTeams];
        for (int i = 0; i < nrTeams; i++) {
            xCoords[i] = sc.nextInt();
            yCoords[i] = sc.nextInt();
        }
        
        double score = solve(xCoords) + solve(yCoords);
        System.out.print(score);
    }
    
    private static double solve(int[] coords) {
        LinkedList<Item> items = new LinkedList();
        items.add(new Item(coords.length-1, coords[coords.length-1]));
        for (int index = coords.length-2; index >= 0; index--) {
            if (coords[index] < items.getFirst().avg) {
                items.add(new Item(index, coords[index]));
            } else {
                Item first = items.removeFirst();
                first.add(coords[index]);
                while (!items.isEmpty() && first.avg > items.getFirst().avg) {
                    Item second = items.removeFirst();
                    first.mergeInLater(second);
                }
                items.addFirst(first);
            }
        }
        return score(coords, items);
    }
    
    private static double score(int[] coords, LinkedList<Item> placements) {
        double score = 0;
        int processIndex = 0;
        while (!placements.isEmpty()) {
            Item first = placements.removeFirst();
            int lstIndex = first.lastIndex;

            while (processIndex <= lstIndex) {
                double dist = (coords[processIndex] - first.avg);
                score += dist * dist;
                processIndex++;
            }
        }
        return score;
    }
}

class Item {
    public double avg;
    public int sum, count, lastIndex;

    public Item(int index, int fstItem) {
        sum = fstItem;
        count = 1;
        avg = sum;
        lastIndex = index;
    }

    public void add(int value) {
        sum += value;
        count++;
        avg = ((double)sum) / count;
    }
    
    public void mergeInLater(Item item) {
        sum += item.sum;
        count += item.count;
        avg = ((double)sum) / count;
        lastIndex = item.lastIndex;
    }
}
