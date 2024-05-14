import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.ListIterator;

class Edge {
    public int v;
   
    public int flow;
   
    public int C;
   
    public int rev;
     
    public Edge(int v, int flow, int C, int rev) {
        this.v = v;
        this.flow = flow;
        this.C = C;
        this.rev = rev;
    }
}
 
class Graph {
    private int V;
    private int[] level;
    private List<Edge>[] adj;
 
    public Graph(int V) {
        adj = new ArrayList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new ArrayList<Edge>();
        }
        this.V = V;
        level = new int[V];
    }
 
    public void addEdge(int u, int v, int C) {
        Edge a = new Edge(v, 0, C, adj[v].size());
       
        Edge b = new Edge(u, 0, 0, adj[u].size());
 
        adj[u].add(a);
        adj[v].add(b);
    }
    
    public boolean BFS(int s, int t) {
        for (int i = 0; i < V; i++) {
            level[i] = -1;
        }
 
        level[s] = 0;
        
        LinkedList<Integer> q = new LinkedList<Integer>();
        q.add(s);
 
        ListIterator<Edge> i;
        while (q.size() != 0) {
            int u = q.poll();
 
            for (i = adj[u].listIterator(); i.hasNext();) {
                Edge e = i.next();
                if (level[e.v] < 0 && e.flow < e.C) {
                    level[e.v] = level[u] + 1;
                    q.add(e.v);
                }
            }
        }
 
        return level[t] < 0 ? false : true;
    }
    
    public int sendFlow(int u, int flow, int t, int start[]) {
       
        if (u == t) {
            return flow;
        }
 
        for (; start[u] < adj[u].size(); start[u]++) {
            Edge e = adj[u].get(start[u]);
 
            if (level[e.v] == level[u] + 1 && e.flow < e.C) {
                int curr_flow = Math.min(flow, e.C - e.flow);
 
                int temp_flow = sendFlow(e.v, curr_flow, t, start);
                
                if (temp_flow > 0) {
                    e.flow += temp_flow;
                    adj[e.v].get(e.rev).flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }
 
    public int dinicMaxFlow(int s, int t) {
        if (s == t) {
            return -1;
        }
 
        int total = 0;
 
        while (BFS(s, t) == true) {
            int[] start = new int[V + 1];
            while (true) {
                int flow = sendFlow(s, Integer.MAX_VALUE, t, start);
                if (flow == 0) {
                    break;
                }
                total += flow;
            }
        }
 
        return total;
    }
}

public class Solution {
   static int INF = 10000000;
    public static int solution(int[] entrances, int[] exits, int[][] path) {
        int n = path.length;
        int[][] capacity = new int[n + 2][n + 2];
        for(int i = 0; i < entrances.length; i++) {
            capacity[0][entrances[i] + 1] = INF;
        }
        for(int i = 0; i < exits.length; i++) {
            capacity[exits[i] + 1][n + 1] = INF;
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                capacity[i + 1][j + 1] = path[i][j];
            }
        }
        n += 2;
        Graph g = new Graph(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                g.addEdge(i, j, capacity[i][j]);
            }
        }
        return g.dinicMaxFlow(0, n - 1);
    }

   public static void main(String[] args) {
      System.out.println(solution(new int[]{0, 1}, new int[]{4, 5}, new int[][]{{0, 0, 4, 6, 0, 0}, {0, 0, 5, 2, 0, 0}, {0, 0, 0, 0, 4, 4}, {0, 0, 0, 0, 6, 6}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}));
   }
}
