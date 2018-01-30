import org.junit.Test;

public class a69 {
    public int mySqrt(int x) {
        if(x == 0 || x == 1)
        	return x;
        
        int left = 1;
        int right = x;
        
        while(left <= right) {
        	int mid = (right - left) / 2 + left;
        	
        	if(mid * mid == x) {
        		return mid;
        	}else if ((long)mid * mid < x) {
				left = mid + 1;
			}else {
				right = mid - 1;
			}
        }
        
        return right;
    }
    
    @Test
    public void test() {
    	System.out.println(mySqrt(2147395599));
    	
    }
}
