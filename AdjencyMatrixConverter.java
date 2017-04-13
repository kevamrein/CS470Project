import java.io.*;
import java.util.*;

public class AdjencyMatrixConverter {
        public static void main (String[] args) {
                //ArrayList<ArrayList<Integer>> matrix = new ArrayList<ArrayList<Integer>>();
                //ArrayList<Integer> innerMatrix;
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
                printMatrix(array);
        }

        private static void printMatrix(int[][] array) {
            for (int i = 0 ; i < array.length ; i++) {
                for (int j = 0 ; j < array[i].length ; j++) {
                    System.out.printf("%d ", array[i][j]);
                }
                System.out.println();
            }
        }
}
