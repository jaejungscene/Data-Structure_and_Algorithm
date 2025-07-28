import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int N = Integer.parseInt(st.nextToken());
        String gameType = st.nextToken();

        Set<String> uniquePlayers = new HashSet<>();
        for (int i = 0; i < N; i++) {
            uniquePlayers.add(br.readLine());
        }

        int requiredPlayersPerGame;
        switch (gameType) {
            case "Y":
                requiredPlayersPerGame = 1;
                break;
            case "F":
                requiredPlayersPerGame = 2;
                break;
            case "O":
                requiredPlayersPerGame = 3;
                break;
            default:
                return;
        }

        int maxPlayedGames = uniquePlayers.size() / requiredPlayersPerGame;
        System.out.println(maxPlayedGames);
    }
}