import java.util.ArrayList;
import java.util.Arrays;

class Graph {
    int vtx;
    int[][] adj;
    ArrayList<Integer> path;
    boolean[] visited;
        
    Graph(int[][] times, int n) {
        vtx = n;
        adj = times;
    }
    
    void dfs(int src, int time, ArrayList<Integer> cpath) {
        if((time < 0 && src == vtx - 1) || path.size() == vtx - 2 || time <= -999) {
            return;
        }
        if(time >= 0 && src == vtx - 1) {
            if(cpath.size() > path.size()) {
                path = new ArrayList<Integer>(cpath);
            }
            return;
        }
        if(visited[src]) {
            return;
        }
        visited[src] = true;
        cpath.add(src - 1);
        for(int dst = 1; dst < vtx; dst++) {
            if(src != dst) {
                dfs(dst, time - adj[src][dst], cpath);
            }
        }
        cpath.remove(cpath.size() - 1);
        visited[src] = false;
    }
        
    void dfsAll(int time) {
        path = new ArrayList<Integer>();
        visited = new boolean[vtx];
        visited[0] = true;
        for(int i = 1; i < vtx - 1; i++) {
            dfs(i, time - adj[0][i], new ArrayList<Integer>());
        }
    }
    
    void FloydWarshall() {
        for(int i = 0; i < vtx; i++) {
            for(int j = 0; j < vtx; j++) {
                for(int k = 0; k < vtx; k++) {
                    adj[i][j] = Math.min(adj[i][j], adj[i][k] + adj[k][j]);
                }
            }
        }
    }
    
    boolean hasNegativeCycle() {
        FloydWarshall();
         trace();
        for(int i = 0; i < vtx; i++) {
            if(adj[i][i] < 0) {
                return true;
            }
        }
        return false;
    }

   void trace() {
      for(int i = 0; i < vtx; i++) {
         for(int j = 0; j < vtx; j++) {
            System.out.print(adj[i][j] + " ");
         }
         System.out.println();
      }
   }
}

public class Solution {
    public static int[] solution(int[][] times, int times_limit) {
        int n = times.length;
        Graph g = new Graph(times, n);
        int[] ans;
        
        if(g.hasNegativeCycle()) {
            ans = new int[n - 2];
            for(int i = 0; i < n - 2; i++) {
                ans[i] = i;
            }
            return ans;
        }
        
        g.dfsAll(times_limit);
        
        if(g.path.size() == 0) {
            ans = new int[]{};
            return ans;
        }
        
        ans = new int[g.path.size()];
        for(int i = 0; i < ans.length; i++) {
            ans[i] = g.path.get(i);
        }
        Arrays.sort(ans);
        return ans;
    }

   public static void main(String[] args) {
      int[] ans1 = solution(new int[][]{{0, 1, 1, 1, 1}, {1, 0, 1, 1, 1}, {1, 1, 0, 1, 1}, {1, 1, 1, 0, 1}, {1, 1, 1, 1, 0}}, 3);
      int[] ans2 = solution(new int[][]{{0, 2, 2, 2, -1}, {9, 0, 2, 2, -1}, {9, 3, 0, 2, -1}, {9, 3, 2, 0, -1}, {9, 3, 2, 2, 0}}, 1);
      for(int i = 0; i < ans1.length; i++) {
         System.out.println(ans1[i]);
      }
      for(int i = 0; i < ans2.length; i++) {
         System.out.println(ans2[i]);
      }
   }
}
