import java.io.*;
import java.util.*;

class Country {
    int id;
    int gold;
    int silver;
    int bronze;

    public Country(int id, int gold, int silver, int bronze) {
        this.id = id;
        this.gold = gold;
        this.silver = silver;
        this.bronze = bronze;
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());

        List<Country> countries = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            int id = Integer.parseInt(st.nextToken());
            int gold = Integer.parseInt(st.nextToken());
            int silver = Integer.parseInt(st.nextToken());
            int bronze = Integer.parseInt(st.nextToken());
            countries.add(new Country(id, gold, silver, bronze));
        }

        Country targetCountry = null;
        for (Country c : countries) {
            if (c.id == K) {
                targetCountry = c;
                break;
            }
        }

        int rank = 1; 
        for (Country otherCountry : countries) {
            if (otherCountry.id == K) continue; 

            if (otherCountry.gold > targetCountry.gold) {
                rank++;
            } else if (otherCountry.gold == targetCountry.gold && otherCountry.silver > targetCountry.silver) {
                rank++;
            } else if (otherCountry.gold == targetCountry.gold && otherCountry.silver == targetCountry.silver && otherCountry.bronze > targetCountry.bronze) {
                rank++;
            }
        }
        
        System.out.println(rank);
    }
}