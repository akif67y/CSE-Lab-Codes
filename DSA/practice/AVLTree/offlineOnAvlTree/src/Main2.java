import java.io.*;

public class Main2 {
    public static void main(String[] args) {
        RedBlackTree<Integer> tree = new RedBlackTree<>();
        String inputFileName = "D:\\CSE-Lab-Codes\\DSA\\practice\\AVLTree\\offlineOnAvlTree\\src\\input2.txt";
        String outputFileName = "D:\\CSE-Lab-Codes\\DSA\\practice\\AVLTree\\offlineOnAvlTree\\src\\output2.txt";

        try (
            BufferedReader br = new BufferedReader(new FileReader(inputFileName));
            BufferedWriter bw = new BufferedWriter(new FileWriter(outputFileName))
        ) {
            String line = br.readLine();
            if (line == null) return;
            int N = Integer.parseInt(line.trim());
            bw.write(String.valueOf(N));
            bw.newLine();

            for (int i = 0; i < N; i++) {
                line = br.readLine();
                if (line == null) break;
                
                String[] parts = line.trim().split("\\s+");
                int command = Integer.parseInt(parts[0]);
                int value = Integer.parseInt(parts[1]);

                switch (command) {
                    case 0: 
                        boolean deleted = tree.delete(value);
                        bw.write("0 " + value + " " + (deleted ? "1" : "0"));
                        bw.newLine();
                        break;

                    case 1: 
                        boolean inserted = tree.insert(value);
                        bw.write("1 " + value + " " + (inserted ? "1" : "0"));
                        bw.newLine();
                        break;

                    case 2: 
                        boolean found = tree.search(value);
                        bw.write("2 " + value + " " + (found ? "1" : "0"));
                        bw.newLine();
                        break;
                        
                    case 3: 
                        int count = tree.countLessThan(value);
                        bw.write("3 " + value + " " + count);
                        bw.newLine();
                        break;
                }
            }
            System.out.println("Processing complete. Check " + outputFileName);

        } catch (IOException e) {
            System.err.println("Error processing file: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("Error parsing integer from file: " + e.getMessage());
        }
    }
}
