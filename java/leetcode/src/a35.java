import org.junit.jupiter.api.Test;

public class a35 {
    public int searchInsert(int[] nums, int target) {
    	int start = 0;
    	int end = nums.length - 1;
    	
    	while(start <= end) {
    		int mid = (start + end) >> 1;
    	
    		if(nums[mid] == target)
    			return mid;
    		else if (nums[mid] > target) {
				end = mid - 1;
			}else {
				start = mid + 1;
			}
    	}
    	
    	return start;
    }
    
    
    @Test
    public void test() {
    	int target1 = 5;
    	int a1[] = {1,3,5,6};
    	assert searchInsert(a1, target1) == 2;
    	
    	int target2 = 2;
    	int a2[] = {1,3,5,6};
    	assert searchInsert(a2, target2) == 1;
    	
    	int target3 = 7;
    	int a3[] = {1,3,5,6};
    	assert searchInsert(a3, target3) == 4;
    	
    	int target4 = 0;
    	int a4[] = {1,3,5,6};
    	assert searchInsert(a4, target4) == 0;
    }
}
