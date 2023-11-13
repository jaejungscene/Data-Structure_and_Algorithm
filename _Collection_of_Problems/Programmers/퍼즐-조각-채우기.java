import java.util.*;
class Solution {
    class Figure{
        List<int[]> points = new ArrayList<>();
    }

    public int solution(int[][] game_board, int[][] table) {
        // table에서 각각의 퍼즐에 대한 좌표 값을 bfs로 구함.
        List<Figure[]> figures = new ArrayList<>();
        int mode = 1; //채워진 곳 찾기
        for(int y=0; y<table.length; y++)
            for(int x=0; x<table[0].length; x++)
                if(table[y][x]==mode)
                    rotate(getFigureByBfs(table, x, y, mode), figures);

        int answer = 0;
        mode = 0; // 빈곳 찾기
        for(int y=0; y<game_board.length; y++)
            for(int x=0; x<game_board[0].length; x++)
                if(game_board[y][x]==mode)
                    answer += match(getFigureByBfs(game_board, x, y, mode), figures);

        return answer;
    }

    // return: {size, {x, y} points... }
    public Figure getFigureByBfs(int[][] map, int x, int y, int mode){
        Figure fig = new Figure();
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{x,y});
        map[y][x] = mode==1 ? 0:1;
        int remain;
        int[] now;
        int tempX, tempY;
        int[] dx = {0, 1, 0, -1};
        int[] dy = {1, 0, -1, 0};

        while(!q.isEmpty()){
            remain = q.size();
            for(int i=0; i<remain; i++){
                now = q.remove();
                fig.points.add(new int[]{now[0]-x,now[1]-y});

                for(int j=0; j<4; j++){
                    tempX = now[0] + dx[j];
                    tempY = now[1] + dy[j];
                    if(-1<tempX && tempX<map.length &&
                       -1<tempY && tempY<map[0].length &&
                       map[tempY][tempX] == mode){
                        q.add(new int[]{tempX, tempY});
                        map[tempY][tempX] = mode==1 ? 0 : 1; // visited
                    }
                }
            }
        }
        arrangeFig(fig);
        return fig;
    }

    public void arrangeFig(Figure fig){
        fig.points.sort(new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                if(o1[0]!=o2[0])
                    return o1[0]-o2[0];
                else
                    return o1[1]-o2[1];
            }
        });
    }

    public void rotate(Figure origin, List<Figure[]> figures){
        // 회전변환 행렬에 의해 (x,y)의 90도 회전된 좌표는 (-y,x)
        Figure[] figs = new Figure[4];
        figs[0] = origin;

        for(int i=1; i<4; i++){
            figs[i] = new Figure();
            for(int[] p : figs[i-1].points)
                figs[i].points.add(new int[]{-p[1], p[0]});
            arrangeFig(figs[i]);
        }
        figures.add(figs);
    }

    public int match(Figure emptyFig, List<Figure[]> figures){
        Figure[] nowFig;
        int xDiff = 0;
        int yDiff = 0;
        int cnt = 0;
        for(int i=0; i<figures.size(); i++){
            nowFig = figures.get(i);
            if(nowFig[0].points.size() == emptyFig.points.size()) {
                for (int j = 0; j < nowFig.length; j++) {
                    cnt = 1;
                    xDiff = nowFig[j].points.get(0)[0] - emptyFig.points.get(0)[0];
                    yDiff = nowFig[j].points.get(0)[1] - emptyFig.points.get(0)[1];
                    for (int k = 1; k < nowFig[j].points.size(); k++) {
                        if (xDiff == (nowFig[j].points.get(k)[0] - emptyFig.points.get(k)[0])
                            && yDiff == (nowFig[j].points.get(k)[1] - emptyFig.points.get(k)[1])) {
                            cnt++;
                        } else {
                            break;
                        }
                    }

                    if (cnt == emptyFig.points.size()) {
                        figures.remove(i);
                        return cnt;
                    }
                }
            }
        }
        return 0;
    }
}