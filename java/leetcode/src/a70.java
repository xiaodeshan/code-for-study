
public class a70 {
    public int climbStairs(int n) {
        if(n == 1)
        	return 1;
        if(n == 2)
        	return 2;
        int x1, x2, result = 0;
        
        x1 = 1;
        x2 = 2;
        
        for(int i = 3; i <= n; i++) {
        	result = x1 + x2;
        	x1 = x2;
        	x2 = result;
        }
        
        return result;
    }
}
