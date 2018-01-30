
public class a189 {
	
	public void  change(int[] nums, int x, int y) {
		int len = y - x + 1;
		
		for(int i = x; 2 * i < x + y; i++) {
        	int temp = nums[i];
        	nums[i] = nums[x + y - i];
        	nums[x + y - i] = temp;
		}
	}
	
    public void rotate(int[] nums, int k) {  	
    	int len = nums.length;
    	
    	k = k % len;
    	
    	change(nums, 0, len - 1); 
    	change(nums, 0, k - 1); 
    	change(nums, k, len - 1); 
    }
}
