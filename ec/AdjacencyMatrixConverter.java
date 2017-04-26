import java.io.*;
import java.util.*;

/**
 * Converts a file containing edge lists to a file containing
 * an adjacency matrix.
 *
 * Usage: java AdjacencyMatrixConverter EDGELISTFILE NUMBEROFNODES FILETOWRITETO
 *
 * @author Kevin Amrein, Sam Carswell, Chuchi Soriano
 */
public class AdjacencyMatrixConverter {
    public static void main (String[] args) {
        int numNodes = Integer.parseInt(args[1]);
        int[][] array = new int[numNodes][numNodes];
        File f = new File(args[0]);
        try {
            Scanner scan = new Scanner(f);
            scan.nextInt();

            while (scan.hasNextInt()) {
                int x = scan.nextInt() - 1;
                int y = scan.nextInt() - 1;
                array[x][y] = 1;
                array[y][x] = 1;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        if (args.length <= 2)
            printMatrix(array, numNodes);
        else
            writeMatrix(array, numNodes, args[2]);
    }
    
    /**
     * Prints the created matrix to standard out
     *
     * @param array int array representing adjacency matrix
     * @param numNodes int number of nodes in the matrix
     */
    private static void printMatrix(int[][] array, int numNodes) {
        System.out.println(numNodes);
        for (int i = 0 ; i < array.length ; i++) {
            for (int j = 0 ; j < array[i].length ; j++) {
                System.out.printf("%d ", array[i][j]);
            }
            System.out.println();
        }
    }

    /**
     * Writes the created adjacency matrix to the passed filepath
     *
     * @param array int array representing adjacency matrix
     * @param numNodes int number of nodes in the matrix
     * @param file String path that the new file will be created at
     */
    private static void writeMatrix(int[][] array, int numNodes, String file) {
        File f = new File(file);

        try {
            PrintWriter writer = new PrintWriter(f);

            writer.println(numNodes);

            for (int i = 0 ; i < array.length ; i++) {
                for (int j = 0 ; j < array[i].length ; j++) {
                    writer.printf("%d ", array[i][j]);
                }
                writer.println();
            }
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
