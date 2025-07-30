import java.util.Queue;
import java.util.LinkedList;

class ServerEvent {
    int startTime;
    int count;
    
    public ServerEvent(int startTime, int count) {
        this.startTime = startTime;
        this.count = count;
    }
}

class Solution {
    public int solution(int[] players, int m, int k) {
        Queue<ServerEvent> q = new LinkedList<>();
        
        int totalIncrServerNum = 0;
        int nowIncreServerNum = 0;
        
        for (int i=0; i<players.length; i++) {
            ServerEvent serverEvent = q.peek();
            if (serverEvent != null) {
            }
            if (serverEvent != null && i - serverEvent.startTime == k) {
                q.poll();
                nowIncreServerNum -= serverEvent.count;
            }
            
            int neededServerNum = players[i] / m;
            int newIncreServerNum = neededServerNum - nowIncreServerNum;
            if (newIncreServerNum > 0) {
                q.offer(new ServerEvent(i, newIncreServerNum));
                nowIncreServerNum += newIncreServerNum;
                totalIncrServerNum += newIncreServerNum;
            }
        }
        return totalIncrServerNum;
    }
}