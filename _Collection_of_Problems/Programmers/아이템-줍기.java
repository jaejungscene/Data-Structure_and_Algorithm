import java.util.Queue;
import java.util.LinkedList;

class Solution {
    public int solution(int[][] rectangle, int characterX, int characterY, int itemX, int itemY) {
        int answer = -1;
        boolean[][] board = new boolean[51*2][51*2]; //false auto initialization
		int[] dx = {1, 0, -1, 0};
        int[] dy = {0, 1, 0, -1};
        int x1, y1, x2, y2;
        
        characterX *= 2;
        characterY *= 2;
        itemX *= 2;
        itemY *= 2;
        
        for(int i=0; i<rectangle.length; i++){
            for(int j=0; j<rectangle[0].length; j++)
                rectangle[i][j] *= 2;
            x1 = rectangle[i][0];
            y1 = rectangle[i][1];
            x2 = rectangle[i][2];
            y2 = rectangle[i][3];
            
            for(int x=x1; x<=x2; x++)
                for(int y=y1; y<=y2; y++)
                    board[x][y] = true;
        }
        
        for(int i=0; i<rectangle.length; i++){
            x1 = rectangle[i][0];
            y1 = rectangle[i][1];
            x2 = rectangle[i][2];
            y2 = rectangle[i][3];
            
            for(int x=x1+1; x<=x2-1; x++)
                for(int y=y1+1; y<=y2-1; y++)
                    board[x][y] = false;
        }
        
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{characterX, characterY});
        int[] now;
        int size;
       
        while(!q.isEmpty()){
            size = q.size();
            answer++;
            for(int i=0; i<size; i++){
                now = q.remove();
                if(now[0]==itemX && now[1]==itemY)
                    return answer/2;
                
                board[now[0]][now[1]] = false;
                for(int j=0; j<4; j++)
                    if(board[now[0]+dx[j]][now[1]+dy[j]])
                        q.add(new int[]{now[0]+dx[j], now[1]+dy[j]});
            }
        }
        
        return -1;
    }
    
    
}