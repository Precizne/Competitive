public class Solution {
    public static int[] solution(int[] pegs) {
        int n = pegs.length;
        if(n % 2 == 0) {
            int sum = 0;
            for(int i = 0; i < n - 1; i++) {
                int alt = (i % 2 == 0) ? 1 : -1;
                sum += (pegs[n - 1 - i] - pegs[n - 2 - i]) * alt;
            }
            sum *= 2;
            int r = sum;
            if(r < 3) {
                return new int[]{-1, -1};
            }
            for(int i = 0; i < n - 1; i++) {
                r = 3 * (pegs[i + 1] - pegs[i]) - r;
                if(r < 3) {
                    return new int[]{-1, -1};
                }
            }
            if(sum % 3 == 0) {
                return new int[]{sum / 3, 1};
            }
            else {
                return new int[]{sum, 3};
            }
        }
        else {
            int sum = 0;
            for(int i = 1; i < n; i++) {
                int alt = (i % 2 != 0) ? 1 : -1;
                sum += (pegs[i] - pegs[i - 1]) * alt;
            }
            sum *= 2;
            int r = sum;
            if(r < 1) {
                return new int[]{-1, -1};
            }
            for(int i = 0; i < n - 1; i++) {
                r = pegs[i + 1] - pegs[i] - r;
                if(r < 1) {
                    return new int[]{-1, -1};
                }
            }
            return new int[]{sum, 1};
        }
    }

   public static void main(String[] args) {
     int[] ans = solution(new int[]{-1, 4, 6, 8});
      for(int i = 0; i < ans.length; i++) {
         System.out.println(ans[i]);
      }
   }
}
