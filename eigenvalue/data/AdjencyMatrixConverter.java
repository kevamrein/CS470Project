import java.io.*;
import java.util.*;

public class AdjencyMatrixConverter {
	private static String filename;
	private static int numNodes;	
	public static void main (String[] args) {
		//ArrayList<ArrayList<Integer>> matrix = new ArrayList<ArrayList<Integer>>();
		//ArrayList<Integer> innerMatrix;
		numNodes = Integer.parseInt(args[1]);
		int[][] array = new int[numNodes][numNodes];
		filename = args[0];
		File f = new File(filename);
		try {
			Scanner scan = new Scanner(f);
			scan.nextInt();
			//			array = new int[numNodes][numNodes];
			while (scan.hasNextInt()) {
				int x = scan.nextInt() - 1;
				int y = scan.nextInt() - 1;
				array[x][y] = 1;
				array[y][x] = 1;
			}
			scan.close();
			printMatrix(array);
		} catch (Exception e) {
			e.printStackTrace();
		}
		// printMatrix(array, args[2]);
	}

	private static void printMatrix(int[][] array) {


		String output = "output_" + filename;
		PrintWriter writer = null;
		try {
			writer = new PrintWriter(output);
			writer.println(numNodes);		

			for (int i = 0 ; i < array.length ; i++) {
				for (int j = 0 ; j < array[i].length ; j++) {
					writer.print(String.format("%d ", array[i][j]));
				}
				writer.println();
			}
		} catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			writer.close();
		}
	}
}
