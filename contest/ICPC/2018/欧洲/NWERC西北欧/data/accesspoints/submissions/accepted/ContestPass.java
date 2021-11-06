import java.util.Scanner;
import java.util.LinkedList;

public class ContestPass {
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
	xTeams = new double[nrTeams];
	yTeams = new double[nrTeams];
        
        double score = solve(xCoords, xTeams) + solve(yCoords, yTeams);
	if (args.length > 0 && "visualize".equals(args[0])) {
		System.out.println(nrTeams);
		for (int i = 0; i < nrTeams; i++) {
			System.out.println(xCoords[i] + " " + yCoords[i] + " " + xTeams[i] + " " + yTeams[i]);
		}
	} else {
		System.out.print(score);
	}
    }
    static double[] xTeams;
    static double[] yTeams;
    
    private static double solve(int[] coords, double[] teams) {
        LinkedList<Item> items = new LinkedList();
        items.add(new Item(coords.length-1, coords[coords.length-1]));
        for (int index = coords.length-2; index >= 0; index--) {
            if (coords[index] < items.getFirst().avg) {
                items.addFirst(new Item(index, coords[index]));
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
        return score(coords, items, teams);
    }

    private static double score(int[] coords, LinkedList<Item> placements, double[] teams) {
        double score = 0;
        int processIndex = 0;

        while (!placements.isEmpty()) {
            Item first = placements.removeFirst();
            int lstIndex = first.lastIndex;

            while (processIndex <= lstIndex) {
                double dist = (coords[processIndex] - first.avg);
		teams[processIndex] = first.avg;
                score += dist * dist;
                processIndex++;
            }
        }
        return score;
    }
}

class Item {
    public double avg;
    public long sum;
	public int count, lastIndex;

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

	public String toString(){
		return String.format("%d %d (%d)", sum, count, lastIndex);
	}
}
