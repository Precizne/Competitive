import java.util.Queue;
import java.util.LinkedList;
import java.util.Arrays;

class Cell {
    int x;
    int y;
    int d;
    int f;
    Cell(int x, int y, int d, int f) {
        this.x = x;
        this.y = y;
        this.d = d;
        this.f = f;
    }
}

public class Solution {
    public static void floodFill(Cell c, int[][] map, int[][][] distance, Queue<Cell> q) {
        int n = map.length;
        int m = map[0].length;
        if(c.x < 0 || c.x > n - 1 || c.y < 0 || c.y > m - 1 || distance[c.x][c.y][c.f] != Integer.MAX_VALUE) {
            return;
        }
        if(map[c.x][c.y] == 1) {
            if(c.f == 1) {
                return;
            }
            else {
                c.f = 1;
            }
        }
        distance[c.x][c.y][c.f] = c.d;
        q.add(c);
    }
    
    public static int solution(int[][] map) {
        int n = map.length;
        int m = map[0].length;
        int[][][] distance = new int[n][m][2];
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < 2; k++) {
                    distance[i][j][k] = Integer.MAX_VALUE;   
                }
            }
        }
        Queue<Cell> q = new LinkedList<>();
        q.add(new Cell(0, 0, 1, 0));
        distance[0][0][0] = 1;
        while(!q.isEmpty()) {
            Cell c = q.poll();
            floodFill(new Cell(c.x + 1, c.y, c.d + 1, c.f), map, distance, q);
            floodFill(new Cell(c.x - 1, c.y, c.d + 1, c.f), map, distance, q);
            floodFill(new Cell(c.x, c.y + 1, c.d + 1, c.f), map, distance, q);
            floodFill(new Cell(c.x, c.y - 1, c.d + 1, c.f), map, distance, q);
        }
        return Math.min(distance[n - 1][m - 1][0], distance[n - 1][m - 1][1]);
    }

   public static void main(String[] args) {
      int[][] arr = {{0, 0, 1, 1}, {1, 0 ,0 ,0}, {0, 0, 1, 1}, {0, 1, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 0}};
      int res = solution(arr);
      System.out.println(res);
   }
}
