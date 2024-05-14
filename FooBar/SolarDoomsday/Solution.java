import java.util.ArrayList;

public class Solution {
    public static int[] solution(int area) {
        ArrayList<Integer> l = new ArrayList<>();
        while(area > 0) {
            int root = (int)Math.sqrt(area);
            root = root * root;
            l.add(root);
            area -= root;
        }
        int[] res = new int[l.size()]; 
        for(int i = 0; i < l.size(); i++) {
            res[i] = l.get(i);
            System.out.println(res[i]);
        }
        return res;
    }

   public static void main(String[] args) {
      System.out.println(solution(15324));
   }
}
