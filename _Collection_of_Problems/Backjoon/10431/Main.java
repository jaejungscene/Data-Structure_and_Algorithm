import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
             BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out))) {

            int P = Integer.parseInt(br.readLine());

            for (int i = 0; i < P; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());

                int testCaseNum = Integer.parseInt(st.nextToken());

                int[] heights = new int[20];
                for (int j = 0; j < 20; j++) {
                    heights[j] = Integer.parseInt(st.nextToken());
                }

                int totalSteps = calculateTotalSteps(heights);

                bw.write(testCaseNum + " " + totalSteps + "\n");
            }
        }
    }

    public static int calculateTotalSteps(int[] heights) {
        List<Integer> line = new ArrayList<>();
        int totalSteps = 0;
        
        for (int currentStudentHeight : heights) {
            int insertionPoint = 0;
            while (insertionPoint < line.size() && line.get(insertionPoint) < currentStudentHeight) {
                insertionPoint++;
            }
            line.add(insertionPoint, currentStudentHeight);
            totalSteps += line.size() - 1 - insertionPoint;
        }
        return totalSteps;
    }
}