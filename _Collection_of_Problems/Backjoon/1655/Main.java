import java.util.PriorityQueue;
import java.util.Comparator;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        int N = Integer.parseInt(br.readLine());

        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Comparator.reverseOrder());

        for (int i=0; i<N; i++) {
            int nowNum = Integer.parseInt(br.readLine());
            int minHeapSize = minHeap.size();
            int maxHeapSize = maxHeap.size();

            if (minHeapSize == maxHeapSize) {
                maxHeap.offer(nowNum);
            } else {
                minHeap.offer(nowNum);
            }

            if (!maxHeap.isEmpty() && !minHeap.isEmpty() && maxHeap.peek() > minHeap.peek()) {
                int maxNumOfMaxHeap = maxHeap.poll();
                int minNumOfMinHeap = minHeap.poll();
                minHeap.offer(maxNumOfMaxHeap);
                maxHeap.offer(minNumOfMinHeap);
            }

            sb.append(maxHeap.peek()).append("\n");
        }
        
        System.out.println(sb);
    }
}