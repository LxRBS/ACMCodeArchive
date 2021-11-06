import java.util.ArrayList;
import java.util.Scanner;

public class AllInTheFamily_John {

	public static ArrayList<Map> table = new ArrayList<>();
	
	public static Node getNode(String name)
	{
		for(Map map : table) {
			if (map.name.equals(name))
				return map.tree;
		}
		Map newMap = new Map(name, new Node());
		table.add(newMap);
		return newMap.tree;
	}
	
	public static void main(String [] args)
	{
		int nbuild, nquery;
		Scanner in = new Scanner(System.in);
		
		nbuild = in.nextInt();
		nquery = in.nextInt();
		for(int i=1; i<=nbuild; i++) {
			String name = in.next();
			Node p = getNode(name);
			int nchildren = in.nextInt();
			for(int j=1; j<=nchildren; j++) {
				name = in.next();
				Node child = getNode(name);
				child.parent = p;
				p.children.add(child);
			}
		}
		
		Node root = null;
		for(Map m : table) {
			if (m.tree.parent == null) {
				root = m.tree;
				break;
			}
		}
		if (root == null) {
			System.out.println("ERROR: No root in tree");
			System.exit(-1);
		}
		setDepth(root, 0);
/*		
		for(Map m : table) {
			System.out.println(m.name + ": depth = " + m.tree.depth);
		}
/**/
		for(int i=1; i<=nquery; i++) {
			String name1 = in.next();
			String name2 = in.next();
			Node n1 = getNode(name1);
			Node n2 = getNode(name2);
			int removed = n1.depth - n2.depth;
			if (removed >= 0) {
				for(int j=1; j<=removed; j++) 
					n1 = n1.parent;
				int cousinLevel = 0;
				while (n1 != n2) {
					n1 = n1.parent;
					n2 = n2.parent;
					cousinLevel++;
				}
				if (cousinLevel == 0) {
					outputChild(name1, name2, removed);
				}
				else if (cousinLevel == 1 && removed == 0)
					System.out.println(name1 + " and " + name2 + " are siblings");
				else
					outputCousin(name1, name2, cousinLevel-1, removed);
			}
			else {
				removed = -removed;
				for(int j=1; j<=removed; j++) 
					n2 = n2.parent;
				int cousinLevel = 0;
				while (n1 != n2) {
					n1 = n1.parent;
					n2 = n2.parent;
					cousinLevel++;
				}
				if (cousinLevel == 0) {
					outputChild(name2, name1, removed);
				}
				else if (cousinLevel == 1 && removed == 0)
					System.out.println(name1 + " and " + name2 + " are siblings");
				else
					outputCousin(name1, name2, cousinLevel-1, removed);
			}
		}
	}
	
	public static void setDepth(Node n, int d)
	{
		n.depth = d;
		for(Node child : n.children) {
			setDepth(child, d+1);
		}
	}
	
	public static void outputChild(String n1, String n2, int level)
	{
		System.out.print(n1 + " is the ");
		if (level > 1) {
			for(int i=3; i<=level; i++)
				System.out.print("great ");
			System.out.print("grand");
		}
		System.out.println("child of " + n2);
	}
	
	public static void outputCousin(String n1, String n2, int level, int removed)
	{
		System.out.print(n1 + " and " + n2 + " are " + level);
		switch (level%10) {
		case 1 : if (level/10 == 1)
					System.out.print("th");
				 else 
					System.out.print("st");
				 break;
		case 2 : if (level/10 == 1)
					System.out.print("th");
				 else 
					System.out.print("nd");
				 break;
		case 3 : if (level/10 == 1)
					System.out.print("th");
				 else 
					System.out.print("rd");
				 break;
		default : System.out.print("th");
		}
		System.out.print(" cousins");
		if (removed > 0) {
			System.out.print(", " + removed + " time");
			if (removed > 1)
				System.out.print("s");
			System.out.print(" removed");
		}
		System.out.println();
	}
}

class Node
{
	public int depth;
	public Node parent;
	public ArrayList<Node> children;
	
	public Node()
	{
		depth = 0;
		parent = null;
		children = new ArrayList<>();
	}
}

class Map
{
	public String name;
	public Node tree;
	
	public Map(String name, Node tree)
	{
		this.name = name;
		this.tree = tree;
	}
}