/**
 * DFS와BFS
 * https://www.acmicpc.net/problem/1260
 */ 
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    public void dfs(int now, List<Integer>[]G, boolean[] visited, StringBuilder sb){
        visited[now] = true;
        sb.append(now + " ");
        for(int i : G[now]){
            if(!visited[i])
                dfs(i, G, visited, sb);
        }
    }

    public void bfs(int now, List<Integer>[]G, boolean[] visited, StringBuilder sb){
        Queue<Integer> q = new ArrayDeque<>();
        q.add(now);
        while (!q.isEmpty()) {
            now = q.remove();
            visited[now] = true;
            sb.append(now + " ");
            for(int i : G[now]){
                if(visited[i] == false){
                    visited[i] = true;
                    q.add(i);
                }
            }
        }
    }

    public void solution(int N, int M, int V, List<Integer>[] G){
        boolean visited[] = new boolean[N+1];
        StringBuilder sb = new StringBuilder();

        dfs(V, G, visited, sb);
        sb.append("\n");
        visited = new boolean[N+1];
        bfs(V, G, visited, sb);

        System.out.println(sb);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine(), " ");
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        int V = Integer.parseInt(st.nextToken());

        List<Integer>[] G = new ArrayList[N+1];
        for(int i=0; i<N+1; i++)
            G[i] = new ArrayList<>();

        int v1, v2;
        for(int i=0; i<M; i++){
            st = new StringTokenizer(br.readLine(), " ");
            v1 = Integer.parseInt(st.nextToken());
            v2 = Integer.parseInt(st.nextToken());
            G[v1].add(v2);
            G[v2].add(v1);
        }

        for(int i=0; i<N+1; i++){
            if(G[i].size()!=0)
                G[i].sort(Comparator.naturalOrder());
        }
        int min = 1000000001;

        System.out.println(Arrays.toString(G));
        new Main().solution(N, M, V, G);
    }
}